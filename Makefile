# Used to determine the SoC board drivers 
export RPI_VERSION ?= 1

export ARMGNU = arm-none-eabi

export C_FLAGS = -mcpu=arm1176jzf-s -fpic -ffreestanding -I$(INCLUDE_DIR) -std=gnu99 -O2 -Wall -Wextra
export ASM_FLAGS = -mcpu=arm1176jzf-s -fpic -ffreestanding -I$(INCLUDE_DIR)
export LINK_FLAGS = -mcpu=arm1176jzf-s -ffreestanding -O2 -nostdlib -lgcc -I$(INCLUDE_DIR)

INCLUDE_DIR = $(shell pwd)/include

BUILD_DIR = build
# Prepend absolute path for sub-makes to use
export BUILD_DIR := $(shell pwd)/$(BUILD_DIR)

# Flags for QEMU to run
EMULATOR_FLAGS = -M raspi1ap -serial stdio -kernel


.PHONY: all
all: build


.PHONY: run
run: build
	@echo
	@echo
	@echo "Running kernel image in QEMU"
	@echo
	@echo
	@qemu-system-arm $(EMULATOR_FLAGS) $(BUILD_DIR)/kernel.elf


.PHONY: build
build: create_build_dir build_sub_dirs $(BUILD_DIR)/kernel.img

create_build_dir:
	mkdir -p $(BUILD_DIR)

build_sub_dirs:
	make -e -C lib
	make -e -C boot
	make -e -C init
	make -e -C kernel
	make -e -C mm
	make -e -C drivers


$(BUILD_DIR)/kernel.img: $(BUILD_DIR)/kernel.elf
	$(ARMGNU)-objcopy $< -O binary $@

$(BUILD_DIR)/kernel.elf: linker.ld
	$(ARMGNU)-gcc -T $< -o $@ $(LINK_FLAGS) $(BUILD_DIR)/*.o

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

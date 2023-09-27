export ARMGNU = arm-none-eabi

INCLUDE_DIR = $(shell pwd)/include

export C_FLAGS = -mcpu=arm1176jzf-s -fpic -ffreestanding -I$(INCLUDE_DIR) -std=gnu99 -O2 -Wall -Wextra
export ASM_FLAGS = -mcpu=arm1176jzf-s -fpic -ffreestanding -I$(INCLUDE_DIR)
export LINK_FLAGS = -mcpu=arm1176jzf-s -ffreestanding -O2 -nostdlib -lgcc -I$(INCLUDE_DIR)

EMULATOR_FLAGS = -M raspi1ap -serial stdio -kernel

BUILD_DIR = build

export BUILD_DIR := $(shell pwd)/$(BUILD_DIR)

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
build: build_sub_dirs $(BUILD_DIR)/kernel.img


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

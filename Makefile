export ARMGNU = arm-none-eabi

export C_FLAGS = -mcpu=arm1176jzf-s -fpic -ffreestanding -std=gnu99 -O2 -Wall -Wextra
export ASM_FLAGS = -mcpu=arm1176jzf-s -fpic -ffreestanding
export LINK_FLAGS = -mcpu=arm1176jzf-s -ffreestanding -O2 -nostdlib -lgcc

EMULATOR_FLAGS = -M raspi1ap -serial stdio -kernel

BUILD_DIR = build

export BUILD_DIR := $(shell pwd)/$(BUILD_DIR)

C_FILES = $(wildcard *.c)
ASM_FILES = $(wildcard *.s)
OBJ_FILES = $(C_FILES:%.c=$(BUILD_DIR)/%_c.o)
OBJ_FILES += $(ASM_FILES:%.s=$(BUILD_DIR)/%_s.o)

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

$(BUILD_DIR)/kernel.elf: linker.ld $(OBJ_FILES)
	$(ARMGNU)-gcc -T $< -o $@ $(LINK_FLAGS) $(BUILD_DIR)/*.o

$(BUILD_DIR)/%_c.o: %.c
	mkdir -p $(@D)
	$(ARMGNU)-gcc $(C_FLAGS) -c $^ -o $@

$(BUILD_DIR)/%_s.o: %.s
	mkdir -p $(@D)
	$(ARMGNU)-gcc $(ASM_FLAGS) -c $^ -o $@


.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

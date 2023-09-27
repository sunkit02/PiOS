CC = arm-none-eabi-gcc
BOOT_FLAGS = -mcpu=arm1176jzf-s -fpic -ffreestanding
KERNEL_FLAGS = -mcpu=arm1176jzf-s -fpic -ffreestanding -std=gnu99 -O2 -Wall -Wextra

C_FLAGS = -mcpu=arm1176jzf-s -fpic -ffreestanding -std=gnu99 -O2 -Wall -Wextra
ASM_FLAGS = -mcpu=arm1176jzf-s -fpic -ffreestanding
LINK_FLAGS = -ffreestanding -O2 -nostdlib -lgcc

EMULATOR_FLAGS = -M raspi1ap -serial stdio -kernel

BUILD_DIR = build

export BUILD_DIR := $(shell pwd)/$(BUILD_DIR)

all: $(BUILD_DIR)/kernel.img

crun: clean run

run: $(BUILD_DIR)/kernel.elf
	@echo
	@echo
	@echo "Running kernel image in QEMU"
	@echo
	@echo
	@qemu-system-arm $(EMULATOR_FLAGS) $<

$(BUILD_DIR)/kernel.img: $(BUILD_DIR)/kernel.elf
	arm-none-eabi-objcopy $< -O binary $@

$(BUILD_DIR)/kernel.elf: linker.ld $(BUILD_DIR)/boot.o $(BUILD_DIR)/kernel.o $(BUILD_DIR)/utils.o
	$(CC) -T $< -o $@ $(LINK_FLAGS) $(BUILD_DIR)/*.o

$(BUILD_DIR)/boot.o: boot.s
	$(CC) $(ASM_FLAGS) -c $< -o $@

$(BUILD_DIR)/utils.o: utils.s
	$(CC) $(ASM_FLAGS) -c $< -o $@
		
$(BUILD_DIR)/kernel.o: kernel.c
	$(CC) $(C_FLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)/*

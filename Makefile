ARMGNU = arm-none-eabi

C_FLAGS = -mcpu=arm1176jzf-s -fpic -ffreestanding -std=gnu99 -O2 -Wall -Wextra
ASM_FLAGS = -mcpu=arm1176jzf-s -fpic -ffreestanding
LINK_FLAGS = -ffreestanding -O2 -nostdlib -lgcc

EMULATOR_FLAGS = -M raspi1ap -serial stdio -kernel

BUILD_DIR = build

export BUILD_DIR := $(shell pwd)/$(BUILD_DIR)

C_FILES = $(wildcard *.c)
ASM_FILES = $(wildcard *.s)
OBJ_FILES = $(C_FILES:%.c=$(BUILD_DIR)/%_c.o)
OBJ_FILES += $(ASM_FILES:%.o=$(BUILD_DIR)/%_s.o)

.PHONY: all
all: $(BUILD_DIR)/kernel.img

.PHONY: crun
crun: clean run

.PHONY: run
run: $(BUILD_DIR)/kernel.elf
	@echo
	@echo
	@echo "Running kernel image in QEMU"
	@echo
	@echo
	@qemu-system-arm $(EMULATOR_FLAGS) $<

$(BUILD_DIR)/kernel.img: $(BUILD_DIR)/kernel.elf
	$(ARMGNU)-objcopy $< -O binary $@

$(BUILD_DIR)/kernel.elf: linker.ld $(BUILD_DIR)/boot.o $(BUILD_DIR)/kernel.o $(BUILD_DIR)/utils.o
	$(ARMGNU)-gcc -T $< -o $@ $(LINK_FLAGS) $(BUILD_DIR)/*.o

$(BUILD_DIR)/boot.o: boot.s
	$(ARMGNU)-gcc $(ASM_FLAGS) -c $< -o $@

$(BUILD_DIR)/utils.o: utils.s
	$(ARMGNU)-gcc $(ASM_FLAGS) -c $< -o $@
		
$(BUILD_DIR)/kernel.o: kernel.c
	$(ARMGNU)-gcc $(C_FLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)/*

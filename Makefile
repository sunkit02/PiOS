ARMGCC=arm-none-ebi-gcc
BOOT_FLAGS=-mcpu=arm1176jzf-s -fpic -ffreestanding
KERNEL_FLAGS=-mcpu=arm1176jzf-s -fpic -ffreestanding -std=gnu99 -O2 -Wall -Wextra

BUILD=build

all: $(BUILD)/kernel.img

run: $(BUILD)/kernel.elf
	@echo
	@echo
	@echo "Running kernel image in QEMU"
	@echo
	@echo
	@qemu-system-arm -M raspi1ap -serial stdio -kernel $<

$(BUILD)/kernel.img: $(BUILD)/kernel.elf
	arm-none-eabi-objcopy $< -O binary $@

$(BUILD)/kernel.elf: linker.ld $(BUILD)/boot.o $(BUILD)/kernel.o
	arm-none-eabi-gcc -T $< -o $@ -ffreestanding -O2 -nostdlib $(BUILD)/*.o -lgcc

$(BUILD)/boot.o: boot.s
	arm-none-eabi-gcc -mcpu=arm1176jzf-s -fpic -ffreestanding -c $< -o $@
		
$(BUILD)/kernel.o: kernel.c
	arm-none-eabi-gcc -mcpu=arm1176jzf-s -fpic -ffreestanding -std=gnu99 -c $< -o $@ -O2 -Wall -Wextra

clean:
	rm -rf $(BUILD)/*

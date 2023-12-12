C_FILES = $(wildcard *.c)
ASM_FILES = $(wildcard *.S)
OBJ_FILES = $(C_FILES:%.c=$(BUILD_DIR)/%_c.o)
OBJ_FILES += $(ASM_FILES:%.S=$(BUILD_DIR)/%_S.o)

.PHONY: all
all: $(OBJ_FILES)

$(BUILD_DIR)/%_c.o: %.c
	mkdir -p $(@D)
	$(ARMGNU)-gcc $(C_FLAGS) -c $^ -o $@

$(BUILD_DIR)/%_S.o: %.S
	mkdir -p $(@D)
	$(ARMGNU)-gcc $(ASM_FLAGS) -c $^ -o $@

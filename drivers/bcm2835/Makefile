C_FILES = $(wildcard *.c)
ASM_FILES = $(wildcard *.s)
OBJ_FILES = $(C_FILES:%.c=$(BUILD_DIR)/%_c.o)
OBJ_FILES += $(ASM_FILES:%.s=$(BUILD_DIR)/%_s.o)

.PHONY: all
all: $(OBJ_FILES)
	@echo
	@echo
	@echo
	@echo "OBJ_FILES: " $(OBJ_FILES)
	@echo
	@echo
	@echo

$(BUILD_DIR)/%_c.o: %.c
	$(ARMGNU)-gcc $(C_FLAGS) -c $^ -o $@

$(BUILD_DIR)/%_s.o: %.s
	$(ARMGNU)-gcc $(ASM_FLAGS) -c $^ -o $@

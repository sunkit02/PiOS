C_FILES = $(wildcard *.c)
ASM_FILES = $(wildcard *.s)
OBJ_FILES = $(C_FILES:%.c=$(BUILD_DIR)/%_c.o)
OBJ_FILES += $(ASM_FILES:%.s=$(BUILD_DIR)/%_s.o)

.PHONY: all
all: $(OBJ_FILES) build_bcm_drivers

$(BUILD_DIR)/%_c.o: %.c
	mkdir -p $(@D)
	$(ARMGNU)-gcc $(C_FLAGS) -c $^ -o $@

$(BUILD_DIR)/%_s.o: %.s
	mkdir -p $(@D)
	$(ARMGNU)-gcc $(ASM_FLAGS) -c $^ -o $@

# Determine the BCM directory to compile based on RPI_VERSION

BCM_BOARD_NUM = 2835

ifeq ($(RPI_VERSION), 1)
	BCM_BOARD_NUM = 2835
endif
ifeq ($(RPI_VERSION), 2)
	BCM_BOARD_NUM = 2837
endif
ifeq ($(RPI_VERSION), 3)
	BCM_BOARD_NUM = 2837
endif
ifeq ($(RPI_VERSION), 4)
	BCM_BOARD_NUM = 2711
endif
ifeq ($(RPI_VERSION), 5)
	BCM_BOARD_NUM = 2712
endif

build_bcm_drivers:
	@echo
	@echo
	@echo
	make -e -C bcm$(BCM_BOARD_NUM)
	@echo
	@echo
	@echo

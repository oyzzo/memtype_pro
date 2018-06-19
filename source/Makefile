#
# Makefile for c project of Atmel ATSAMD21G18A device
#

ifdef SystemRoot
	SHELL = cmd.exe
	MKDIR = mkdir
else
	ifeq ($(shell uname), Linux)
	MKDIR = mkdir -p
	endif
endif

# COMPILER TOOLS (GCC VERSION arm-none-eabi-gcc-7.2.1)
CC=arm-none-eabi-gcc
CXX=arm-none-eabi-g++
OBJCOPY=arm-none-eabi-objcopy
OBJDUMP=arm-none-eabi-objdump
SIZE=arm-none-eabi-size

# PROJECT NAME
OUTPUT_FILE=memtype_pro.elf
OUTPUT_FILE_NAME=$(basename $(OUTPUT_FILE))

# ASM FLAGS
ASFLAGS=-mthumb -mcpu=Cortex-M0plus -D__SAMD21G18A__ -O1 -ffunction-sections -Wall

# C FLAGS
CFLAGS=-x c -mthumb -mcpu=Cortex-M0plus -D__SAMD21G18A__ -O1 -ffunction-sections -Wall -c -std=gnu99

#LINKER
LINKER_FILE = Device_Startup/samd21g18a_flash.ld
LDFLAGS=-Wl,--start-group -lm  -Wl,--end-group -Wl,--gc-sections -mthumb -mcpu=Cortex-M0plus -T$(LINKER_FILE) -L ../tools/ARM.CMSIS.5.0.1/CMSIS/Lib/GCC

# PROJECT PATHS
INCLUDE_PATHS=-I../tools/Atmel.SAMD21_DFP.1.3.304/samd21a/include
INCLUDE_PATHS+=-I../tools/ARM.CMSIS.5.0.1/CMSIS/Include

# SOURCE FILES
SRCS =  main.c  
SRCS += Device_Startup/system_samd21.c  Device_Startup/startup_samd21.c
SRCS += CLOCK/clock_manager.c
SRCS += PM/power_manager.c
SRCS += PORT/port_manager.c
SRCS += I2C/i2c.c
SRCS += USART/usart.c
SRCS += OLED/oled.c
SRCS += GUI/gui.c

# Convert .c to .o
OBJS = $(SRCS:.c=.o)

# All target
all: release

# Release target
# Using target specific variable values
release: CFLAGS += -O1
release: ASLAGS += -O1
release: $(OUTPUT_FILE)

# Debug target
# Using target specific variable values
debug: CFLAGS += -ggdb -DDEBUG
debug: ASFLAGS += -ggdb -DDEBUG
debug: $(OUTPUT_FILE)

# Generate the documentation
docs:
	rm -rf docs
	doxygen Doxyfile

# Link target
$(OUTPUT_FILE): $(OBJS)
	$(CC) -o $(OUTPUT_FILE) $(LDFLAGS) $(OBJS)
	$(OBJCOPY) -O binary $(OUTPUT_FILE_NAME).elf $(OUTPUT_FILE_NAME).bin
	$(OBJCOPY) -O ihex -R .eeprom -R .fuse -R .lock -R .signature  $(OUTPUT_FILE_NAME).elf $(OUTPUT_FILE_NAME).hex
	$(OBJDUMP) -h -S $(OUTPUT_FILE_NAME).elf > $(OUTPUT_FILE_NAME).lss
	$(SIZE) $(OUTPUT_FILE_NAME).elf

# Compile target(s)
./%.o: ./%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE_PATHS) -o $@ $<

./%.o: ./%.c
	$(CC) $(CFLAGS) $(INCLUDE_PATHS) -o $@ $<

startup/%.o: startup/%.c
	$(CC) $(CFLAGS) $(INCLUDE_PATHS) -o $@ $<

clean:
	rm -f $(OBJS)
	rm -f $(OUTPUT_FILE_NAME).elf $(OUTPUT_FILE_NAME).bin $(OUTPUT_FILE_NAME).hex $(OUTPUT_FILE_NAME).lss
	rm -rf docs

# Add targets that aren't a file
.PHONY: all release debug clean

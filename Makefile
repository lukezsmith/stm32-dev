.PHONY: all build cmake clean format

BUILD_DIR := build
TARGET := blinky
BUILD_TYPE ?= Debug

all: build flash

${BUILD_DIR}/Makefile:
	cmake \
		-B${BUILD_DIR} \
		-DCMAKE_BUILD_TYPE=${BUILD_TYPE} \
		-DCMAKE_TOOLCHAIN_FILE=cmake/gcc-arm-none-eabi.cmake \
		-DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
		-DDUMP_ASM=OFF
	

cmake: ${BUILD_DIR}/Makefile

build: cmake
	$(MAKE) -C ${BUILD_DIR} --no-print-directory

SRCS := $(shell find . -name '*.[ch]' -or -name '*.[ch]pp')
%.format: %
	clang-format -i $<
format: $(addsuffix .format, ${SRCS})

flash: build
	@st-flash write $(BUILD_DIR)/$(TARGET).bin 0x8000000

clean:
	rm -rf $(BUILD_DIR)



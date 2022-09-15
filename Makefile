.PHONY: all build cmake clean

TARGET := main
BUILD_TYPE ?= test
CMAKE_PATH := /opt/local/bin/cmake
CTEST_PATH := /opt/local/bin/ctest
STFLASH_PATH := /opt/homebrew/bin/st-flash

ifeq ($(BUILD_TYPE), test)
	BUILD_DIR := build/test
	TOOLCHAIN_FILE := ""
else
	BUILD_DIR := build/release
	TOOLCHAIN_FILE := cmake/gcc-arm-none-eabi.cmake
endif

all: build 
	    @if [ "$(BUILD_TYPE)" = "test" ]; then \
			$(CTEST_PATH) --test-dir $(BUILD_DIR);\
		fi

${BUILD_DIR}/Makefile:
	@${CMAKE_PATH} \
		-B${BUILD_DIR} \
		-DCMAKE_BUILD_TYPE=${BUILD_TYPE} \
		-DCMAKE_TOOLCHAIN_FILE=${TOOLCHAIN_FILE} \
		-DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
		-DDUMP_ASM=OFF

cmake: ${BUILD_DIR}/Makefile

build: cmake
	@$(MAKE) -C ${BUILD_DIR} --no-print-directory

flash: build/release/Makefile 
	@st-flash write build/release/$(TARGET).bin 0x8000000

# test: build
# 	ctest --test-dir ./build/test
clean:
	rm -rf build



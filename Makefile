.PHONY: all build cmake clean

TARGET := main
TEST_MODE ?= FALSE
BUILD_TYPE ?= Debug
CMAKE_PATH := /opt/local/bin/cmake
CTEST_PATH := /opt/local/bin/ctest

ifeq ($(TEST_MODE), TRUE)
	BUILD_DIR := build/test
	TOOLCHAIN_FILE := ""
else
	BUILD_DIR := build/release
	TOOLCHAIN_FILE := cmake/gcc-arm-none-eabi.cmake
endif

all: build 
	    @if [ "$(TEST_MODE)" = TRUE ]; then \
			$(CTEST_PATH) --test-dir $(BUILD_DIR);\
		fi

${BUILD_DIR}/Makefile:
	@${CMAKE_PATH} \
		-B${BUILD_DIR} \
		-DTEST_MODE=${TEST_MODE} \
		-DCMAKE_BUILD_TYPE=${BUILD_TYPE} \
		-DCMAKE_TOOLCHAIN_FILE=${TOOLCHAIN_FILE} \
		-DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
		-DDUMP_ASM=OFF

cmake: ${BUILD_DIR}/Makefile

build: cmake
	@$(MAKE) -C ${BUILD_DIR} --no-print-directory

flash: build/release/Makefile 
	openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c "program build/release/$(TARGET).elf verify reset exit"

# test: build
# 	ctest --test-dir ./build/test
clean:
	rm -rf build



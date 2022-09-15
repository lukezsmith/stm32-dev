cmake_minimum_required(VERSION 3.14)

# add modules to module path so we can include() them easier
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

project(main LANGUAGES C CXX ASM)

set(EXECUTABLE main)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

set(CPU_PARAMETERS
    -mcpu=cortex-m4
    -mthumb
    -mfpu=fpv4-sp-d16
    -mfloat-abi=softfp)

set(PROJECT_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR})    
set(PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(STARTUP_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/include/startup_stm32f407vgtx.s)
set(MCU_LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/flash/STM32F407VGTX_FLASH.ld)
set(CMSIS_PATH ${CMAKE_CURRENT_SOURCE_DIR}/libs/CMSIS_5/CMSIS/Core)

add_subdirectory(src/modules)

# Production build
if(CMAKE_BUILD_TYPE STREQUAL release)
    #  -------- Create executable --------
    add_executable(${EXECUTABLE}
        ${PROJECT_DIR}/${EXECUTABLE}.c
        ${STARTUP_SCRIPT})
        
    #  -------- Include dependencies --------
    target_include_directories(${EXECUTABLE} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMSIS_PATH}/Include)

    #  -------- Compilation configuration --------
    target_compile_options(${EXECUTABLE} PRIVATE
        ${CPU_PARAMETERS}
            -DSTM32F407xx
            -std=gnu11
            -Wall
            -Wextra
            -Wpedantic
            -Wshadow
            -Wdouble-promotion
            -Wformat=2 -Wformat-truncation
            -Wmissing-include-dirs
            -Wsign-compare
            -Wundef
            -Wcast-align
            -Wconversion
            -fno-common
            -fsingle-precision-constant
            -fomit-frame-pointer
            -ffunction-sections 
            -fdata-sections
            -Wno-unused-parameter
            --specs=nano.specs
            $<$<CONFIG:Debug>:-Og -g3 -ggdb>
            $<$<CONFIG:Release>:-Og -g0>)

    target_link_options(${EXECUTABLE} PRIVATE
        -T${MCU_LINKER_SCRIPT}
        ${CPU_PARAMETERS}
        -Wl,-Map=${EXECUTABLE}.map
        --specs=nano.specs
        -Wl,--gc-sections
        -lc)

    #  -------- Post-build: create binary --------
    add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${EXECUTABLE}> ${EXECUTABLE}.bin)
# Test build
else()
    #  -------- GoogleTest --------
    include(FetchContent)
    FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
    )
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    # set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
    enable_testing()
    add_subdirectory(test)

endif()
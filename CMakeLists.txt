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

set(STARTUP_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/src/startup_stm32f407xx.s)
set(MCU_LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/flash/STM32F407VGTX_FLASH.ld)
set(CMSIS_PATH ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/CMSIS)
set(HAL_PATH ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver)

add_subdirectory(src/modules)

# Production build
if(CMAKE_BUILD_TYPE STREQUAL release)
    #  -------- Collate Code Sources --------
    file(GLOB_RECURSE PROJECT_SOURCES "${PROJECT_DIR}/*.c")
    file(GLOB_RECURSE HAL_SOURCES "${HAL_PATH}/Src/*.c")
    #  -------- Include HAL Sources -------- 
    set(HAL_SOURCES
    ${HAL_PATH}/Src/stm32f4xx_hal_hcd.c 
    ${HAL_PATH}/Src/stm32f4xx_ll_usb.c
    ${HAL_PATH}/Src/stm32f4xx_hal_rcc.c 
    ${HAL_PATH}/Src/stm32f4xx_hal_rcc_ex.c 
    ${HAL_PATH}/Src/stm32f4xx_hal_flash.c 
    ${HAL_PATH}/Src/stm32f4xx_hal_flash_ex.c 
    ${HAL_PATH}/Src/stm32f4xx_hal_flash_ramfunc.c 
    ${HAL_PATH}/Src/stm32f4xx_hal_gpio.c 
    ${HAL_PATH}/Src/stm32f4xx_hal_dma_ex.c 
    ${HAL_PATH}/Src/stm32f4xx_hal_dma.c 
    ${HAL_PATH}/Src/stm32f4xx_hal_pwr.c 
    ${HAL_PATH}/Src/stm32f4xx_hal_pwr_ex.c
    ${HAL_PATH}/Src/stm32f4xx_hal_cortex.c 
    ${HAL_PATH}/Src/stm32f4xx_hal.c 
    ${HAL_PATH}/Src/stm32f4xx_hal_exti.c 
    ${HAL_PATH}/Src/stm32f4xx_hal_i2c.c 
    ${HAL_PATH}/Src/stm32f4xx_hal_i2c_ex.c 
    ${HAL_PATH}/Src/stm32f4xx_hal_i2s.c 
    ${HAL_PATH}/Src/stm32f4xx_hal_i2s_ex.c 
    ${HAL_PATH}/Src/stm32f4xx_hal_spi.c 
    ${HAL_PATH}/Src/stm32f4xx_hal_tim.c 
    ${HAL_PATH}/Src/stm32f4xx_hal_tim_ex.c)

    #  -------- Create executable --------
    add_executable(${EXECUTABLE}
        ${PROJECT_SOURCES}
        ${HAL_SOURCES}
        ${STARTUP_SCRIPT})
        
    #  -------- Include dependencies --------
    target_include_directories(${EXECUTABLE} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${HAL_PATH}/Inc
        ${HAL_PATH}/Inc/Legacy
        ${CMSIS_PATH}/Device/ST/STM32F4xx/Include
        ${CMSIS_PATH}/Include)

    #  -------- Compilation configuration --------
    target_compile_options(${EXECUTABLE} PRIVATE
        ${CPU_PARAMETERS}
            -DUSE_HAL_DRIVER 
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
            # -Wcast-align
            # -Wconversion
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
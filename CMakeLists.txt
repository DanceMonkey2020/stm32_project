# 设置 CMake 最低支持版本
cmake_minimum_required(VERSION 3.17)

# Cmake 交叉编译配置
set(CMAKE_SYSTEM_NAME Generic)

# 定义工程名称
project("demo")

# 指定编译工具
set(CMAKE_C_COMPILER "arm-none-eabi-gcc")
set(CMAKE_CXX_COMPILER "arm-none-eabi-g++")
set(CMAKE_ASM_COMPILER "arm-none-eabi-gcc")
set(CMAKE_AR "arm-none-eabi-ar")
set(CMAKE_OBJCOPY "arm-none-eabi-objcopy")
set(CMAKE_OBJDUMP "arm-none-eabi-objdump")
set(CMAKE_SIZE "arm-none-eabi-size")

# 编译相关选项
set(MCU_FLAGS "-mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16")
set(CMAKE_C_FLAGS_DEBUG "-g -ggdb -Og")
set(CMAKE_C_FLAGS_RELEASE "-O3")
set(CMAKE_C_FLAGS "${MCU_FLAGS}  -Wall -Wno-unknown-pragmas -Wl,-u,_printf_float") #-w -Wall
set(CMAKE_ASM_FLAGS "${MCU_FLAGS} -x assembler-with-cpp")


option(BOOT "build for boot!" OFF)
option(RELEASE "build for release!" OFF)
option(FREERTOS "FreeRTOS support" OFF)


if(RELEASE)
    message("build for release!")
    set(CMAKE_BUILD_TYPE "Release")
    add_definitions(-DRELEASE)
else()
    message("build for debug!")
    set(CMAKE_BUILD_TYPE "Debug")
    add_definitions(-DDEBUG)
endif()

if(BOOT)
    message("build for boot!")
    add_definitions(-DBOOT)
else()
    message("build for app!")
endif()

if(FREERTOS)
    message("FreeRTOS support!")
    add_definitions(-DFREERTOS)
else()
    message("FreeRTOS support not!")
endif()

if(${DEVICE_TYPE} MATCHES "STM32") 
    add_definitions(-DSTM32)
endif()

if(${DEVICE_TYPE} MATCHES "STM32F4") 
    add_definitions(-DSTM32F4)
    add_definitions(-DARM_MATH_CM4)

endif()

if(${DEVICE_TYPE} MATCHES "STM32F40|STM32F41") 
    add_definitions(-DSTM32F40_41xxx)
endif()

if(${DEVICE_TYPE} MATCHES "STM32F407ZGTX") 
    add_definitions(-DSTM32F407ZGTX) 
endif()

add_definitions(-DUSE_STDPERIPH_DRIVER)

add_subdirectory(Platform) #平台库
add_subdirectory(Application) #应用



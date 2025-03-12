## 简介
本工程使用GCC编译器、MinGW、CMake构建工具和OpenOCD调试工具。实现了替代KEIL, IAR等在某些情况下不方便使用的情况。实现了编译、调试、下载、烧录一体。搭配Cursor的Tab补全功能，编码效率大大提升。

---
## 工具下载及安装
- **Cursor** 辅助编码工具
- **GCC** 交叉编译工具是一种用于在一种平台上编译代码，以便在另一种平台上运行的工具。
- **MinGW** MinGW包含make工具,它通过读取名为`Makefile`的文件，定义了如何编译和链接程序。
- **CMake** 构建工具，它通过读取名为`CMakeLists.txt`的文件，定义了如何编译和链接程序。
- **OpenOCD** 开源的调试器，用于调试嵌入式系统。


此工程使用的是Windows系统，所以下载的工具都是Windows版本的。ubuntu系统同理。

版本对应日期：2025-02-08

<span style="color:red;">注意：工具安装路径不要有中文，否则可能会出现编译错误。</span>


### 安装Cursor
 Cursor是VSCode的分支，所以VSCode的插件都可以使用，这也是Cursor的优点之一。强大的Claude 3.5 Sonnet模型加上自动提示Tab补全功能对于编码来说真的是妙不可言。收费20$/月，高端模型500次调用GPT-4, GPT-4o, 和Claude 3.5 Sonnet。GPT-4o-mini或Cursor-small则没有次数限制。
 github账号登陆可以体验15天，过期不缴费则与VSCode一样。
 
 现在正是AI的窗口期，AI工具日新月异。包括国产的大模型DeepSeek搭配VSCode也是不错的低价方案。

版本：**0.44.8**
下载地址：https://www.cursor.com/

安装过程略

需要安装的插件 
- **Cortex-Debug**  ARM Cortex-M GDB Debugger support for VSCode
- **C/C++** C/C++ for Visual Studio Code

### 安装GCC
交叉编译工具是一种用于在一种平台上编译代码，以便在另一种平台上运行的工具。它们特别适用于嵌入式系统开发，因为开发环境通常与目标硬件平台不同。

版本：**gcc-arm-none-eabi-10.3-2021.10-win32.zip**

下载地址：https://developer.arm.com/downloads/-/gnu-rm

解压到非中文路径下，例如：E:\tools\

在环境变量中添加环境变量

`此电脑->属性->高级系统设置->环境变量->系统变量->Path->编辑->新建->E:\tools\gcc-arm-none-eabi-10.3-2021.10\bin`

添加成功后，在命令行中输入```arm-none-eabi-gcc -v```，如果出现版本信息，则表示添加成功。内容如下

```
C:\Users\yulc>arm-none-eabi-gcc -v
Using built-in specs.
COLLECT_GCC=arm-none-eabi-gcc
COLLECT_LTO_WRAPPER=d:/desktop/software/gcc-arm-none-eabi-10.3-2021.10/bin/../lib/gcc/arm-none-eabi/10.3.1/lto-wrapper.exe
Target: arm-none-eabi
Configured with: /mnt/workspace/workspace/GCC-10-pipeline/jenkins-GCC-10-pipeline-338_20211018_1634516203/src/gcc/configure --build=x86_64-linux-gnu --host=i686-w64-mingw32 --target=arm-none-eabi --prefix=/mnt/workspace/workspace/GCC-10-pipeline/jenkins-GCC-10-pipeline-338_20211018_1634516203/install-mingw --libexecdir=/mnt/workspace/workspace/GCC-10-pipeline/jenkins-GCC-10-pipeline-338_20211018_1634516203/install-mingw/lib --infodir=/mnt/workspace/workspace/GCC-10-pipeline/jenkins-GCC-10-pipeline-338_20211018_1634516203/install-mingw/share/doc/gcc-arm-none-eabi/info --mandir=/mnt/workspace/workspace/GCC-10-pipeline/jenkins-GCC-10-pipeline-338_20211018_1634516203/install-mingw/share/doc/gcc-arm-none-eabi/man --htmldir=/mnt/workspace/workspace/GCC-10-pipeline/jenkins-GCC-10-pipeline-338_20211018_1634516203/install-mingw/share/doc/gcc-arm-none-eabi/html --pdfdir=/mnt/workspace/workspace/GCC-10-pipeline/jenkins-GCC-10-pipeline-338_20211018_1634516203/install-mingw/share/doc/gcc-arm-none-eabi/pdf --enable-languages=c,c++ --enable-mingw-wildcard --disable-decimal-float --disable-libffi --disable-libgomp --disable-libmudflap --disable-libquadmath --disable-libssp --disable-libstdcxx-pch --disable-nls --disable-shared --disable-threads --disable-tls --with-gnu-as --with-gnu-ld --with-headers=yes --with-newlib --with-python-dir=share/gcc-arm-none-eabi --with-sysroot=/mnt/workspace/workspace/GCC-10-pipeline/jenkins-GCC-10-pipeline-338_20211018_1634516203/install-mingw/arm-none-eabi --with-libiconv-prefix=/mnt/workspace/workspace/GCC-10-pipeline/jenkins-GCC-10-pipeline-338_20211018_1634516203/build-mingw/host-libs/usr --with-gmp=/mnt/workspace/workspace/GCC-10-pipeline/jenkins-GCC-10-pipeline-338_20211018_1634516203/build-mingw/host-libs/usr --with-mpfr=/mnt/workspace/workspace/GCC-10-pipeline/jenkins-GCC-10-pipeline-338_20211018_1634516203/build-mingw/host-libs/usr --with-mpc=/mnt/workspace/workspace/GCC-10-pipeline/jenkins-GCC-10-pipeline-338_20211018_1634516203/build-mingw/host-libs/usr --with-isl=/mnt/workspace/workspace/GCC-10-pipeline/jenkins-GCC-10-pipeline-338_20211018_1634516203/build-mingw/host-libs/usr --with-libelf=/mnt/workspace/workspace/GCC-10-pipeline/jenkins-GCC-10-pipeline-338_20211018_1634516203/build-mingw/host-libs/usr --with-host-libstdcxx='-static-libgcc -Wl,-Bstatic,-lstdc++,-Bdynamic -lm' --with-pkgversion='GNU Arm Embedded Toolchain 10.3-2021.10' --with-multilib-list=rmprofile,aprofile
Thread model: single
Supported LTO compression algorithms: zlib
gcc version 10.3.1 20210824 (release) (GNU Arm Embedded Toolchain 10.3-2021.10)
```

### 安装MinGW

版本：**x86_64-14.2.0-release-win32-seh-ucrt-rt_v12-rev1.7z**

下载地址：https://www.mingw-w64.org/downloads/

解压到非中文路径下，例如：E:\tools\

在环境变量中添加环境变量

`此电脑->属性->高级系统设置->环境变量->系统变量->Path->编辑->新建->E:\tools\mingw64\bin`

添加成功后，在命令行中输入`make -v`，如果出现版本信息，则表示添加成功。内容如下

```
C:\Users\yulc>make -v
GNU Make 4.2.1
Built for x86_64-w64-mingw32
Copyright (C) 1988-2016 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
```

### 安装CMake

CMake是一个跨平台的开源构建系统，用于管理和构建软件项目。它通过读取名为`CMakeLists.txt`的文件，定义了如何编译和链接程序。

下载地址：https://cmake.org/download/

版本：**cmake-3.31.5-windows-x86_64.zip**

解压到非中文路径下，例如：E:\tools\

在环境变量中添加环境变量

`此电脑->属性->高级系统设置->环境变量->系统变量->Path->编辑->新建->E:\tools\cmake\bin`

添加成功后，在命令行中输入`cmake --version`，如果出现版本信息，则表示添加成功。内容如下

```
C:\Users\yulc>cmake -version
cmake version 3.26.4

CMake suite maintained and supported by Kitware (kitware.com/cmake).
```

### 安装OpenOCD

下载地址：https://github.com/openocd-org/openocd

版本：**xpack-openocd-0.12.0-6-darwin-arm64.tar.gz**

解压到非中文路径下，例如：E:\tools\

在环境变量中添加环境变量

`此电脑->属性->高级系统设置->环境变量->系统变量->Path->编辑->新建->E:\tools\xpack-openocd-0.12.0-3\bin`

添加成功后，在命令行中输入`openocd -v`，如果出现版本信息，则表示添加成功。内容如下

```
C:\Users\yulc>openocd -v
Open On-Chip Debugger 0.12.0 (2023-02-02) [https://github.com/sysprogs/openocd]
Licensed under GNU GPL v2
libusb1 09e75e98b4d9ea7909e8837b7a3f00dda4589dc3
For bug reports, read
        http://openocd.org/doc/doxygen/bugs.html
```

---

## 工程搭建

这里通过STM32F407ZGTX为例，讲解如何搭建工程，GD32同理。

新建工程目录，该项目结构如下所示，包含了编译输出、工程配置、平台库、应用代码、脚本和VSCode配置等内容：

```
PROJECT
├── build               # 编译输出目录，存放生成的二进制文件和其他构建产物
├── CMakeLists.txt      # 工程配置文件，定义了构建过程和依赖关系
├── Platform            # 平台库，包含硬件抽象层和标准库
│   ├── FW              # 标准库，提供对STM32F4系列微控制器的支持
│   └── CMSIS           # Cortex-M微控制器软件接口标准
│   └── CMakeLists.txt  # 平台库的CMake配置文件生成libxxxx.a文件
├── Application         # 应用代码，包含主程序和其他应用逻辑
│   └── CMakeLists.txt  # BSP目录
│   └── BoardTest       # 各个板级
│        └── main.c          # 主函数，程序的入口点
│        └── CMakeLists.txt  # 应用的CMake配置文件生成elf文件，链接libxxxx.a文件，生成hex和bin文件
├── scripts             # 脚本，包含构建和调试所需的配置文件
│   ├── STM32F407ZGTX.ld  # 链接脚本，定义了内存布局和链接规则
│   ├── STM32F407ZGTX.svd # 寄存器描述文件，提供外设寄存器的定义
│   ├── openocd_target.cfg # OpenOCD配置文件，用于调试和编程
│   ├── cmsis-dap.cfg   # CMSIS-DAP下载器配置文件
│   └── stlink-dap.cfg  # ST-Link下载器配置文件
└── .vscode             # VSCode工程配置，包含调试和任务设置
   ├── tasks.json       # 任务设置，包含编译、下载、烧录等任务
   └── launch.json      # 调试配置，包含调试器和调试参数
   └── c_cpp_properties.json # 编译器配置，包含编译器路径、标准库路径、宏定义等

```

具体思路通过CMAKE配置，交叉编译参数，指定静态库目录，和应用执行目录，通过链接脚本生成elf文件，通过objcopy生成hex和bin文件。

由于涉及到的内容较多，篇幅有限，仅贴出部分代码如下。

### 根CMakeLists.txt

 PROJECT/CMakeLists.txt，指定编译工具，交叉编译配置，定义工程名称，指定编译工具，指定静态库目录，和应用执行目录。  通过DEVICE_TYPE指定设备类型，添加宏定义。
 
 ```
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




 ```

### 库CMakeLists.txt

 Platform/CMakeLists.txt，指定启动文件，添加ASM支持，设置启动文件C属性，生成库目标platform，设置库输出的名称，设置库文件的默认输出路径。
 
 ```
#添加头文件搜索路径
include_directories(    
    ./CMSIS/Include
    ./CMSIS/Device/ST/STM32F4xx/Include
    ./FW/STM32F4xx_StdPeriph_Driver/inc   
    ./Include
)

#添加源文件
aux_source_directory(./CMSIS/Device/ST/STM32F4xx/Source/Templates SRC_LIST)

#添加标准库源文件
if(${DEVICE_TYPE} MATCHES "STM32F40|STM32F41")

file(GLOB FW_LIST 
./FW/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_adc.c
./FW/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_crc.c
./FW/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dbgmcu.c
./FW/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dma.c
./FW/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_exti.c
./FW/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_flash.c
./FW/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_gpio.c
./FW/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_i2c.c
./FW/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_iwdg.c
./FW/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_pwr.c
./FW/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rcc.c
./FW/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rtc.c
./FW/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_sdio.c
./FW/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_spi.c
./FW/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_syscfg.c
./FW/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_tim.c
./FW/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_usart.c
./FW/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_wwdg.c
./FW/STM32F4xx_StdPeriph_Driver/src/misc.c   
./FW/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp.c
./FW/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash.c
./FW/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rng.c
./FW/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_can.c
./FW/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dac.c
./FW/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dcmi.c
./FW/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_fsmc.c
)
endif()

#设置启动文件变量
if(${DEVICE_TYPE} MATCHES "STM32F407ZGTX") 
set(START_UP_ASM ./CMSIS/Device/ST/STM32F4xx/Source/Templates/GNU/startup_stm32f407zgtx.s)
endif()

#设置支持 ASM
ENABLE_LANGUAGE(ASM)

#设置启动文件 C 属性
set_property(SOURCE ${START_UP_ASM} PROPERTY LANGUAGE C)

#生成库目标 platform
add_library(platform STATIC
    ${START_UP_ASM}
    ${SRC_LIST}
    ${FW_LIST}
)

#设置库输出的名称
set_target_properties(platform PROPERTIES OUTPUT_NAME ${DEVICE_TYPE})

#设置库文件的默认输出路径
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/lib)

 ```    

### BSP目录CMakeLists.txt

通过tasks.json传入参数，检索BSP子目录

```
#添加头文件搜索路径
include_directories(
    ${PROJECT_SOURCE_DIR}/Platform/CMSIS/Include
    ${PROJECT_SOURCE_DIR}/Platform/CMSIS/Device/ST/STM32F4xx/Include
    ${PROJECT_SOURCE_DIR}/Platform/FW/STM32F4xx_StdPeriph_Driver/inc   
    ${PROJECT_SOURCE_DIR}/Application
)


#测试
if(${BOARD_TYPE} MATCHES "BOARD_TEST") 
    add_definitions(-DBOARD_TEST)
    message("build for BOARD_TEST!")
    add_subdirectory(BoardTest)
endif()
```


### 可执行CMakeLists.txt

 Application/CMakeLists.txt，指定链接脚本，设置链接选项，生成目标文件，确保可执行文件依赖于动态库，把目标文件与库文件进行链接，设置可执行文件输出路径，设置 ELF 转换路径，添加自定义命令实现 ELF 转换 hex 和 bin 文件。

```
set(VERSION_MAJOR "1")
set(VERSION_MINOR "0")
set(VERSION_PATCH "0")

#APP
# v1.0.0 首次添加


set(BOOT_VERSION_MAJOR "1")
set(BOOT_VERSION_MINOR "0")
set(BOOT_VERSION_PATCH "0")

#BOOT
# v1.0.0 首次添加

add_definitions(-DVERSION_MAJOR=${VERSION_MAJOR})
add_definitions(-DVERSION_MINOR=${VERSION_MINOR})
add_definitions(-DVERSION_PATCH=${VERSION_PATCH})
add_definitions(-DBOOT_VERSION_MAJOR=${BOOT_VERSION_MAJOR})
add_definitions(-DBOOT_VERSION_MINOR=${BOOT_VERSION_MINOR})
add_definitions(-DBOOT_VERSION_PATCH=${BOOT_VERSION_PATCH})

#添加头文件搜索路径
include_directories(
    ./Include
)


aux_source_directory(./Source SRC_LIST)


#添加非标准的共享库搜索路径
link_directories(${PROJECT_SOURCE_DIR}/build/lib)
link_directories(${PROJECT_SOURCE_DIR}/Platform/CMSIS/Lib/GCC)

if(${BOOT})
        set(LINKER_SCRIPT ${PROJECT_SOURCE_DIR}/scripts/${DEVICE_TYPE}_BOOT.ld)
else()
        set(LINKER_SCRIPT ${PROJECT_SOURCE_DIR}/scripts/${DEVICE_TYPE}.ld)
endif()

#设置链接选项
set(CMAKE_EXE_LINKER_FLAGS " -specs=rdimon.specs --specs=nano.specs -specs=nosys.specs -T${LINKER_SCRIPT} -Wl,-Map=${PROJECT_BINARY_DIR}/${DEVICE_TYPE}.map,--cref -Wl,--gc-sections")

#生成目标文件
add_executable(${DEVICE_TYPE}.elf main.c ${SRC_LIST})

# 确保可执行文件依赖于动态库
add_dependencies(${DEVICE_TYPE}.elf platform)

if(${BOOT})
    #把目标文件与库文件进行链接
    target_link_libraries(${DEVICE_TYPE}.elf 
    ${DEVICE_TYPE}
    arm_cortexM4lf_math
    )
else()
    #把目标文件与库文件进行链接
    target_link_libraries(${DEVICE_TYPE}.elf 
    ${DEVICE_TYPE}
    arm_cortexM4lf_math
    )
endif()

#设置可执行文件输出路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

#设置 ELF 转换路径
set(ELF_FILE ${PROJECT_BINARY_DIR}/${DEVICE_TYPE}.elf)
set(HEX_FILE ${PROJECT_BINARY_DIR}/${DEVICE_TYPE}.hex)
set(BIN_FILE ${PROJECT_BINARY_DIR}/${DEVICE_TYPE}.bin)


if(${BOOT})
    #添加自定义命令实现 ELF 转换 hex 和 bin 文件
    add_custom_command(TARGET "${DEVICE_TYPE}.elf" POST_BUILD   
    COMMAND ${CMAKE_OBJCOPY} -Obinary ${ELF_FILE} ${BIN_FILE}
    COMMAND ${CMAKE_OBJCOPY} -Oihex ${ELF_FILE} ${HEX_FILE}
    COMMENT "Building ${PROJECT_NAME}.bin and ${PROJECT_NAME}.hex"
    COMMAND ${CMAKE_COMMAND} -E copy ${HEX_FILE} "${PROJECT_BINARY_DIR}/bin/${PROJECT_NAME}_Boot_V${BOOT_VERSION_MAJOR}.${BOOT_VERSION_MINOR}.${BOOT_VERSION_PATCH}.hex"
    COMMAND ${CMAKE_COMMAND} -E copy ${BIN_FILE} "${PROJECT_BINARY_DIR}/bin/${PROJECT_NAME}_Boot_V${BOOT_VERSION_MAJOR}.${BOOT_VERSION_MINOR}.${BOOT_VERSION_PATCH}.bin"
    COMMAND ${CMAKE_COMMAND} -E copy ${BIN_FILE} "${PROJECT_BINARY_DIR}/bin/${PROJECT_NAME}.bin"
    COMMAND ${CMAKE_COMMAND} -E copy ${ELF_FILE} "${PROJECT_BINARY_DIR}/bin/${PROJECT_NAME}.elf"
    COMMAND ${CMAKE_SIZE} --format=berkeley ${ELF_FILE} ${HEX_FILE}
    COMMENT "Invoking: Cross ARM GNU Print Size")
else()
    #添加自定义命令实现 ELF 转换 hex 和 bin 文件
    add_custom_command(TARGET "${DEVICE_TYPE}.elf" POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -Obinary ${ELF_FILE} ${BIN_FILE}
    COMMAND ${CMAKE_OBJCOPY} -Oihex ${ELF_FILE} ${HEX_FILE}
    COMMENT "Building ${PROJECT_NAME}.bin and ${PROJECT_NAME}.hex"
    COMMAND ${CMAKE_COMMAND} -E copy ${BIN_FILE} "${PROJECT_BINARY_DIR}/bin/${PROJECT_NAME}.bin"
    COMMAND ${CMAKE_COMMAND} -E copy ${ELF_FILE} "${PROJECT_BINARY_DIR}/bin/${PROJECT_NAME}.elf"
    COMMAND ${CMAKE_SIZE} --format=berkeley ${ELF_FILE} ${HEX_FILE}
    COMMENT "Invoking: Cross ARM GNU Print Size")
endif()


```

### task.json

VSCode 任务配置，包含清理、编译、下载等任务。

```
{
    "version": "2.0.0",
    "options": {
        "cwd": "${workspaceFolder}/build"
    },
    "tasks": [
        {
            "label": "clean",
            "type": "shell",
            "command": "rm * -r"
        },
        {
            "label": "cmake",
            "type": "shell",
            "command": "cmake",
            "args": [ 
                "-G",
                "MinGW Makefiles",
                "..",       
                "-DDEVICE_TYPE=STM32F407ZGTX",
                // "-DBOOT=ON",
                // "-DRELEASE=ON",
                "-DBOARD_TYPE=BOARD_TEST"  
            ],
            "dependsOn": [
                "clean",
            ]
        },

        {
            "label": "make",
            "type": "shell",
            "command": "make -j10",
            // "command": "make",
            "group": {
                "kind": "build",
                "isDefault": true
            }
        },
        {
            "label": "rebuild",
            "dependsOrder": "sequence",
            "dependsOn": [
                "cmake",
                "make"
            ],
            "problemMatcher": []
        },
        {
            "type": "shell",
            "label": "download boot",
            "command": "openocd",
            "args": [
                "-f",
                "../scripts/stlink-dap.cfg",
                "-f",
                "../scripts/openocd_target.cfg",
                // "-f",
                // "E:/project/scripts/cmsis-dap.cfg",
                // "-f",
                // "E:/project/scripts/openocd_target.cfg",
                "-c",
                "init",
                "-c",
                "halt",
                "-c",
                "program STM32F407ZGTX.bin 0x8000000",
                "-c",
                "reset",
                "-c",
                "shutdown"
            ],
            "group": "build",
            "dependsOn": "make"
        }
        ,
        {
            "type": "shell",
            "label": "download",
            "command": "openocd",
            "args": [
                "-f",
                "../scripts/stlink-dap.cfg",
                "-f",
                "../scripts/openocd_target.cfg",
                // "-f",
                // "E:/project/scripts/cmsis-dap.cfg",
                // "-f",
                // "E:/project/scripts/openocd_target.cfg",
                "-c",
                "init",
                "-c",
                "halt",
                "-c",
                "program STM32F407ZGTX.bin 0x8020000",
                "-c",
                "reset",
                "-c",
                "shutdown"
            ],
            "group": "build",
            "dependsOn": "make"
        }

    ]
}
```

### Cursor 点亮LED

打开 main.c 文件，添加程序入口点及基础配置。

```
#include "stm32f4xx.h"

int main(void)
{
    SystemInit();
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
    NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0);
    __enable_irq();
    __set_FAULTMASK(0);

    return 0;
}

```

呼出cursor面板 `CTRL+I` ，输入 `通过标准库添加呼吸灯，IO口选择PA5，呼吸频率为1S` ，点击 `生成代码` ，然后就变成了这个样子。

```     
#include "stm32f4xx.h"

// 延时函数
void delay(volatile uint32_t delay) {
    while (delay--) {
        __asm("nop");
    }
}

int main(void)
{
    // 初始化系统
    SystemInit();
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
    NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0);
    __enable_irq();
    __set_FAULTMASK(0);

    // 配置PA5为输出模式
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; // 使能GPIOA时钟
    GPIOA->MODER &= ~(3U << (5 * 2)); // 清除PA5的模式
    GPIOA->MODER |= (1U << (5 * 2)); // 设置PA5为输出模式

    while (1) {
        // 呼吸灯效果
        for (int i = 0; i < 1000; i++) {
            GPIOA->ODR |= (1U << 5); // 点亮LED
            delay(1000 - i); // 延时
        }
        for (int i = 0; i < 1000; i++) {
            GPIOA->ODR &= ~(1U << 5); // 熄灭LED
            delay(i); // 延时
        }
    }
}

```

显然，代码已经自动生成好了。但我想要的并不是直接寄存器操作，而是通过标准库操作。

在对话中输入 `不是直接寄存器操作，而是通过标准库操作` ，点击 `生成代码` ，然后就变成了我想要的样子。

```
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"

// 延时函数
void delay(volatile uint32_t delay) {
    while (delay--) {
        __asm("nop");
    }
}

int main(void)
{
    // 初始化系统
    SystemInit();
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
    NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0);
    __enable_irq();
    __set_FAULTMASK(0);

    // 配置PA5为输出模式
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); // 使能GPIOA时钟

    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5; // 选择PA5
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT; // 设置为输出模式
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz; // 设置速度
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP; // 设置为推挽输出
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL; // 不使用上拉或下拉
    GPIO_Init(GPIOA, &GPIO_InitStruct); // 初始化GPIOA

    while (1) {
        // 呼吸灯效果
        for (int i = 0; i < 1000; i++) {
            GPIO_SetBits(GPIOA, GPIO_Pin_5); // 点亮LED
            delay(1000 - i); // 延时
        }
        for (int i = 0; i < 1000; i++) {
            GPIO_ResetBits(GPIOA, GPIO_Pin_5); // 熄灭LED
            delay(i); // 延时
        }
    }
}
```



### 工程测试

**清理**

删除build目录下的所有文件

`终端->运行任务->clean`

输出内容如下

```
正在执行任务: rm * -r 

终端将被任务重用，按任意键关闭。 
```

**配置**

通过cmake 生成Makefile。该操作前会先清理build目录下的所有文件。

`终端->运行任务->cmake`

输出内容如下

```
正在执行任务: cmake -G 'MinGW Makefiles' .. -DDEVICE_TYPE=STM32F407ZGTX 

-- The C compiler identification is GNU 8.1.0
-- The CXX compiler identification is GNU 8.1.0
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - failed
-- Check for working C compiler: D:/Desktop/Software/mingw64/bin/gcc.exe
-- Check for working C compiler: D:/Desktop/Software/mingw64/bin/gcc.exe - works
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - failed
-- Check for working CXX compiler: D:/Desktop/Software/mingw64/bin/c++.exe
-- Check for working CXX compiler: D:/Desktop/Software/mingw64/bin/c++.exe - works
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- The ASM compiler identification is GNU
-- Found assembler: D:/Desktop/Software/gcc-arm-none-eabi-10.3-2021.10/bin/arm-none-eabi-gcc.exe
-- Configuring done (3.6s)
-- Generating done (0.1s)
-- Build files have been written to: E:/project/build
 *  终端将被任务重用，按任意键关闭。 
```

**编译**

通过make 编译工程。修改make -j10 指定编译线程数。减少编译时间。

`终端->运行任务->make`

输出内容如下

```
正在执行任务: make 

[  3%] Building C object Platform/CMakeFiles/platform.dir/CMSIS/Device/ST/STM32F4xx/Source/Templates/GNU/startup_stm32f407zgtx.s.obj
[  6%] Building C object Platform/CMakeFiles/platform.dir/CMSIS/Device/ST/STM32F4xx/Source/Templates/system_stm32f4xx.c.obj
[  9%] Building C object Platform/CMakeFiles/platform.dir/FW/STM32F4xx_StdPeriph_Driver/src/misc.c.obj
[ 12%] Building C object Platform/CMakeFiles/platform.dir/FW/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_adc.c.obj
[ 16%] Building C object Platform/CMakeFiles/platform.dir/FW/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_can.c.obj
[ 19%] Building C object Platform/CMakeFiles/platform.dir/FW/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_crc.c.obj
[ 22%] Building C object Platform/CMakeFiles/platform.dir/FW/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp.c.obj
[ 25%] Building C object Platform/CMakeFiles/platform.dir/FW/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dac.c.obj
[ 29%] Building C object Platform/CMakeFiles/platform.dir/FW/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dbgmcu.c.obj
[ 32%] Building C object Platform/CMakeFiles/platform.dir/FW/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dcmi.c.obj
[ 35%] Building C object Platform/CMakeFiles/platform.dir/FW/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dma.c.obj
[ 38%] Building C object Platform/CMakeFiles/platform.dir/FW/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_exti.c.obj
[ 41%] Building C object Platform/CMakeFiles/platform.dir/FW/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_flash.c.obj
[ 45%] Building C object Platform/CMakeFiles/platform.dir/FW/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_fsmc.c.obj
[ 48%] Building C object Platform/CMakeFiles/platform.dir/FW/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_gpio.c.obj
[ 51%] Building C object Platform/CMakeFiles/platform.dir/FW/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash.c.obj
[ 54%] Building C object Platform/CMakeFiles/platform.dir/FW/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_i2c.c.obj
[ 58%] Building C object Platform/CMakeFiles/platform.dir/FW/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_iwdg.c.obj
[ 61%] Building C object Platform/CMakeFiles/platform.dir/FW/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_pwr.c.obj
[ 64%] Building C object Platform/CMakeFiles/platform.dir/FW/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rcc.c.obj
[ 67%] Building C object Platform/CMakeFiles/platform.dir/FW/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rng.c.obj
[ 70%] Building C object Platform/CMakeFiles/platform.dir/FW/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rtc.c.obj
[ 74%] Building C object Platform/CMakeFiles/platform.dir/FW/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_sdio.c.obj
[ 77%] Building C object Platform/CMakeFiles/platform.dir/FW/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_spi.c.obj
[ 80%] Building C object Platform/CMakeFiles/platform.dir/FW/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_syscfg.c.obj
[ 83%] Building C object Platform/CMakeFiles/platform.dir/FW/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_tim.c.obj
[ 87%] Building C object Platform/CMakeFiles/platform.dir/FW/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_usart.c.obj
[ 90%] Building C object Platform/CMakeFiles/platform.dir/FW/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_wwdg.c.obj
[ 93%] Linking C static library ..\lib\libSTM32F407ZGTX.a
[ 93%] Built target platform
[ 96%] Building C object Application/CMakeFiles/STM32F407ZGTX.elf.dir/main.c.obj
[100%] Linking C executable ..\STM32F407ZGTX.elf
Invoking: Cross ARM GNU Print Size
   text    data     bss     dec     hex filename
  15236     472    2096   17804    458c E:/project/build/STM32F407ZGTX.elf
      0   15708       0   15708    3d5c E:/project/build/STM32F407ZGTX.hex
[100%] Built target STM32F407ZGTX.elf
终端将被任务重用，按任意键关闭。 

```

**重新编译**

`终端->运行任务->rebuild` 实际上是 `终端->运行任务->cmake` 和 `终端->运行任务->make` 的组合

**下载**

`终端->运行任务->download`

<span style="color:red;">注意修改CMakeLists.txt 后，需要重新编译。即重新生成Makefile。</span>

## 仿真

这里仿真器我选择的是 stlink

选择运行与调试->Cortex Debug STM32 或者 ***F5*** 选择上次的仿真进行

**使用仿真需要工程RELEASE改为DEBUG**

## 项目地址
https://github.com/DanceMonkey2020/stm32_project.git

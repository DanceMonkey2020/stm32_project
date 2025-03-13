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

## FreeRTOS 


以下内容摘选自正点原子 **《FreeRTOS 开发指南》**

```
为什么选择 FreeRTOS？
上面我们说了 RTOS 类操作系统有很多，那为什么要选择FreeRTOS呢？在µC/OS 教程中，
我们说过学习 RTOS 首选 µC/OS，因为 µC/OS 的资料很多，尤其是中文资料！相比之下 FreeRTOS
的资料少，而且大多数是英文的，那为什么还要选择学习和使用 FreeRTOS 呢？主要原因有以
下的几点：
1．免费。这是很重要的一点，因为在做产品的时候是要考虑产品的成本的，显而易见的
FreeRTOS 操作系统就是一个很好的选择，当然了，也可以选择其他免费的 RTOS 操作系统。
2．简单。这一点单从 FreeRTOS 操作系统的文件数量上，就能感觉到，这个在我们后面的
具体学习中就会看到，和 µC/OS 操作系统系统相比要少很多！
3．使用广泛。许多半导体厂商和软件厂商都在其产品中使用了 FreeRTOS 操作系统。比如，
许多的半导体厂商都会在其产品的 SDK 包中使用 FreeRTOS 操作系统，尤其是涉及 Wi-Fi、蓝
牙等这些带协议栈的芯片或模块；著名的 GUI 设计软件库 TouchGFX 在其软件的应用例程中使
用了 FreeRTOS 操作系统；ST 公司也在其 STM32Cube 生态系统中加入了对 FreeRTOS 操作系
统的支持。
4．资料齐全。在 FreeRTOS 操作系统的官网（https://www.freertos.org/）上，提供了大量的
FreeRTOS 操作系统的相关文档及例程源码。但是美中不足的是，提供的文档都是英文文档，查
看这些资料要求有一定的英语功底。
5．可移植性强。FreeRTOS 操作系统支持多种不同架构的不同型号的处理器，比如 STM32
系列的 F1、F4、F7 和 H7 等都可以移植 FreeRTOS，这极大的方便了我们学习和使用 FreeRTOS
操作系统。
```
**补充下FreeRTOS 中文文档已经很全面了** 

### 移植(复制)

这里选择了较新的FreeRTOS 内核版本 **V11.1.0**

源码下载地址 https://www.freertos.org/zh-cn-cmn-s

移植(复制)过程比较容易，将文件复制过来，并在CMakeLists.txt中引用适配的文件即可，具体需要的文件参考FreeRTOS-Kernel目录。

主要在于FreeRTOSConfig.h的配置，以下为修改处

- 修改主频及滴答周期等
    ```
    #define configCPU_CLOCK_HZ    ( ( unsigned long ) 168000000 )
    #define configTICK_RATE_HZ                         1000
    ```

- 添加中断宏定义、已避免修改asm文件、在结尾处添加如下    
    ```
    #define vPortSVCHandler    SVC_Handler
    #define xPortPendSVHandler PendSV_Handler
    #define xPortSysTickHandler SysTick_Handler
    ```

- 更改正确的中断级别、否则会卡在断言处，比如 port.c configASSERT( ucMaxSysCallPriority );
    ```
    #define configMAX_SYSCALL_INTERRUPT_PRIORITY    ( 0x50 )  
    #define configMIN_INTERRUPT_PRIORITY            ( 0xFF )  
    #define configKERNEL_INTERRUPT_PRIORITY         ( configMIN_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )
    #define configPRIO_BITS                         4
    ```
- 修改合适的大小堆栈内存等
- 根据需求选择钩子函数

完整的FreeRTOSConfig.h内容如下,并修改了中文注释
```
/*
 * FreeRTOS 内核 V11.1.0
 * 版权所有 (C) 2021 Amazon.com, Inc. 或其附属公司。保留所有权利。
 *
 * SPDX-License-Identifier: MIT
 *
 * 特此免费授予任何获得本软件及相关文档文件（"软件"）副本的人，允许其不受限制地使用、复制、修改、合并、出版、分发、再许可和/或销售本软件的副本，并允许向其提供本软件的人这样做，前提是满足以下条件：
 *
 * 上述版权声明和本许可声明应包含在所有副本或实质性部分的本软件中。
 *
 * 本软件是按"原样"提供的，不附有任何种类的明示或暗示的担保，包括但不限于对适销性、特定用途的适用性和不侵权的担保。在任何情况下，作者或版权持有人均不对因使用本软件或其他交易而引起的任何索赔、损害或其他责任承担责任，无论是在合同、侵权或其他方面。
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 */

/*******************************************************************************
 * 本文件提供了一个示例 FreeRTOSConfig.h 头文件，包括每个配置项的简要说明。
 * 在线和参考文档提供了更多信息。
 * https://www.freertos.org/a00110.html
 *
 * 用方括号（'[' 和 ']'）括起来的常量值必须在本文件构建之前完成。
 *
 * 如果有可用的 RTOS 端口，请使用随附的 FreeRTOSConfig.h，而不是此通用文件。
 ******************************************************************************/

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/******************************************************************************/
/* 硬件描述相关定义。 *******************************************************/
/******************************************************************************/

/* 在大多数情况下，configCPU_CLOCK_HZ 必须设置为驱动用于生成内核周期性滴答中断的外设的时钟频率。
 * 默认值设置为 20MHz，匹配 QEMU 演示设置。您的应用程序肯定需要不同的值，因此请正确设置此值。
 * 这通常，但并不总是，等于主系统时钟频率。 */
#define configCPU_CLOCK_HZ    ( ( unsigned long ) 168000000 )

/* configSYSTICK_CLOCK_HZ 是 ARM Cortex-M 端口的可选参数。
 *
 * 默认情况下，ARM Cortex-M 端口从 Cortex-M SysTick 定时器生成 RTOS 滴答中断。
 * 大多数 Cortex-M MCU 以与 MCU 本身相同的频率运行 SysTick 定时器 - 当这种情况发生时，configSYSTICK_CLOCK_HZ 不需要，应该保持未定义。
 * 如果 SysTick 定时器以与 MCU 核心不同的频率时钟，则将 configCPU_CLOCK_HZ 设置为 MCU 时钟频率，正常情况下，configSYSTICK_CLOCK_HZ 设置为 SysTick 时钟频率。
 * 如果保持未定义，则不使用。 */
/*
 #define configSYSTICK_CLOCK_HZ                  [平台特定]
 */

/******************************************************************************/
/* 调度行为相关定义。 *******************************************************/
/******************************************************************************/

/* configTICK_RATE_HZ 设置滴答中断的频率（以 Hz 为单位），通常从 configCPU_CLOCK_HZ 值计算得出。 */
#define configTICK_RATE_HZ                         1000

/* 将 configUSE_PREEMPTION 设置为 1 以使用抢占式调度。将 configUSE_PREEMPTION 设置为 0 以使用协作调度。
 * 参见 https://www.freertos.org/single-core-amp-smp-rtos-scheduling.html。 */
#define configUSE_PREEMPTION                       1

/* 将 configUSE_TIME_SLICING 设置为 1 以使调度程序在每个滴答中断时在相同优先级的就绪状态任务之间切换。
 * 将 configUSE_TIME_SLICING 设置为 0 以防止调度程序仅因为有滴答中断而在就绪状态任务之间切换。
 * 参见 https://freertos.org/single-core-amp-smp-rtos-scheduling.html。 */
#define configUSE_TIME_SLICING                     0

/* 将 configUSE_PORT_OPTIMISED_TASK_SELECTION 设置为 1 以使用针对目标硬件指令集优化的算法选择下一个要运行的任务 -
 * 通常使用计数前导零汇编指令。设置为 0 以使用适用于所有 FreeRTOS 端口的通用 C 算法选择下一个要运行的任务。
 * 不是所有 FreeRTOS 端口都有此选项。如果保持未定义，则默认为 0。 */
#define configUSE_PORT_OPTIMISED_TASK_SELECTION    0

/* 将 configUSE_TICKLESS_IDLE 设置为 1 以使用低功耗无滴答模式。将 0 设置为始终保持滴答中断运行。
 * 不是所有 FreeRTOS 端口都支持无滴答模式。参见 https://www.freertos.org/low-power-tickless-rtos.html
 * 如果保持未定义，则默认为 0。 */
#define configUSE_TICKLESS_IDLE                    0

/* configMAX_PRIORITIES 设置可用任务优先级的数量。任务可以分配优先级 0 到 (configMAX_PRIORITIES - 1)。
 * 0 是最低优先级。 */
#define configMAX_PRIORITIES                       5

/* configMINIMAL_STACK_SIZE 定义空闲任务使用的堆栈大小（以字为单位，而不是以字节为单位！）。
 * 内核不使用此常量用于其他目的。演示应用程序使用该常量使演示在不同硬件架构之间具有一定的可移植性。 */
#define configMINIMAL_STACK_SIZE                   128

/* configMAX_TASK_NAME_LEN 设置任务人类可读名称的最大长度（以字符为单位）。包括 NULL 终止符。 */
#define configMAX_TASK_NAME_LEN                    16

/* 时间以"滴答"为单位测量 - 这是自 RTOS 内核启动以来滴答中断执行的次数。
 * 滴答计数保存在 TickType_t 类型的变量中。
 *
 * configTICK_TYPE_WIDTH_IN_BITS 控制 TickType_t 的类型（因此是位宽）：
 *
 * 将 configTICK_TYPE_WIDTH_IN_BITS 定义为 TICK_TYPE_WIDTH_16_BITS 会导致 TickType_t 被定义（typedef）为无符号 16 位类型。
 *
 * 将 configTICK_TYPE_WIDTH_IN_BITS 定义为 TICK_TYPE_WIDTH_32_BITS 会导致 TickType_t 被定义（typedef）为无符号 32 位类型。
 *
 * 将 configTICK_TYPE_WIDTH_IN_BITS 定义为 TICK_TYPE_WIDTH_64_BITS 会导致 TickType_t 被定义（typedef）为无符号 64 位类型。 */
#define configTICK_TYPE_WIDTH_IN_BITS              TICK_TYPE_WIDTH_32_BITS

/* 将 configIDLE_SHOULD_YIELD 设置为 1 以使空闲任务在有空闲优先级（优先级 0）应用任务可以运行时让出。
 * 将其设置为 0 以使空闲任务使用其所有时间片。如果保持未定义，则默认为 1。 */
#define configIDLE_SHOULD_YIELD                    1

/* 每个任务都有一个任务通知数组。
 * configTASK_NOTIFICATION_ARRAY_ENTRIES 设置数组中的索引数量。
 * 参见 https://www.freertos.org/RTOS-task-notifications.html 默认为 1。 */
#define configTASK_NOTIFICATION_ARRAY_ENTRIES      1

/* configQUEUE_REGISTRY_SIZE 设置可以从队列注册表引用的队列和信号量的最大数量。
 * 仅在使用内核感知调试器时需要。默认为 0，如果保持未定义。 */
#define configQUEUE_REGISTRY_SIZE                  8

/* 将 configENABLE_BACKWARD_COMPATIBILITY 设置为 1 以将旧版本 FreeRTOS 的函数名称和数据类型映射到其最新等效项。
 * 如果保持未定义，则默认为 1。 */
#define configENABLE_BACKWARD_COMPATIBILITY        0

/* 每个任务都有自己的指针数组，可以用作线程本地存储。
 * configNUM_THREAD_LOCAL_STORAGE_POINTERS 设置数组中的索引数量。
 * 参见 https://www.freertos.org/thread-local-storage-pointers.html 默认为 0，如果保持未定义。 */
#define configNUM_THREAD_LOCAL_STORAGE_POINTERS    0

/* 当 configUSE_MINI_LIST_ITEM 设置为 0 时，MiniListItem_t 和 ListItem_t 是相同的。
 * 当 configUSE_MINI_LIST_ITEM 设置为 1 时，MiniListItem_t 包含比 ListItem_t 少 3 个字段，这样可以节省一些 RAM，
 * 但代价是违反某些编译器依赖于优化的严格别名规则。如果保持未定义，则默认为 1。 */
#define configUSE_MINI_LIST_ITEM                   1

/* 设置用于 xTaskCreate() 的参数的类型，该参数指定正在创建的任务的堆栈大小。
 * 相同的类型用于在各种其他 API 调用中返回有关堆栈使用的信息。如果保持未定义，则默认为 size_t。 */
#define configSTACK_DEPTH_TYPE                     size_t

/* configMESSAGE_BUFFER_LENGTH_TYPE 设置用于存储写入 FreeRTOS 消息缓冲区的每条消息的长度的类型（长度也写入消息缓冲区）。
 * 如果保持未定义，则默认为 size_t - 但如果消息从未超过可以用 uint8_t 存储的长度，则可能会浪费空间。 */
#define configMESSAGE_BUFFER_LENGTH_TYPE           size_t

/* 如果 configHEAP_CLEAR_MEMORY_ON_FREE 设置为 1，则使用 pvPortMalloc() 分配的内存块在使用 vPortFree() 释放时将被清零（即设置为零）。
 * 如果保持未定义，则默认为 0。 */
#define configHEAP_CLEAR_MEMORY_ON_FREE            1

/* vTaskList 和 vTaskGetRunTimeStats API 将缓冲区作为参数，并假定缓冲区的长度为 configSTATS_BUFFER_MAX_LENGTH。
 * 如果保持未定义，则默认为 0xFFFF。
 * 新应用程序建议使用 vTaskListTasks 和 vTaskGetRunTimeStatistics API，而不是使用 vTaskList 和 vTaskGetRunTimeStats API，并显式提供缓冲区的长度，以避免内存损坏。 */
#define configSTATS_BUFFER_MAX_LENGTH              0xFFF

/* 将 configUSE_NEWLIB_REENTRANT 设置为 1 以为每个任务分配一个 newlib reent 结构。
 * 将 0 设置为不支持 newlib reent 结构。如果保持未定义，则默认为 0。
 *
 * 注意，因应广泛需求已包含 newlib 支持，但 FreeRTOS 维护者并未使用或测试。
 * FreeRTOS 对 resulting newlib 操作不负责。用户必须熟悉 newlib，并提供必要的系统范围实现。注意，在撰写本文时，当前 newlib 设计实现了一个系统范围的 malloc()，必须提供锁。 */
#define configUSE_NEWLIB_REENTRANT                 0

/******************************************************************************/
/* 软件定时器相关定义。 *****************************************************/
/******************************************************************************/

/* 将 configUSE_TIMERS 设置为 1 以在构建中包含软件定时器功能。
 * 将 0 设置为从构建中排除软件定时器功能。必须在构建中包含 FreeRTOS/source/timers.c 源文件，如果 configUSE_TIMERS 设置为 1。
 * 如果保持未定义，则默认为 0。参见 https://www.freertos.org/RTOS-software-timer.html。 */
#define configUSE_TIMERS                1

/* configTIMER_TASK_PRIORITY 设置定时器任务使用的优先级。仅在 configUSE_TIMERS 设置为 1 时使用。
 * 定时器任务是标准 FreeRTOS 任务，因此其优先级与其他任务一样设置。
 * 参见 https://www.freertos.org/RTOS-software-timer-service-daemon-task.html 仅在 configUSE_TIMERS 设置为 1 时使用。 */
#define configTIMER_TASK_PRIORITY       ( configMAX_PRIORITIES - 1 )

/* configTIMER_TASK_STACK_DEPTH 设置分配给定时器任务的堆栈大小（以字为单位，而不是以字节为单位！）。
 * 定时器任务是标准 FreeRTOS 任务。参见 https://www.freertos.org/RTOS-software-timer-service-daemon-task.html
 * 仅在 configUSE_TIMERS 设置为 1 时使用。 */
#define configTIMER_TASK_STACK_DEPTH    configMINIMAL_STACK_SIZE

/* configTIMER_QUEUE_LENGTH 设置用于向定时器任务发送命令的队列的长度（队列可以容纳的离散项目数量）。
 * 参见 https://www.freertos.org/RTOS-software-timer-service-daemon-task.html 仅在 configUSE_TIMERS 设置为 1 时使用。 */
#define configTIMER_QUEUE_LENGTH        10

/******************************************************************************/
/* 事件组相关定义。 *********************************************************/
/******************************************************************************/

/* 将 configUSE_EVENT_GROUPS 设置为 1 以在构建中包含事件组功能。
 * 将 0 设置为从构建中排除事件组功能。必须在构建中包含 FreeRTOS/source/event_groups.c 源文件，如果 configUSE_EVENT_GROUPS 设置为 1。
 * 如果保持未定义，则默认为 1。 */
#define configUSE_EVENT_GROUPS    1

/******************************************************************************/
/* 流缓冲区相关定义。 *******************************************************/
/******************************************************************************/

/* 将 configUSE_STREAM_BUFFERS 设置为 1 以在构建中包含流缓冲区功能。
 * 将 0 设置为从构建中排除流缓冲区功能。必须在构建中包含 FreeRTOS/source/stream_buffer.c 源文件，如果 configUSE_STREAM_BUFFERS 设置为 1。
 * 如果保持未定义，则默认为 1。 */
#define configUSE_STREAM_BUFFERS    1

/******************************************************************************/
/* 内存分配相关定义。 *******************************************************/
/******************************************************************************/

/* 将 configSUPPORT_STATIC_ALLOCATION 设置为 1 以在构建中包含 FreeRTOS API 函数，这些函数使用静态分配的内存创建 FreeRTOS 对象（任务、队列等）。
 * 将 0 设置为从构建中排除创建静态分配对象的能力。如果保持未定义，则默认为 0。
 * 参见 https://www.freertos.org/Static_Vs_Dynamic_Memory_Allocation.html。 */
#define configSUPPORT_STATIC_ALLOCATION              1

/* 将 configSUPPORT_DYNAMIC_ALLOCATION 设置为 1 以在构建中包含 FreeRTOS API 函数，这些函数使用动态分配的内存创建 FreeRTOS 对象（任务、队列等）。
 * 将 0 设置为从构建中排除创建动态分配对象的能力。如果保持未定义，则默认为 1。
 * 参见 https://www.freertos.org/Static_Vs_Dynamic_Memory_Allocation.html。 */
#define configSUPPORT_DYNAMIC_ALLOCATION             1

/* 设置 FreeRTOS 堆的总大小（以字节为单位），当 heap_1.c、heap_2.c 或 heap_4.c 包含在构建中时。
 * 此值默认为 4096 字节，但必须根据每个应用程序进行调整。
 * 注意，堆将出现在 .bss 段中。参见 https://www.freertos.org/a00111.html。 */
#define configTOTAL_HEAP_SIZE                         ( 32 * 1024 ) 

/* 将 configAPPLICATION_ALLOCATED_HEAP 设置为 1 以让应用程序分配用作 FreeRTOS 堆的数组。
 * 将 0 设置为让链接器分配用作 FreeRTOS 堆的数组。如果保持未定义，则默认为 0。 */
#define configAPPLICATION_ALLOCATED_HEAP             0

/* 将 configSTACK_ALLOCATION_FROM_SEPARATE_HEAP 设置为 1 以使任务堆栈从 FreeRTOS 堆以外的地方分配。
 * 如果您希望确保堆栈保存在快速内存中，这很有用。将 0 设置为使任务堆栈来自标准 FreeRTOS 堆。
 * 如果设置为 1，则应用程序编写者必须提供 pvPortMallocStack() 和 vPortFreeStack() 的实现。
 * 如果保持未定义，则默认为 0。 */
#define configSTACK_ALLOCATION_FROM_SEPARATE_HEAP    0

/* 将 configENABLE_HEAP_PROTECTOR 设置为 1 以启用边界检查和对 heap_4.c 和 heap_5.c 中内部堆块指针的混淆，以帮助捕获指针损坏。
 * 如果保持未定义，则默认为 0。 */
#define configENABLE_HEAP_PROTECTOR                  0

/******************************************************************************/
/* 中断嵌套行为配置。 *******************************************************/
/******************************************************************************/

// /* configKERNEL_INTERRUPT_PRIORITY 设置滴答和上下文切换执行中断的优先级。
//  * 不是所有 FreeRTOS 端口都支持。参见 https://www.freertos.org/RTOS-Cortex-M3-M4.html 以获取特定于 ARM Cortex-M 设备的信息。 */
// #define configKERNEL_INTERRUPT_PRIORITY          0

// /* configMAX_SYSCALL_INTERRUPT_PRIORITY 设置 FreeRTOS API 调用不得进行的中断优先级。
//  * 高于此优先级的中断永远不会被禁用，因此不会被 RTOS 活动延迟。默认值设置为最高中断优先级（0）。
//  * 不是所有 FreeRTOS 端口都支持。参见 https://www.freertos.org/RTOS-Cortex-M3-M4.html 以获取特定于 ARM Cortex-M 设备的信息。 */
// #define configMAX_SYSCALL_INTERRUPT_PRIORITY     5

// /* configMAX_API_CALL_INTERRUPT_PRIORITY 的另一个名称 - 名称取决于 FreeRTOS 端口。 */
// #define configMAX_API_CALL_INTERRUPT_PRIORITY    0


/* 设置最大系统调用中断优先级 */
#define configMAX_SYSCALL_INTERRUPT_PRIORITY    ( 0x50 )  // 修改为一个非零值

/* 设置最小中断优先级 */
#define configMIN_INTERRUPT_PRIORITY            ( 0xFF )  // 最低优先级

/* 设置内核中断优先级 */
#define configKERNEL_INTERRUPT_PRIORITY         ( configMIN_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )

/* PendSV 中断优先级 */
#define configPENDSV_PRIORITY                   ( configKERNEL_INTERRUPT_PRIORITY )

/* SysTick 中断优先级 */
#define configTICK_PRIORITY                     ( configKERNEL_INTERRUPT_PRIORITY )

/* 添加优先级位数定义 */
#define configPRIO_BITS                         4

/******************************************************************************/
/* 钩子和回调函数相关定义。 ***********************************************/
/******************************************************************************/

/* 将以下 configUSE_* 常量设置为 1 以在构建中包含命名钩子功能。
 * 将 0 设置为排除钩子功能。应用程序编写者负责提供设置为 1 的任何钩子函数。
 * 参见 https://www.freertos.org/a00016.html。 */
#define configUSE_IDLE_HOOK                   0
#define configUSE_TICK_HOOK                   0
#define configUSE_MALLOC_FAILED_HOOK          0
#define configUSE_DAEMON_TASK_STARTUP_HOOK    0

/* 将 configUSE_SB_COMPLETED_CALLBACK 设置为 1 以为每个流缓冲区或消息缓冲区实例提供发送和接收完成回调。
 * 当选项设置为 1，可以使用 API xStreamBufferCreateWithCallback() 和 xStreamBufferCreateStaticWithCallback()（以及消息缓冲区的类似 API）创建带有应用程序提供的回调的流缓冲区或消息缓冲区实例。
 * 如果保持未定义，则默认为 0。 */
#define configUSE_SB_COMPLETED_CALLBACK       0

/* 将 configCHECK_FOR_STACK_OVERFLOW 设置为 1 或 2，以便 FreeRTOS 在上下文切换时检查堆栈溢出。
 * 将 0 设置为不检查堆栈溢出。如果 configCHECK_FOR_STACK_OVERFLOW 设置为 1，则检查仅在任务的上下文保存到其堆栈时查看堆栈指针是否超出边界 - 这很快但效果不佳。
 * 如果 configCHECK_FOR_STACK_OVERFLOW 设置为 2，则检查查看写入任务堆栈末尾的模式是否被覆盖。
 * 这较慢，但会捕获大多数（但不是全部）堆栈溢出。应用程序编写者必须在 configCHECK_FOR_STACK_OVERFLOW 设置为 1 时提供堆栈溢出回调。
 * 参见 https://www.freertos.org/Stacks-and-stack-overflow-checking.html 如果保持未定义，则默认为 0。 */
#define configCHECK_FOR_STACK_OVERFLOW        0

/******************************************************************************/
/* 运行时和任务统计收集相关定义。 ***************************************/
/******************************************************************************/

/* 将 configGENERATE_RUN_TIME_STATS 设置为 1 以使 FreeRTOS 收集每个任务使用的处理时间的数据。
 * 将 0 设置为不收集数据。应用程序编写者需要提供时钟源（如果设置为 1）。
 * 如果保持未定义，则默认为 0。参见 https://www.freertos.org/rtos-run-time-stats.html。 */
#define configGENERATE_RUN_TIME_STATS           0

/* 将 configUSE_TRACE_FACILITY 设置为 1 以包括额外的任务结构成员，这些成员用于跟踪和可视化功能和工具。
 * 将 0 设置为从结构中排除额外信息。如果保持未定义，则默认为 0。 */
#define configUSE_TRACE_FACILITY                0

/* 将 configUSE_STATS_FORMATTING_FUNCTIONS 设置为 1 以在构建中包含 vTaskList() 和 vTaskGetRunTimeStats() 函数。
 * 将 0 设置为从构建中排除这些函数。这两个函数引入了字符串格式化函数的依赖关系，这些函数在其他情况下将不存在 - 因此它们被分开。
 * 如果保持未定义，则默认为 0。 */
#define configUSE_STATS_FORMATTING_FUNCTIONS    0

/******************************************************************************/
/* 协程相关定义。 ***********************************************************/
/******************************************************************************/

/* 将 configUSE_CO_ROUTINES 设置为 1 以在构建中包含协程功能，或 0 以省略协程功能。
 * 要包括协程，必须在项目中包含 croutine.c。如果保持未定义，则默认为 0。 */
#define configUSE_CO_ROUTINES              0

/* configMAX_CO_ROUTINE_PRIORITIES 定义可用于应用程序协程的优先级数量。
 * 任何数量的协程可以共享相同的优先级。如果保持未定义，则默认为 0。 */
#define configMAX_CO_ROUTINE_PRIORITIES    1

/******************************************************************************/
/* 调试辅助功能。 ***********************************************************/
/******************************************************************************/

/* configASSERT() 的语义与标准 C 断言相同。
 * 它可以被定义为在断言失败时采取某种操作，或者根本不定义（即注释掉或删除定义）以完全删除断言。 */
#define configASSERT( x )         \
    if( ( x ) == 0 )              \
    {                             \
        taskDISABLE_INTERRUPTS(); \
        for( ; ; )                \
        ;                         \
    }

/******************************************************************************/
/* FreeRTOS MPU 特定定义。 ***************************************************/
/******************************************************************************/

/* 如果 configINCLUDE_APPLICATION_DEFINED_PRIVILEGED_FUNCTIONS 设置为 1，则应用程序编写者可以提供以特权模式执行的函数。
 * 参见: https://www.freertos.org/a00110.html#configINCLUDE_APPLICATION_DEFINED_PRIVILEGED_FUNCTIONS
 * 如果保持未定义，则默认为 0。仅用于 FreeRTOS Cortex-M MPU 端口，而不是标准 ARMv7-M Cortex-M 端口。 */
#define configINCLUDE_APPLICATION_DEFINED_PRIVILEGED_FUNCTIONS    0

/* 将 configTOTAL_MPU_REGIONS 设置为目标硬件上实现的 MPU 区域的数量。
 * 通常为 8 或 16。仅用于 FreeRTOS Cortex-M MPU 端口，而不是标准 ARMv7-M Cortex-M 端口。
 * 如果保持未定义，则默认为 8。 */
#define configTOTAL_MPU_REGIONS                                   8

/* configTEX_S_C_B_FLASH 允许应用程序编写者覆盖覆盖 Flash 的 MPU 区域的 TEX、可共享（S）、可缓存（C）和可缓冲（B）位的默认值。
 * 如果保持未定义，则默认为 0x07UL（这意味着 TEX=000，S=1，C=1，B=1）。仅用于 FreeRTOS Cortex-M MPU 端口，而不是标准 ARMv7-M Cortex-M 端口。 */
#define configTEX_S_C_B_FLASH                                     0x07UL

/* configTEX_S_C_B_SRAM 允许应用程序编写者覆盖覆盖 RAM 的 MPU 区域的 TEX、可共享（S）、可缓存（C）和可缓冲（B）位的默认值。
 * 如果保持未定义，则默认为 0x07UL（这意味着 TEX=000，S=1，C=1，B=1）。仅用于 FreeRTOS Cortex-M MPU 端口，而不是标准 ARMv7-M Cortex-M 端口。 */
#define configTEX_S_C_B_SRAM                                      0x07UL

/* 将 configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY 设置为 0 以防止任何特权提升源自内核代码本身以外的地方。
 * 将 1 设置为允许应用程序任务提升特权。如果保持未定义，则默认为 1。
 * 仅用于 FreeRTOS Cortex-M MPU 端口，而不是标准 ARMv7-M Cortex-M 端口。 */
#define configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY               1

/* 将 configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS 设置为 1 以允许非特权任务进入临界区（有效地屏蔽中断）。
 * 将 0 设置为防止非特权任务进入临界区。如果保持未定义，则默认为 1。
 * 仅用于 FreeRTOS Cortex-M MPU 端口，而不是标准 ARMv7-M Cortex-M 端口。 */
#define configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS                0

/* FreeRTOS 内核版本 10.6.0 引入了一个新的 v2 MPU 包装器，即 mpu_wrappers_v2.c。
 * 将 configUSE_MPU_WRAPPERS_V1 设置为 0 以使用新的 v2 MPU 包装器。
 * 将 configUSE_MPU_WRAPPERS_V1 设置为 1 以使用旧的 v1 MPU 包装器（mpu_wrappers.c）。
 * 如果保持未定义，则默认为 0。 */
#define configUSE_MPU_WRAPPERS_V1                                 0

/* 使用 v2 MPU 包装器时，将 configPROTECTED_KERNEL_OBJECT_POOL_SIZE 设置为内核对象的总数，
 * 包括任务、队列、信号量、互斥锁、事件组、定时器、流缓冲区和消息缓冲区。
 * 应用程序在任何时候都不能拥有超过 configPROTECTED_KERNEL_OBJECT_POOL_SIZE 的内核对象。 */
#define configPROTECTED_KERNEL_OBJECT_POOL_SIZE                   10

/* 使用 v2 MPU 包装器时，将 configSYSTEM_CALL_STACK_SIZE 设置为系统调用堆栈的大小（以字为单位）。
 * 每个任务都有一个静态分配的内存缓冲区，该缓冲区用于作为执行系统调用的堆栈。
 * 例如，如果 configSYSTEM_CALL_STACK_SIZE 定义为 128，并且应用程序中有 10 个任务，则用于系统调用堆栈的总内存为 128 * 10 = 1280 字。 */
#define configSYSTEM_CALL_STACK_SIZE                              128

/* 使用 v2 MPU 包装器时，将 configENABLE_ACCESS_CONTROL_LIST 设置为 1 以启用访问控制列表（ACL）功能。
 * 启用 ACL 功能后，默认情况下，非特权任务无法访问任何内核对象，除了它自己。
 * 应用程序编写者需要使用提供的 API 显式授予非特权任务访问所需的内核对象。
 * 如果保持未定义，则默认为 0。 */
#define configENABLE_ACCESS_CONTROL_LIST                          1

/******************************************************************************/
/* SMP（对称多处理）特定配置定义。 ***************************************/
/******************************************************************************/

/* 将 configNUMBER_OF_CORES 设置为可用处理器核心的数量。
 * 如果保持未定义，则默认为 1。 */
/*
 #define configNUMBER_OF_CORES                     [可用核心数量]
 */

/* 使用 SMP（即 configNUMBER_OF_CORES 大于 1）时，将 configRUN_MULTIPLE_PRIORITIES 设置为 0 以允许多个任务仅在它们没有相同优先级时同时运行，
 * 从而保持较低优先级任务在较高优先级任务能够运行时不会运行的范例。
 * 如果 configRUN_MULTIPLE_PRIORITIES 设置为 1，则具有不同优先级的多个任务可以同时运行 - 因此较高和较低优先级任务可以在不同核心上同时运行。 */
#define configRUN_MULTIPLE_PRIORITIES             0

/* 使用 SMP（即 configNUMBER_OF_CORES 大于 1）时，将 configUSE_CORE_AFFINITY 设置为 1 以启用核心亲和性功能。
 * 启用核心亲和性功能后，可以使用 vTaskCoreAffinitySet 和 vTaskCoreAffinityGet API 设置和检索任务可以运行的核心。
 * 如果 configUSE_CORE_AFFINITY 设置为 0，则 FreeRTOS 调度程序可以自由地在任何可用核心上运行任何任务。 */
#define configUSE_CORE_AFFINITY                   0

/* 使用 SMP（即 configNUMBER_OF_CORES 大于 1）时，将 configTASK_DEFAULT_CORE_AFFINITY 设置为更改未指定亲和性掩码的任务的默认核心亲和性掩码。
 * 将定义设置为 1 将使此类任务在核心 0 上运行，将定义设置为 (1 << portGET_CORE_ID()) 将使此类任务在当前核心上运行。
 * 此配置值很有用，如果在核心之间交换任务不受支持（例如 Tricore）或如果需要控制遗留代码。默认为 tskNO_AFFINITY，如果保持未定义。 */
#define configTASK_DEFAULT_CORE_AFFINITY          tskNO_AFFINITY

/* 使用 SMP（即 configNUMBER_OF_CORES 大于 1）时，如果 configUSE_TASK_PREEMPTION_DISABLE 设置为 1，则可以使用 vTaskPreemptionDisable 和 vTaskPreemptionEnable API 将单个任务设置为抢占式或协作模式。 */
#define configUSE_TASK_PREEMPTION_DISABLE         0

/* 使用 SMP（即 configNUMBER_OF_CORES 大于 1）时，将 configUSE_PASSIVE_IDLE_HOOK 设置为 1 以允许应用程序编写者使用被动空闲任务钩子添加后台功能，而无需单独的任务开销。
 * 如果保持未定义，则默认为 0。 */
#define configUSE_PASSIVE_IDLE_HOOK               0

/* 使用 SMP（即 configNUMBER_OF_CORES 大于 1），configTIMER_SERVICE_TASK_CORE_AFFINITY 允许应用程序编写者设置 RTOS 守护/定时器服务任务的核心亲和性。
 * 如果保持未定义，则默认为 tskNO_AFFINITY。 */
#define configTIMER_SERVICE_TASK_CORE_AFFINITY    tskNO_AFFINITY


/******************************************************************************/
/* ARMv8-M 安全侧端口相关定义。 *********************************************/
/******************************************************************************/

/* secureconfigMAX_SECURE_CONTEXTS 定义可以调用 ARMv8-M 芯片安全侧的任务的最大数量。
 * 仅用于其他端口。 */
#define secureconfigMAX_SECURE_CONTEXTS        5

/* 定义内核提供的实现 vApplicationGetIdleTaskMemory() 和 vApplicationGetTimerTaskMemory()，
 * 以提供空闲任务和定时器任务使用的内存。
 * 应用程序可以通过将 configKERNEL_PROVIDED_STATIC_MEMORY 设置为 0 或保持未定义来提供自己的实现。 */
#define configKERNEL_PROVIDED_STATIC_MEMORY    1

/******************************************************************************/
/* ARMv8-M 端口特定配置定义。 ***********************************************/
/******************************************************************************/

/* 当在非安全侧运行 FreeRTOS 时，将 configENABLE_TRUSTZONE 设置为 1 以启用 FreeRTOS ARMv8-M 端口中的 TrustZone 支持，
 * 允许非安全 FreeRTOS 任务调用从安全侧导出的（非安全可调用）函数。 */
#define configENABLE_TRUSTZONE            1

/* 如果应用程序编写者不想使用 TrustZone，但硬件不支持禁用 TrustZone，
 * 则整个应用程序（包括 FreeRTOS 调度程序）可以在安全侧运行，而无需分支到非安全侧。
 * 为此，除了将 configENABLE_TRUSTZONE 设置为 0 之外，还应将 configRUN_FREERTOS_SECURE_ONLY 设置为 1。 */
#define configRUN_FREERTOS_SECURE_ONLY    1

/* 将 configENABLE_MPU 设置为 1 以启用内存保护单元（MPU），或 0 以禁用内存保护单元。 */
#define configENABLE_MPU                  1

/* 将 configENABLE_FPU 设置为 1 以启用浮点单元（FPU），或 0 以禁用浮点单元。 */
#define configENABLE_FPU                  1

/* 将 configENABLE_MVE 设置为 1 以启用 M-Profile 向量扩展（MVE）支持，或 0 以禁用 MVE 支持。
 * 此选项仅适用于 Cortex-M55 和 Cortex-M85 端口，因为 M-Profile 向量扩展（MVE）仅在这些架构上可用。
 * configENABLE_MVE 必须保持未定义，或定义为 0 以适用于 Cortex-M23、Cortex-M33 和 Cortex-M35P 端口。 */
#define configENABLE_MVE                  1

/******************************************************************************/
/* ARMv7-M 和 ARMv8-M 端口特定配置定义。 **********************************/
/******************************************************************************/

/* 将 configCHECK_HANDLER_INSTALLATION 设置为 1 以启用额外的断言，以验证应用程序是否正确安装了 FreeRTOS 中断处理程序。
 *
 * 应用程序可以通过以下方式之一安装 FreeRTOS 中断处理程序：
 *   1. 直接路由 - 为 SVC 调用和 PendSV 中断安装 vPortSVCHandler 和 xPortPendSVHandler 函数。
 *   2. 间接路由 - 为 SVC 调用和 PendSV 中断安装单独的处理程序，并将程序控制路由到 vPortSVCHandler 和 xPortPendSVHandler 函数。
 * 使用间接路由的应用程序必须将 configCHECK_HANDLER_INSTALLATION 设置为 0。
 *
 * 如果保持未定义，则默认为 1。 */
#define configCHECK_HANDLER_INSTALLATION    1

/******************************************************************************/
/* 包含或排除功能的定义。 **************************************************/
/******************************************************************************/

/* 将以下 configUSE_* 常量设置为 1 以在构建中包含命名功能，或 0 以从构建中排除命名功能。 */
#define configUSE_TASK_NOTIFICATIONS           1
#define configUSE_MUTEXES                      1
#define configUSE_RECURSIVE_MUTEXES            1
#define configUSE_COUNTING_SEMAPHORES          1
#define configUSE_QUEUE_SETS                   0
#define configUSE_APPLICATION_TASK_TAG         0

/* 将以下 INCLUDE_* 常量设置为 1 以在构建中包含命名 API 函数，或 0 以从构建中排除命名 API 函数。
 * 大多数链接器即使常量为 1 也会删除未使用的函数。 */
#define INCLUDE_vTaskPrioritySet               1
#define INCLUDE_uxTaskPriorityGet              1
#define INCLUDE_vTaskDelete                    1
#define INCLUDE_vTaskSuspend                   1
#define INCLUDE_xResumeFromISR                 1
#define INCLUDE_vTaskDelayUntil                1
#define INCLUDE_vTaskDelay                     1
#define INCLUDE_xTaskGetSchedulerState         1
#define INCLUDE_xTaskGetCurrentTaskHandle      1
#define INCLUDE_uxTaskGetStackHighWaterMark    0
#define INCLUDE_xTaskGetIdleTaskHandle         0
#define INCLUDE_eTaskGetState                  0
#define INCLUDE_xEventGroupSetBitFromISR       1
#define INCLUDE_xTimerPendFunctionCall         0
#define INCLUDE_xTaskAbortDelay                0
#define INCLUDE_xTaskGetHandle                 0
#define INCLUDE_xTaskResumeFromISR             1

#define vPortSVCHandler    SVC_Handler
#define xPortPendSVHandler PendSV_Handler
#define xPortSysTickHandler SysTick_Handler

#endif /* FREERTOS_CONFIG_H */

```

### 项目中添加

在项目中的cmake 里面添加了宏，来确定改项目是否需要包含FreeRTOS功能

在tasks.json中修改如下
- 开启
    ```
    ...
    "args": [ 
        "-G",
        "MinGW Makefiles",
        "..",       
        "-DDEVICE_TYPE=STM32F407ZGTX",
        "-DBOOT=ON",
        //"-DRELEASE=ON",
        "-DFREERTOS=ON",
        "-DBOARD_TYPE=BOARD_TEST"  
    ],
    ...
    ```
- 关闭
    ```
    ...
    "args": [ 
        "-G",
        "MinGW Makefiles",
        "..",       
        "-DDEVICE_TYPE=STM32F407ZGTX",
        "-DBOOT=ON",
        //"-DRELEASE=ON",
        //"-DFREERTOS=ON",
        "-DBOARD_TYPE=BOARD_TEST"  
    ],
    ...
    ```


## 项目地址

https://github.com/DanceMonkey2020/stm32_project.git

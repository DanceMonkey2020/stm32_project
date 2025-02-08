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
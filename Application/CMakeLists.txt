#添加头文件搜索路径
include_directories(
    ${PROJECT_SOURCE_DIR}/Platform/CMSIS/Include
    ${PROJECT_SOURCE_DIR}/Platform/CMSIS/Device/ST/STM32F4xx/Include
    ${PROJECT_SOURCE_DIR}/Platform/FW/STM32F4xx_StdPeriph_Driver/inc   
    ${PROJECT_SOURCE_DIR}/Platform/FreeRTOS-Kernel
    ${PROJECT_SOURCE_DIR}/Platform/FreeRTOS-Kernel/include
    ${PROJECT_SOURCE_DIR}/Platform/FreeRTOS-Kernel/portable/GCC/ARM_CM4F
    ${PROJECT_SOURCE_DIR}/Application
)


#裸跑
if(${BOARD_TYPE} MATCHES "BOARD_DEMO") 
    add_definitions(-DBOARD_DEMO)
    message("build for BOARD_DEMO!")
    add_subdirectory(BoardDemo)
endif()

#FreeRTOS
if(${BOARD_TYPE} MATCHES "BOARD_RTOS_DEMO") 
    add_definitions(-DBOARD_RTOS_DEMO)
    message("build for BOARD_RTOS_DEMO!")
    add_subdirectory(BoardRTOSDemo)
endif()
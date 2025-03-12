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
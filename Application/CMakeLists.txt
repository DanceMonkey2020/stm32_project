
#添加头文件搜索路径
include_directories(
    ${PROJECT_SOURCE_DIR}/Platform/CMSIS/Include
    ${PROJECT_SOURCE_DIR}/Platform/CMSIS/Device/ST/STM32F4xx/Include
    ${PROJECT_SOURCE_DIR}/Platform/FW/STM32F4xx_StdPeriph_Driver/inc   
    ${PROJECT_SOURCE_DIR}/Application  
    ./Include 
)

#添加源文件
aux_source_directory(./Source SRC_LIST)

#添加非标准的共享库搜索路径
link_directories(${PROJECT_SOURCE_DIR}/build/lib)

#设置链接脚本
set(LINKER_SCRIPT ${PROJECT_SOURCE_DIR}/scripts/${DEVICE_TYPE}.ld)

#设置链接选项
set(CMAKE_EXE_LINKER_FLAGS "--specs=nano.specs -specs=nosys.specs -T${LINKER_SCRIPT} -Wl,-Map=${PROJECT_BINARY_DIR}/${DEVICE_TYPE}.map,--cref -Wl,--gc-sections")

#生成目标文件
add_executable(${DEVICE_TYPE}.elf main.c ${SRC_LIST})

# 确保可执行文件依赖于动态库
add_dependencies(${DEVICE_TYPE}.elf platform)

#把目标文件与库文件进行链接
target_link_libraries(${DEVICE_TYPE}.elf 
${DEVICE_TYPE}
)

#设置可执行文件输出路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

#设置 ELF 转换路径
set(ELF_FILE ${PROJECT_BINARY_DIR}/${DEVICE_TYPE}.elf)
set(HEX_FILE ${PROJECT_BINARY_DIR}/${DEVICE_TYPE}.hex)
set(BIN_FILE ${PROJECT_BINARY_DIR}/${DEVICE_TYPE}.bin)

#添加自定义命令实现 ELF 转换 hex 和 bin 文件
add_custom_command(TARGET "${DEVICE_TYPE}.elf" POST_BUILD
COMMAND ${CMAKE_OBJCOPY} -Obinary ${ELF_FILE} ${BIN_FILE}
COMMAND ${CMAKE_OBJCOPY} -Oihex ${ELF_FILE} ${HEX_FILE}
COMMENT "Building ${PROJECT_NAME}.bin and ${PROJECT_NAME}.hex"
COMMAND ${CMAKE_COMMAND} -E copy ${BIN_FILE} "${PROJECT_BINARY_DIR}/bin/${PROJECT_NAME}.bin"
COMMAND ${CMAKE_COMMAND} -E copy ${ELF_FILE} "${PROJECT_BINARY_DIR}/bin/${PROJECT_NAME}.elf"
COMMAND ${CMAKE_SIZE} --format=berkeley ${ELF_FILE} ${HEX_FILE}
COMMENT "Invoking: Cross ARM GNU Print Size")

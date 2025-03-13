#include "iap.h"

#include "stm32f4xx.h"


#pragma pack(push, 1)
typedef struct {
    // uint8_t start;
    uint8_t len;
    uint16_t addr;
    uint8_t type;
    //	uint8_t data[];
    //	uint8_t crc;
} S90;
#pragma pack(pop)

typedef void (*pFunction)(void);

const uint8_t* deserializationHex(const uint8_t* array, int32_t arrayLen, int32_t* dataType, uint16_t* dataAddr, int32_t* dataLen) {
    // 校验CRC
    uint8_t crc = 0;
    for (int32_t i = 0; i < arrayLen; i++)
        crc += array[i];
    if (crc != 0)
        return 0;

    // 校验长度
    uint8_t len = array[0];
    if ((len + 5) != arrayLen)
        return 0;

    // 提取地址
    uint16_t addr = array[1] << 8 | array[2];

    // 提取类型
    uint8_t type = array[3];

    if (dataAddr)
        *dataAddr = addr;
    if (dataLen)
        *dataLen = len;
    if (dataType)
        *dataType = type;

    // 提取地址
    // *data = array + 4;
    return array + 4;
}

void IapJumpApp(uint32_t addr) {
    // 检查栈顶地址是否合法.
    // if (((*(volatile uint32_t*)addr) & 0x2FFE0000U) != 0x20020000U)
    //     return;

    __disable_irq();
    __set_FAULTMASK(1);
    pFunction gotoApp = (pFunction) * (volatile uint32_t*)(addr + 4);
    __set_MSP(*(volatile uint32_t*)addr);
    gotoApp();
}

void IapJumpBoot() {
    __disable_irq();
    __set_FAULTMASK(1); // 关闭所有中端
    NVIC_SystemReset();
}

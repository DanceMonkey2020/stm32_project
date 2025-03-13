#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"

#include "iap.h"

// 延时函数
void delay(volatile uint32_t delay)
{
    while (delay--)
    {
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

    // 配置为输出模式
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOC, &GPIO_InitStruct);

    int cnt = 0;

#ifdef BOOT
    int count = 100;
#else
    int count = 1000;
#endif

    while (1)
    {

        for (int i = 0; i < 10000; i++)
        {
            GPIO_SetBits(GPIOC, GPIO_Pin_0); // 点亮LED
            delay(count);                    // 延时
        }
        for (int i = 0; i < 10000; i++)
        {
            GPIO_ResetBits(GPIOC, GPIO_Pin_0); // 熄灭LED
            delay(count);                      // 延时
        }

        if (cnt == 5)
            break;
        cnt++;
    }

// #ifdef BOOT
//     IapJumpApp(0x08020000U);
// #else
//     IapJumpBoot();
// #endif
}
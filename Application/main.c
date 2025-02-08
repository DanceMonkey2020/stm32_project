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
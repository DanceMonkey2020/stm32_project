#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"

#ifdef FREERTOS

#include "FreeRTOS.h"
#include "task.h"

#include "FreeRTOSConfig.h"
TaskHandle_t xHandle1 = NULL;
TaskHandle_t xHandle2 = NULL;

void vTask1(void *param)
{
    while (1)
    {
        vTaskDelay(300);
        GPIO_ToggleBits(GPIOC, GPIO_Pin_0);
    }
}

void vTask2(void *param)
{
    while (1)
    {
        vTaskDelay(500);
        GPIO_ToggleBits(GPIOC, GPIO_Pin_1);
    }
}

#else

#include "iap.h"
// 延时函数
void delay(volatile uint32_t delay)
{
    while (delay--)
    {
        __asm("nop");
    }
}

void led()
{
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

        if (cnt == 10)
            break;
        cnt++;
    }

// #ifdef BOOT
//     IapJumpApp(0x08020000U);
// #else
//     IapJumpBoot();
// #endif
}

#endif

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

#ifdef FREERTOS

    SystemCoreClockUpdate();
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
    SysTick_Config(SystemCoreClock / configTICK_RATE_HZ);

    xTaskCreate(vTask1, "vTask1", 512, NULL, 2, &xHandle1);
    xTaskCreate(vTask2, "vTask2", 512, NULL, 1, &xHandle2);
    vTaskStartScheduler();
#else
    led();
#endif

    for (;;)
    {
    }
}
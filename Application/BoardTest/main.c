#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"

#include "iap.h"

/*!
    \brief    this function handles NMI exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void NMI_Handler(void)
{
}

/*!
    \brief    this function handles HardFault exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void HardFault_Handler(void)
{
    /* if Hard Fault exception occurs, go to infinite loop */
    // R14(LR) = 0xFFFF FFFD，则查看 PSP
    // R14(LR) = 0xFFFF FFF1，则查看 MSP
    // 依次为R0~R3、R12、LR、PC、XPRS
    // 堆栈后第21个字节到24字节即为LR，即为异常前PC将要执行的下一条指令地址。
    while (1)
    {
    }
    // NVIC_SystemReset();
}

/*!
    \brief    this function handles MemManage exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void MemManage_Handler(void)
{
    /* if Memory Manage exception occurs, go to infinite loop */
    while (1)
    {
    }
}

/*!
    \brief    this function handles BusFault exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void BusFault_Handler(void)
{
    /* if Bus Fault exception occurs, go to infinite loop */
    while (1)
    {
    }
}

/*!
    \brief    this function handles UsageFault exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void UsageFault_Handler(void)
{
    /* if Usage Fault exception occurs, go to infinite loop */
    while (1)
    {
    }
}

/*!
    \brief    this function handles SVC exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void SVC_Handler(void) {}

/*!
    \brief    this function handles DebugMon exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void DebugMon_Handler(void) {}

/*!
    \brief    this function handles PendSV exception
    \param[in]  none
    \param[out] none
    \retval     none
*/

void PendSV_Handler(void)
{
}

void SysTick_Handler(void)
{
}

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

    // 配置PA5为输出模式
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE); // 使能GPIOA时钟

    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;          // 选择PA5
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;      // 设置为输出模式
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz; // 设置速度
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;     // 设置为推挽输出
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;   // 不使用上拉或下拉
    GPIO_Init(GPIOC, &GPIO_InitStruct);             // 初始化GPIOC

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

#ifdef BOOT
    IapJumpApp(0x08020000U);
#else
    IapJumpBoot();
#endif
}
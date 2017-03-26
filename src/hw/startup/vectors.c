/*
 * File:    vectors.c
 * Author:  GAndaLF
 * Brief:   Interrupt vector for STM32F40x.
 */

/* This symbol is created by the linker script. */
extern const char __stack_end;

void
Reset_Handler(void);

/* Every not used interrupt is redirected to default handler. */
static void __attribute__ ((interrupt))
__Default_Handler(void)
{
    while (1)
    {
        ;
    }
}

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
NMI_Handler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
HardFault_Handler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
MemManage_Handler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
BusFault_Handler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
UsageFault_Handler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
__Reserved_0x1C_Handler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
__Reserved_0x20_Handler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
__Reserved_0x24_Handler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
__Reserved_0x28_Handler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
SVC_Handler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
DebugMon_Handler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
__Reserved_0x34_Handler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
PendSV_Handler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
SysTick_Handler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
WWDG_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
PVD_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
TAMP_STAMP_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
RTC_WKUP_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
FLASH_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
RCC_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
EXTI0_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
EXTI1_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
EXTI2_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
EXTI3_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
EXTI4_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
DMA1_Stream0_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
DMA1_Stream1_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
DMA1_Stream2_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
DMA1_Stream3_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
DMA1_Stream4_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
DMA1_Stream5_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
DMA1_Stream6_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
ADC_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
CAN1_TX_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
CAN1_RX0_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
CAN1_RX1_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
CAN1_SCE_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
EXTI9_5_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
TIM1_BRK_TIM9_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
TIM1_UP_TIM10_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
TIM1_TRG_COM_TIM11_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
TIM1_CC_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
TIM2_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
TIM3_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
TIM4_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
I2C1_EV_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
I2C1_ER_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
I2C2_EV_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
I2C2_ER_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
SPI1_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
SPI2_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
USART1_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
USART2_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
USART3_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
EXTI15_10_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
RTC_Alarm_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
OTG_FS_WKUP_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
TIM8_BRK_TIM12_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
TIM8_UP_TIM13_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
TIM8_TRG_COM_TIM14_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
TIM8_CC_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
DMA1_Stream7_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
FSMC_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
SDIO_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
TIM5_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
SPI3_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
UART4_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
UART5_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
TIM6_DAC_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
TIM7_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
DMA2_Stream0_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
DMA2_Stream1_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
DMA2_Stream2_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
DMA2_Stream3_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
DMA2_Stream4_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
ETH_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
ETH_WKUP_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
CAN2_TX_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
CAN2_RX0_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
CAN2_RX1_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
CAN2_SCE_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
OTG_FS_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
DMA2_Stream5_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
DMA2_Stream6_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
DMA2_Stream7_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
USART6_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
I2C3_EV_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
I2C3_ER_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
OTG_HS_EP1_OUT_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
OTG_HS_EP1_IN_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
OTG_HS_WKUP_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
OTG_HS_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
DCMI_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
CRYP_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
HASH_RNG_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("__Default_Handler")))
FPU_IRQHandler(void);

/*
 * Interrupt vector for STM32F401 is the same as for others from F4 family.
 * When given interrupt is not supported in F401, it is not mentioned in
 * the documentation, but place for it is left in address space.
 */
void (* const vectors[])(void) __attribute__ ((section(".vectors"))) =
{
    (void (*)(void))&__stack_end,
    Reset_Handler,
    NMI_Handler,
    HardFault_Handler,
    MemManage_Handler,
    BusFault_Handler,
    UsageFault_Handler,
    __Reserved_0x1C_Handler,
    __Reserved_0x20_Handler,
    __Reserved_0x24_Handler,
    __Reserved_0x28_Handler,
    SVC_Handler,
    DebugMon_Handler,
    __Reserved_0x34_Handler,
    PendSV_Handler,
    SysTick_Handler,
    WWDG_IRQHandler,
    PVD_IRQHandler,
    TAMP_STAMP_IRQHandler,
    RTC_WKUP_IRQHandler,
    FLASH_IRQHandler,
    RCC_IRQHandler,
    EXTI0_IRQHandler,
    EXTI1_IRQHandler,
    EXTI2_IRQHandler,
    EXTI3_IRQHandler,
    EXTI4_IRQHandler,
    DMA1_Stream0_IRQHandler,
    DMA1_Stream1_IRQHandler,
    DMA1_Stream2_IRQHandler,
    DMA1_Stream3_IRQHandler,
    DMA1_Stream4_IRQHandler,
    DMA1_Stream5_IRQHandler,
    DMA1_Stream6_IRQHandler,
    ADC_IRQHandler,
    CAN1_TX_IRQHandler,
    CAN1_RX0_IRQHandler,
    CAN1_RX1_IRQHandler,
    CAN1_SCE_IRQHandler,
    EXTI9_5_IRQHandler,
    TIM1_BRK_TIM9_IRQHandler,
    TIM1_UP_TIM10_IRQHandler,
    TIM1_TRG_COM_TIM11_IRQHandler,
    TIM1_CC_IRQHandler,
    TIM2_IRQHandler,
    TIM3_IRQHandler,
    TIM4_IRQHandler,
    I2C1_EV_IRQHandler,
    I2C1_ER_IRQHandler,
    I2C2_EV_IRQHandler,
    I2C2_ER_IRQHandler,
    SPI1_IRQHandler,
    SPI2_IRQHandler,
    USART1_IRQHandler,
    USART2_IRQHandler,
    USART3_IRQHandler,
    EXTI15_10_IRQHandler,
    RTC_Alarm_IRQHandler,
    OTG_FS_WKUP_IRQHandler,
    TIM8_BRK_TIM12_IRQHandler,
    TIM8_UP_TIM13_IRQHandler,
    TIM8_TRG_COM_TIM14_IRQHandler,
    TIM8_CC_IRQHandler,
    DMA1_Stream7_IRQHandler,
    FSMC_IRQHandler,
    SDIO_IRQHandler,
    TIM5_IRQHandler,
    SPI3_IRQHandler,
    UART4_IRQHandler,
    UART5_IRQHandler,
    TIM6_DAC_IRQHandler,
    TIM7_IRQHandler,
    DMA2_Stream0_IRQHandler,
    DMA2_Stream1_IRQHandler,
    DMA2_Stream2_IRQHandler,
    DMA2_Stream3_IRQHandler,
    DMA2_Stream4_IRQHandler,
    ETH_IRQHandler,
    ETH_WKUP_IRQHandler,
    CAN2_TX_IRQHandler,
    CAN2_RX0_IRQHandler,
    CAN2_RX1_IRQHandler,
    CAN2_SCE_IRQHandler,
    OTG_FS_IRQHandler,
    DMA2_Stream5_IRQHandler,
    DMA2_Stream6_IRQHandler,
    DMA2_Stream7_IRQHandler,
    USART6_IRQHandler,
    I2C3_EV_IRQHandler,
    I2C3_ER_IRQHandler,
    OTG_HS_EP1_OUT_IRQHandler,
    OTG_HS_EP1_IN_IRQHandler,
    OTG_HS_WKUP_IRQHandler,
    OTG_HS_IRQHandler,
    DCMI_IRQHandler,
    CRYP_IRQHandler,
    HASH_RNG_IRQHandler,
    FPU_IRQHandler,
};

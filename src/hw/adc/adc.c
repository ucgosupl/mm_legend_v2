/*
 * file:	adc.c
 * author:	GAndaLF
 * brief:   ADC peripheral configuration.
 */

#include "platform_specific.h"

#include "gpio_f4/gpio_f4.h"

#include "adc.h"

/** Front right phototransistor pin number - PA02. */
#define PHOTO_FRONT_R_PIN           2
/** Diagonal right phototransistor pin number - PA03. */
#define PHOTO_DIAG_R_PIN            3
/** Side right phototransistor pin number - PA04. */
#define PHOTO_SIDE_R_PIN            4
/** Side left phototransistor pin number - PA05. */
#define PHOTO_SIDE_L_PIN            5
/** Diagonal left phototransistor pin number - PA06. */
#define PHOTO_DIAG_L_PIN            6
/** Front left phototransistor pin number - PA07. */
#define PHOTO_FRONT_L_PIN           7
/** Battery monitor pin number - PB00. */
#define V_BAT_PIN                   0

/** Front right phototransistor ADC channel. */
#define PHOTO_FRONT_R_CHANNEL       2
/** Diagonal right phototransistor ADC channel. */
#define PHOTO_DIAG_R_CHANNEL        3
/** Side right phototransistor ADC channel. */
#define PHOTO_SIDE_R_CHANNEL        4
/** Side left phototransistor ADC channel. */
#define PHOTO_SIDE_L_CHANNEL        5
/** Diagonal left phototransistor ADC channel. */
#define PHOTO_DIAG_L_CHANNEL        6
/** Front left phototransistor ADC channel. */
#define PHOTO_FRONT_L_CHANNEL       7
/** Battery monitor ADC channel. */
#define V_BAT_CHANNEL               8

/** DMA stream used for ADC. */
#define ADC_DMA                     DMA2_Stream0

/** Value of PRIO field in DMA CR register - Priority low. */
#define DMA_PRIO_LOW                0
/** Value of PRIO field in DMA CR register - Priority medium. */
#define DMA_PRIO_MEDIUM             1
/** Value of PRIO field in DMA CR register - Priority high. */
#define DMA_PRIO_HIGH               2
/** Value of PRIO field in DMA CR register - Priority very high. */
#define DMA_PRIO_VERYHIGH           3

/** Value of PSIZE and MSIZE fields in DMA CR register - Size 8-bit. */
#define DMA_SIZE_8BIT               0
/** Value of PSIZE and MSIZE fields in DMA CR register - Size 16-bit. */
#define DMA_SIZE_16BIT              1
/** Value of PSIZE and MSIZE fields in DMA CR register - Size 32-bit. */
#define DMA_SIZE_32BIT              2

/** Value of DIR filed in DMA CR register - Direction peripheral to memory. */
#define DMA_DIR_PERIPH_TO_MEM       0
/** Value of DIR filed in DMA CR register - Direction memory to peripheral. */
#define DMA_DIR_MEM_TO_PERIPH       1
/** Value of DIR filed in DMA CR register - Direction memory to memory. */
#define DMA_DIR_MEM_TO_MEM          2

/** Offset of bitfield CHSEL in DMA CR register. */
#define DMA_CR_CHSEL_BIT            25
/** Offset of bitfield PL in DMA CR register. */
#define DMA_CR_PL_BIT               16
/** Offset of bitfield MSIZE in DMA CR register. */
#define DMA_CR_MSIZE_BIT            13
/** Offset of bitfield PSIZE in DMA CR register. */
#define DMA_CR_PSIZE_BIT            11
/** Offset of bitfield DIR in DMA CR register. */
#define DMA_CR_DIR_BIT              6

/** Sample time 144 cycles of ADCCLK. */
#define ADC_SMP_144_CYCLES          6
/** Sample time 480 cycles of ADCCLK. */
#define ADC_SMP_480_CYCLES          7

/** Offset of bitfield SMP2 in ADC_SPMR2 register. */
#define ADC_SMPR2_SMP2_BIT          6
/** Offset of bitfield SMP3 in ADC_SPMR2 register. */
#define ADC_SMPR2_SMP3_BIT          9
/** Offset of bitfield SMP4 in ADC_SPMR2 register. */
#define ADC_SMPR2_SMP4_BIT          12
/** Offset of bitfield SMP5 in ADC_SPMR2 register. */
#define ADC_SMPR2_SMP5_BIT          15
/** Offset of bitfield SMP6 in ADC_SPMR2 register. */
#define ADC_SMPR2_SMP6_BIT          18
/** Offset of bitfield SMP6 in ADC_SPMR2 register. */
#define ADC_SMPR2_SMP7_BIT          21
/** Offset of bitfield SMP6 in ADC_SPMR2 register. */
#define ADC_SMPR2_SMP8_BIT          24

/** Offset of bitfield LEN in ADC_SQR1 register. */
#define ADC_SQR1_LEN_BIT            20

/** Offset of bitfield SQ7 in ADC_SQR2 register. */
#define ADC_SQR2_SQ7_BIT            0

/** Offset of bitfield SQ1 in ADC_SQR3 register. */
#define ADC_SQR3_SQ1_BIT            0
/** Offset of bitfield SQ2 in ADC_SQR3 register. */
#define ADC_SQR3_SQ2_BIT            5
/** Offset of bitfield SQ3 in ADC_SQR3 register. */
#define ADC_SQR3_SQ3_BIT            10
/** Offset of bitfield SQ4 in ADC_SQR3 register. */
#define ADC_SQR3_SQ4_BIT            15
/** Offset of bitfield SQ5 in ADC_SQR3 register. */
#define ADC_SQR3_SQ5_BIT            20
/** Offset of bitfield SQ6 in ADC_SQR3 register. */
#define ADC_SQR3_SQ6_BIT            25

/** Number of ADC measurements in a cycle. */
#define ADC_BUF_SIZE                7

/**
 * Array storing measured ADC values.
 */
static int32_t adc_buf[ADC_BUF_SIZE];
/**
 * GPIO initialization for ADC.
 */
static void gpio_init(void);

/**
 * DMA configuration to run with ADC.
 */
static void dma_init(void);

/**
 * ADC1 peripheral initialization.
 */
static void adc1_init(void);

void adc_init(void)
{
    gpio_init();
    dma_init();
    adc1_init();
}

int32_t adc_val_get(int32_t id)
{
    return adc_buf[id];
}

static void gpio_init(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

    gpio_mode_config(GPIOA, PHOTO_FRONT_R_PIN, GPIO_MODE_ANALOG);
    gpio_mode_config(GPIOA, PHOTO_DIAG_R_PIN, GPIO_MODE_ANALOG);
    gpio_mode_config(GPIOA, PHOTO_SIDE_R_PIN, GPIO_MODE_ANALOG);
    gpio_mode_config(GPIOA, PHOTO_SIDE_L_PIN, GPIO_MODE_ANALOG);
    gpio_mode_config(GPIOA, PHOTO_DIAG_L_PIN, GPIO_MODE_ANALOG);
    gpio_mode_config(GPIOA, PHOTO_FRONT_L_PIN, GPIO_MODE_ANALOG);
    gpio_mode_config(GPIOB, V_BAT_PIN, GPIO_MODE_ANALOG);
}

static void dma_init(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;

    ADC_DMA->CR = (0 << DMA_CR_CHSEL_BIT) |             /* Set channel 0 */
                (DMA_PRIO_MEDIUM << DMA_CR_PL_BIT) |    /* Set priority */
                (DMA_SIZE_32BIT << DMA_CR_MSIZE_BIT) |  /* Set memory size */
                (DMA_SIZE_32BIT << DMA_CR_PSIZE_BIT) |  /* Set periph size */
                DMA_SxCR_MINC |                     /* Set memory increment */
                DMA_SxCR_CIRC |                     /* Set circular mode */
                (DMA_DIR_PERIPH_TO_MEM << DMA_CR_DIR_BIT);  /* Set direction */

    /* Set source, destination and size */
    ADC_DMA->NDTR = ADC_BUF_SIZE;
    ADC_DMA->PAR = (uint32_t) &ADC1->DR;
    ADC_DMA->M0AR = (uint32_t) adc_buf;

    /* Enable DMA channel */
    ADC_DMA->CR |= DMA_SxCR_EN;
}

static void adc1_init(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;

    /* Max allowed ADC frequency - 36MHz */
    ADC->CCR = 0;   /* Set prescaler to 2 which gives 84 /2 /2 = 21MHz */

    ADC1->CR1 = ADC_CR1_SCAN;   /* Enable scan mode */
    ADC1->CR2 = ADC_CR2_DMA |   /* Enable DMA */
            ADC_CR2_DDS |       /* DMA dont stop after first conversion */
            ADC_CR2_CONT;       /* Enable continuous conversion */

    /* Set sampling time to 144 cycles for channels 2 - 8 */
    ADC1->SMPR2 = (ADC_SMP_144_CYCLES << ADC_SMPR2_SMP2_BIT) |
                (ADC_SMP_144_CYCLES << ADC_SMPR2_SMP3_BIT) |
                (ADC_SMP_144_CYCLES << ADC_SMPR2_SMP4_BIT) |
                (ADC_SMP_144_CYCLES << ADC_SMPR2_SMP5_BIT) |
                (ADC_SMP_144_CYCLES << ADC_SMPR2_SMP6_BIT) |
                (ADC_SMP_144_CYCLES << ADC_SMPR2_SMP7_BIT) |
                (ADC_SMP_144_CYCLES << ADC_SMPR2_SMP8_BIT);

    /* Set 7 conversions on channels 2 - 8 */
    ADC1->SQR1 = ((ADC_BUF_SIZE - 1) << ADC_SQR1_LEN_BIT);
    ADC1->SQR2 = (V_BAT_CHANNEL << ADC_SQR2_SQ7_BIT);
    ADC1->SQR3 = (PHOTO_FRONT_R_CHANNEL << ADC_SQR3_SQ1_BIT) |
                (PHOTO_DIAG_R_CHANNEL << ADC_SQR3_SQ2_BIT) |
                (PHOTO_SIDE_R_CHANNEL << ADC_SQR3_SQ3_BIT) |
                (PHOTO_SIDE_L_CHANNEL << ADC_SQR3_SQ4_BIT) |
                (PHOTO_DIAG_L_CHANNEL << ADC_SQR3_SQ5_BIT) |
                (PHOTO_FRONT_L_CHANNEL << ADC_SQR3_SQ6_BIT);

    ADC1->CR2 |= ADC_CR2_ADON;
    ADC1->CR2 |= ADC_CR2_SWSTART;
}

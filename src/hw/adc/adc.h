/*
 * file:	adc.h
 * author:	GAndaLF
 * brief:	ADC peripheral configuration.
 */

#ifndef _ADC_H_
#define _ADC_H_

/** Channel used by side left phototransistor. */
#define ADC_PHOTO_SIDE_L        0
/** Channel used by side right phototransistor. */
#define ADC_PHOTO_SIDE_R        1
/** Channel used by diagonal left phototransistor. */
#define ADC_PHOTO_DIAG_L        2
/** Channel used by diagonal right phototransistor. */
#define ADC_PHOTO_DIAG_R        3
/** Channel used by front left phototransistor. */
#define ADC_PHOTO_FRONT_L       4
/** Channel used by front right phototransistor. */
#define ADC_PHOTO_FRONT_R       5
/** Channel used by battery voltage monitor. */
#define ADC_VBAT                6

/**
 * Initialisation of ADC peripheral.
 *
 * This function configures ADC to run on 7 channels in cyclic mode. Results are
 * stored in buffer using DMA.
 */
void adc_init(void);

/**
 * Get last ADC measurement for a given channel.
 *
 * @param channel           ADC channel.
 *
 * @return                  ADC value.
 */
int32_t adc_val_get(int32_t channel);

#endif /* _ADC_H_ */

/*
 * file:	adc.h
 * author:	GAndaLF
 * brief:	ADC peripheral configuration.
 */

#ifndef _ADC_H_
#define _ADC_H_

/* Order is dependent on channel sequence programmed in ADC */
/** Front right phototransistor id. */
#define ADC_PHOTO_FRONT_R       0
/** Diagonal right phototransistor id. */
#define ADC_PHOTO_DIAG_R        1
/** Side right phototransistor id. */
#define ADC_PHOTO_SIDE_R        2
/** Side left phototransistor id. */
#define ADC_PHOTO_SIDE_L        3
/** Diagonal left phototransistor id. */
#define ADC_PHOTO_DIAG_L        4
/** Front left phototransistor id. */
#define ADC_PHOTO_FRONT_L       5
/** Battery voltage monitor id. */
#define ADC_VBAT                6

/**
 * Initialisation of ADC peripheral.
 *
 * This function configures ADC to run on 7 channels in cyclic mode. Results are
 * stored in buffer using DMA.
 */
void adc_init(void);

/**
 * Get last ADC measurement for a given id.
 *
 * @param id                ADC id.
 *
 * @return                  ADC value.
 */
int32_t adc_val_get(int32_t id);

#endif /* _ADC_H_ */

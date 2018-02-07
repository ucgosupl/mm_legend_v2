/*
 * file:	adc2dist.h
 * author:	GAndaLF
 * brief:	Conversion from ADC value to distance in millimeters.
 */

#ifndef _ADC2DIST_H_
#define _ADC2DIST_H_

/**
 * Convert ADC value meaured by wall sensor to distance in millimeters.
 *
 * This function returns distance from sensor. To get distance from robot offset
 * depending on sensor orientation should be subtracted.
 *
 * @param adc               ADC value.
 * @return                  Distance in millimeters.
 */
int32_t adc2dist(int32_t adc);

#endif /* _ADC2DIST_H_ */

/*
 * file:	adc2dist.h
 * author:	GAndaLF
 * brief:	Conversion from ADC value to distance in millimeters.
 */

#ifndef _ADC2DIST_H_
#define _ADC2DIST_H_

/**
 * Convert ADC value measured by left front sensor to distance in millimeters.
 *
 * This function returns distance from sensor. To get distance from robot offset
 * depending on sensor orientation should be subtracted.
 *
 * @param adc               ADC value.
 * @return                  Distance in millimeters.
 */
int32_t adc2dist_lfront(int32_t adc);

/**
 * Convert ADC value measured by right front sensor to distance in millimeters.
 *
 * This function returns distance from sensor. To get distance from robot offset
 * depending on sensor orientation should be subtracted.
 *
 * @param adc               ADC value.
 * @return                  Distance in millimeters.
 */
int32_t adc2dist_rfront(int32_t adc);

/**
 * Convert ADC value measured by left diagonal sensor to distance in millimeters.
 *
 * This function returns distance from sensor. To get distance from robot offset
 * depending on sensor orientation should be subtracted.
 *
 * @param adc               ADC value.
 * @return                  Distance in millimeters.
 */
int32_t adc2dist_ldiag(int32_t adc);

/**
 * Convert ADC value measured by right diagonal sensor to distance in millimeters.
 *
 * This function returns distance from sensor. To get distance from robot offset
 * depending on sensor orientation should be subtracted.
 *
 * @param adc               ADC value.
 * @return                  Distance in millimeters.
 */
int32_t adc2dist_rdiag(int32_t adc);

/**
 * Convert ADC value measured by left side sensor to distance in millimeters.
 *
 * This function returns distance from sensor. To get distance from robot offset
 * depending on sensor orientation should be subtracted.
 *
 * @param adc               ADC value.
 * @return                  Distance in millimeters.
 */
int32_t adc2dist_lside(int32_t adc);

/**
 * Convert ADC value measured by right side sensor to distance in millimeters.
 *
 * This function returns distance from sensor. To get distance from robot offset
 * depending on sensor orientation should be subtracted.
 *
 * @param adc               ADC value.
 * @return                  Distance in millimeters.
 */
int32_t adc2dist_rside(int32_t adc);

#endif /* _ADC2DIST_H_ */

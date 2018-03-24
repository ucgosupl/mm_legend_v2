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
int32_t adc2dist_front_l(int32_t adc);

/**
 * Convert ADC value measured by right front sensor to distance in millimeters.
 *
 * This function returns distance from sensor. To get distance from robot offset
 * depending on sensor orientation should be subtracted.
 *
 * @param adc               ADC value.
 * @return                  Distance in millimeters.
 */
int32_t adc2dist_front_r(int32_t adc);

/**
 * Convert ADC value measured by left diagonal sensor to distance in millimeters.
 *
 * This function returns distance from sensor. To get distance from robot offset
 * depending on sensor orientation should be subtracted.
 *
 * @param adc               ADC value.
 * @return                  Distance in millimeters.
 */
int32_t adc2dist_diag_l(int32_t adc);

/**
 * Convert ADC value measured by right diagonal sensor to distance in millimeters.
 *
 * This function returns distance from sensor. To get distance from robot offset
 * depending on sensor orientation should be subtracted.
 *
 * @param adc               ADC value.
 * @return                  Distance in millimeters.
 */
int32_t adc2dist_diag_r(int32_t adc);

/**
 * Convert ADC value measured by left side sensor to distance in millimeters.
 *
 * This function returns distance from sensor. To get distance from robot offset
 * depending on sensor orientation should be subtracted.
 *
 * @param adc               ADC value.
 * @return                  Distance in millimeters.
 */
int32_t adc2dist_side_l(int32_t adc);

/**
 * Convert ADC value measured by right side sensor to distance in millimeters.
 *
 * This function returns distance from sensor. To get distance from robot offset
 * depending on sensor orientation should be subtracted.
 *
 * @param adc               ADC value.
 * @return                  Distance in millimeters.
 */
int32_t adc2dist_side_r(int32_t adc);

#endif /* _ADC2DIST_H_ */

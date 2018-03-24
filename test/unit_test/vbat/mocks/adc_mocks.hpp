/*
 * file:	adc_mocks.hpp
 * author:	GAndaLF
 * brief:	Mock functions for ADC hardware driver.
 */

#ifndef _ADC_MOCKS_HPP_
#define _ADC_MOCKS_HPP_

/** Value of voltage divider upper resistance. */
#define VBAT_DIV_UP_KOHM        51UL
/** Value of voltage divider lower resistance. */
#define VBAT_DIV_DOWN_KOHM      100UL
/** Minimum allowed battery voltage in millivolts. */
#define VBAT_MIN_VOLTAGE_MV     7000UL

/** Minimum allowed value read from ADC. */
#define VBAT_THRESHOLD  \
    ((VBAT_DIV_UP_KOHM * VBAT_MIN_VOLTAGE_MV * ADC_MAX_VAL) / \
((VBAT_DIV_UP_KOHM + VBAT_DIV_DOWN_KOHM) * ADC_MAX_VOLTAGE_MV))

constexpr int32_t ADC_VAL_MIN_ABOVE_THRESHOLD = VBAT_THRESHOLD;
constexpr int32_t ADC_VAL_MAX_BELOW_THRESHOLD = VBAT_THRESHOLD - 1;

class AdcValGetMock
{
private:
    int32_t cnt_ = 0;
    int32_t arg1_ = -1;
    int32_t retVal_ = ADC_MAX_VAL;
    int32_t iterOtherVal_ = -1;
    int32_t retValOther_ = 0;

public:
    AdcValGetMock() = default;
    AdcValGetMock(int32_t retVal);
    AdcValGetMock(int32_t retVal, int32_t iterOtherVal, int32_t retValOther);

    int32_t getCount();
    int32_t getArg1();
    int32_t call(int32_t arg1);
};

void adcValGetMockSet(AdcValGetMock *mock);

#endif /* _ADC_MOCKS_HPP_ */

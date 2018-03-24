/*
 * file:	adc_mocks.cpp
 * author:	GAndaLF
 * brief:	Mock functions for ADC hardware driver.
 */

#include "platform_specific.h"

extern "C"
{
    #include "adc/adc.h"
}

#include "adc_mocks.hpp"

static AdcValGetMock *adcValGetMock = nullptr;

void adc_init(void)
{

}

AdcValGetMock::AdcValGetMock(int32_t retVal) : retVal_(retVal) {};
AdcValGetMock::AdcValGetMock(int32_t retVal, int32_t iterOtherVal, int32_t retvalOther) :
        retVal_(retVal),
        iterOtherVal_(iterOtherVal),
        retValOther_(retvalOther)
{};

int32_t AdcValGetMock::getCount()
{
    return cnt_;
}

int32_t AdcValGetMock::getArg1()
{
    return arg1_;
}

int32_t AdcValGetMock::call(int32_t arg1)
{
    cnt_++;

    arg1_ = arg1;

    /* Mechanism to induce single reading other than the rest. */
    if ((0 < iterOtherVal_) && (cnt_ == iterOtherVal_))
    {
        return retValOther_;
    }

    return retVal_;
}

void adcValGetMockSet(AdcValGetMock *mock)
{
    adcValGetMock = mock;
}

int32_t adc_val_get(int32_t id)
{
    //returning max value so upper threshold is always taken
    return (nullptr == adcValGetMock) ? ADC_MAX_VAL : adcValGetMock->call(id);
}



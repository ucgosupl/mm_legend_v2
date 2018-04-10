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

#include "mock_templates.hpp"
#include "adc_mocks.hpp"

static AdcValGetMock *adcValGetMock = nullptr;

void adc_init(void)
{

}

AdcValGetMock::AdcValGetMock(int32_t retVal) : Ret1ArgMock(retVal)
{}

AdcValGetMock::AdcValGetMock(int32_t retVal, int32_t iterOtherVal, int32_t retvalOther) :
        Ret1ArgMock(retVal),
        iterOtherVal_(iterOtherVal),
        retValOther_(retvalOther)
{}

int32_t AdcValGetMock::call(int32_t arg1)
{
    /* Mechanism to induce single reading other than the rest. */
    if ((0 < iterOtherVal_) && (cnt_ + 1 == iterOtherVal_))
    {
        return retValOther_;
    }

    return Ret1ArgMock<int32_t, int32_t>::call(arg1);
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



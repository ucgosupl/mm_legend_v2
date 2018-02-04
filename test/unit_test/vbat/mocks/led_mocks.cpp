/*
 * file:	led_mocks.cpp
 * author:	GAndaLF
 * brief:	Mock functions for LED hardware driver.
 */

#include "platform_specific.h"

extern "C"
{
    #include "led/led.h"
}

#include "led_mocks.hpp"

static LedOnOffMock *ledOnMock = nullptr;
static LedOnOffMock *ledOffMock = nullptr;
static LedAllOffMock *ledAllOffMock = nullptr;

void led_init(void)
{

}

int32_t LedOnOffMock::getCount()
{
    return cnt_;
}

int32_t LedOnOffMock::getArg1()
{
    return arg1_;
}

void LedOnOffMock::call(int32_t arg1)
{
    cnt_++;

    arg1_ = arg1;
}

void ledOnMockSet(LedOnOffMock *mock)
{
    ledOnMock = mock;
}

void led_on(int32_t id)
{
    if (nullptr != ledOnMock)
    {
        ledOnMock->call(id);
    }
}

void ledOffMockSet(LedOnOffMock *mock)
{
    ledOffMock = mock;
}

void led_off(int32_t id)
{
    if (nullptr != ledOffMock)
    {
        ledOffMock->call(id);
    }
}

int32_t LedAllOffMock::getCount()
{
    return cnt_;
}

void LedAllOffMock::call()
{
    cnt_++;
}

void ledAllOffMockSet(LedAllOffMock *mock)
{
    ledAllOffMock = mock;
}

void led_all_off(void)
{
    if (nullptr != ledAllOffMock)
    {
        ledAllOffMock->call();
    }
}

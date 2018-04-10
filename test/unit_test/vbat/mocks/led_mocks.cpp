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

#include "mock_templates.hpp"
#include "led_mocks.hpp"

static LedOnOffMock *ledOnMock = nullptr;
static LedOnOffMock *ledOffMock = nullptr;
static LedAllOffMock *ledAllOffMock = nullptr;

void led_init(void)
{

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

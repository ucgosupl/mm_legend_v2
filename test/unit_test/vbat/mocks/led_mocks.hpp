/*
 * file:	led_mocks.hpp
 * author:	GAndaLF
 * brief:	Mock functions for LED hardware driver.
 */

#ifndef _LED_MOCKS_HPP_
#define _LED_MOCKS_HPP_

class LedOnOffMock
{
private:
    int32_t cnt_ = 0;
    int32_t arg1_ = -1;

public:
    LedOnOffMock() = default;

    int32_t getCount();
    int32_t getArg1();
    void call(int32_t arg1);
};

void ledOnMockSet(LedOnOffMock *mock);
void ledOffMockSet(LedOnOffMock *mock);

class LedAllOffMock
{
private:
    int32_t cnt_ = 0;

public:
    LedAllOffMock() = default;

    int32_t getCount();
    void call();
};

void ledAllOffMockSet(LedAllOffMock *mock);

#endif /* _LED_MOCKS_HPP_ */

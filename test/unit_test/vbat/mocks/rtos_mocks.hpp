/*
 * file:	rtos_mocks.hpp
 * author:	GAndaLF
 * brief:	Mock functions for rtos functionalities.
 */

#ifndef _RTOS_MOCKS_HPP_
#define _RTOS_MOCKS_HPP_

constexpr uint32_t RTOS_DELAY_UNTIL_MAX_ITERS_REACHED = 0xCC3355AA;

class RtosTickCountMock
{
private:
    int32_t cnt_ = 0;
    tick_t retVal_ = 0;

public:
    RtosTickCountMock() = default;
    RtosTickCountMock(tick_t retVal);

    int32_t getCount();
    tick_t call();
};

void rtosTickCountMockSet(RtosTickCountMock *mock);

class RtosDelayUntilMock
{
private:
    int32_t cnt_ = 0;
    tick_t arg1_ = -1;
    tick_t arg2_ = -1;
    int32_t iters_ = 0;
    bool isMaxItersReached_ = false;

public:
    RtosDelayUntilMock() = default;
    RtosDelayUntilMock(int32_t iters);

    int32_t getCount();
    tick_t getArg1();
    tick_t getArg2();
    void call(tick_t *arg1, tick_t arg2);
    bool isMaxItersReached();
};

void rtosDelayUntilMockSet(RtosDelayUntilMock *mock);

class RtosCriticalSectionMock
{
private:
    int32_t cnt_ = 0;

public:
    RtosCriticalSectionMock() = default;

    int32_t getCount();
    void call();
};

void rtosCriticalSectionEnterMockSet(RtosCriticalSectionMock *mock);
void rtosCriticalSectionExitMockSet(RtosCriticalSectionMock *mock);

#endif /* _RTOS_MOCKS_HPP_ */

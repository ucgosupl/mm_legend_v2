/*
 * file:	rtos_mocks.cpp
 * author:	GAndaLF
 * brief:	Mock functions for rtos functionalities.
 */

#include "platform_specific.h"

#include "rtos_mocks.hpp"

static RtosTickCountMock *tickCntMock = nullptr;
static RtosDelayUntilMock *delayUntilMock = nullptr;
static RtosCriticalSectionMock *criticalEnterMock = nullptr;
static RtosCriticalSectionMock *criticalExitMock = nullptr;

RtosTickCountMock::RtosTickCountMock(tick_t retval) : retVal_(retval) {};

int32_t RtosTickCountMock::getCount()
{
    return cnt_;
}

tick_t RtosTickCountMock::call()
{
    cnt_++;

    return retVal_;
}

void rtosTickCountMockSet(RtosTickCountMock *mock)
{
    tickCntMock = mock;
}

tick_t rtos_tick_count_get_mock(void)
{
    return (nullptr == tickCntMock) ? 0 : tickCntMock->call();
}

RtosDelayUntilMock::RtosDelayUntilMock(int32_t iters) : iters_(iters) {};

int32_t RtosDelayUntilMock::getCount()
{
    return cnt_;
}

tick_t RtosDelayUntilMock::getArg1()
{
    return arg1_;
}

tick_t RtosDelayUntilMock::getArg2()
{
    return arg2_;
}

void RtosDelayUntilMock::call(tick_t *arg1, tick_t arg2)
{
    arg1_ = *arg1;
    arg2_ = arg2;

    cnt_++;
    if (cnt_ >= iters_)
    {
        isMaxItersReached_ = true;
        throw RTOS_DELAY_UNTIL_MAX_ITERS_REACHED;
    }
}

bool RtosDelayUntilMock::isMaxItersReached()
{
    return isMaxItersReached_;
}

void rtosDelayUntilMockSet(RtosDelayUntilMock *mock)
{
    delayUntilMock = mock;
}

void rtos_delay_until_mock(tick_t *last_ptr, tick_t ms)
{
    if (nullptr != delayUntilMock)
    {
        delayUntilMock->call(last_ptr, ms);
    }
    else
    {
        /*
         * Not failing with no mock to ease tests for single iteration.
         */
        throw RTOS_DELAY_UNTIL_MAX_ITERS_REACHED;
    }
}

int32_t RtosCriticalSectionMock::getCount()
{
    return cnt_;
}

void RtosCriticalSectionMock::call()
{
    cnt_++;
}

void rtos_critical_section_enter_mock(void)
{
    if (nullptr != criticalEnterMock)
    {
        criticalEnterMock->call();
    }
}

void rtosCriticalSectionEnterMockSet(RtosCriticalSectionMock *mock)
{
    criticalEnterMock = mock;
}

void rtos_critical_section_exit_mock(void)
{
    if (nullptr != criticalExitMock)
    {
        criticalExitMock->call();
    }
}

void rtosCriticalSectionExitMockSet(RtosCriticalSectionMock *mock)
{
    criticalExitMock = mock;
}

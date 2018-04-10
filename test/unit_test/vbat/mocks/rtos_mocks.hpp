/*
 * file:	rtos_mocks.hpp
 * author:	GAndaLF
 * brief:	Mock functions for rtos functionalities.
 */

#ifndef _RTOS_MOCKS_HPP_
#define _RTOS_MOCKS_HPP_

constexpr uint32_t RTOS_DELAY_UNTIL_MAX_ITERS_REACHED = 0xCC3355AA;

using RtosTickCountMock = RetNoArgMock<tick_t>;
using RtosCriticalSectionMock = NoRetNoArgMock;

void rtosTickCountMockSet(RtosTickCountMock *mock);

class RtosDelayUntilMock : public NoRet2ArgMock<tick_t, tick_t>
{
private:
    int32_t iters_ = 0;
    bool isMaxItersReached_ = false;

public:
    RtosDelayUntilMock() = default;
    RtosDelayUntilMock(int32_t iters);

    void call(tick_t *arg1, tick_t arg2);
    bool isMaxItersReached();
};

void rtosDelayUntilMockSet(RtosDelayUntilMock *mock);

void rtosCriticalSectionEnterMockSet(RtosCriticalSectionMock *mock);
void rtosCriticalSectionExitMockSet(RtosCriticalSectionMock *mock);

#endif /* _RTOS_MOCKS_HPP_ */

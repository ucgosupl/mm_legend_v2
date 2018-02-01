/*
 * file:	endless_loop_mocks.hpp
 * author:	GAndaLF
 * brief:	Mocks for endless loops.
 */

#ifndef _ENDLESS_LOOP_MOCKS_HPP_
#define _ENDLESS_LOOP_MOCKS_HPP_

constexpr uint32_t ENDLESS_LOOP_REACHED = 0x55AA00FF;

class EndlessLoopMock
{
private:
    int32_t cnt_ = 0;
    int32_t iters_ = 0;
    bool isReached_ = false;

public:
    EndlessLoopMock() = default;
    EndlessLoopMock(int32_t iters);

    void call();
    bool isReached();
};

void endlessLoopMockSet(EndlessLoopMock *mock);

#endif /* _ENDLESS_LOOP_MOCKS_HPP_ */

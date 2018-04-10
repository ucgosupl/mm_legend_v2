/*
 * file:	endless_loop_mocks.cpp
 * author:	GAndaLF
 * brief:	Mocks for endless loops.
 */

#include "platform_specific.h"

#include "CppUTest/TestHarness.h"

#include "mock_templates.hpp"
#include "endless_loop_mocks.hpp"

static EndlessLoopMock *endlessLoopMock = nullptr;

EndlessLoopMock::EndlessLoopMock(int32_t iters) : iters_(iters) {};

bool EndlessLoopMock::isReached()
{
    return isReached_;
}

void EndlessLoopMock::call()
{
    if (0 >= iters_)
    {
        FAIL("Entered endless loop unexpectedly!");
    }

    NoRetNoArgMock::call();

    if (cnt_ >= iters_)
    {
        isReached_ = true;
        throw ENDLESS_LOOP_REACHED;
    }
}

void test_endless_loop(void)
{
    if (nullptr != endlessLoopMock)
    {
        endlessLoopMock->call();
    }
    else
    {
        /*
         * Not failing with no mock to ease tests that
         * doesn't care about endless loop.
         */
        throw ENDLESS_LOOP_REACHED;
    }
}

void endlessLoopMockSet(EndlessLoopMock *mock)
{
    endlessLoopMock = mock;
}

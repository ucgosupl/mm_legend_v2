/*
 * file:    position_mocks.cpp
 * author:  GAndaLF
 * brief:   Mock functions for position module.
 */

#include "platform_specific.h"

extern "C"
{
    #include "position/position.h"
}

#include "position_mocks.hpp"

static PositionGetMock *posXMock = nullptr;
static PositionGetMock *posYMock = nullptr;
static PositionGetMock *posAlphaMock = nullptr;

PositionGetMock::PositionGetMock(float retVal) : retVal_(retVal) {};

int32_t PositionGetMock::getCount()
{
    return cnt_;
}

float PositionGetMock::call()
{
    cnt_++;

    return retVal_;
}

void posXMockSet(PositionGetMock *mock)
{
    posXMock = mock;
}

float position_x_get(void)
{
    if (nullptr != posXMock)
    {
        return posXMock->call();
    }

    return 0.0f;
}

void posYMockSet(PositionGetMock *mock)
{
    posYMock = mock;
}

float position_y_get(void)
{
    if (nullptr != posYMock)
    {
        return posYMock->call();
    }

    return 0.0f;
}

void posAlphaMockSet(PositionGetMock *mock)
{
    posAlphaMock = mock;
}

float position_alpha_get(void)
{
    if (nullptr != posAlphaMock)
    {
        return posAlphaMock->call();
    }

    return 0.0f;
}

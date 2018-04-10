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

#include "mock_templates.hpp"
#include "position_mocks.hpp"

static PositionGetMock *posXMock = nullptr;
static PositionGetMock *posYMock = nullptr;
static PositionGetMock *posAlphaMock = nullptr;

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

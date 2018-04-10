/*
 * file:	motor_mocks.cpp
 * author:	GAndaLF
 * brief:	Mock functions for motor control task.
 */

#include "platform_specific.h"

extern "C"
{
    #include "motor/motor.h"
}

#include "mock_templates.hpp"
#include "motor_mocks.hpp"

static MotorAllOffMock *motorAllOffMock = nullptr;

void motorAllOffMockSet(MotorAllOffMock *mock)
{
    motorAllOffMock = mock;
}

void motor_all_off(void)
{
    if (nullptr != motorAllOffMock)
    {
        motorAllOffMock->call();
    }
}

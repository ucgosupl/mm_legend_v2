/*
 * file:	motor_mocks.hpp
 * author:	GAndaLF
 * brief:	Mock functions for motor control task.
 */

#ifndef _MOTOR_MOCKS_HPP_
#define _MOTOR_MOCKS_HPP_

class MotorAllOffMock
{
private:
    int32_t cnt_ = 0;

public:
    MotorAllOffMock() = default;

    int32_t getCount();
    void call();
};

void motorAllOffMockSet(MotorAllOffMock *mock);

#endif /* _MOTOR_MOCKS_HPP_ */

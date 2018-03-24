/*
 * file:	position_mocks.hpp
 * author:	GAndaLF
 * brief:	Mock functions for position module.
 */

#ifndef _POSITION_MOCKS_HPP_
#define _POSITION_MOCKS_HPP_

class PositionGetMock
{
private:
    int32_t cnt_ = 0;
    float retVal_ = 0.0f;

public:
    PositionGetMock() = default;
    PositionGetMock(float retVal);

    int32_t getCount();
    float call();
};

void posXMockSet(PositionGetMock *mock);
void posYMockSet(PositionGetMock *mock);

#endif /* _POSITION_MOCKS_HPP_ */

/*
 * file:	position_mocks.hpp
 * author:	GAndaLF
 * brief:	Mock functions for position module.
 */

#ifndef _POSITION_MOCKS_HPP_
#define _POSITION_MOCKS_HPP_

using PositionGetMock = RetNoArgMock<float>;

void posXMockSet(PositionGetMock *mock);
void posYMockSet(PositionGetMock *mock);
void posAlphaMockSet(PositionGetMock *mock);

#endif /* _POSITION_MOCKS_HPP_ */

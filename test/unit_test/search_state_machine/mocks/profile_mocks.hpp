/*
 * file:	search_mocks.hpp
 * author:	GAndaLF
 * brief:	Mock functions for search module.
 */

#ifndef _PROFILE_MOCKS_HPP_
#define _PROFILE_MOCKS_HPP_

using ProfileSearchTurnMoveMock = NoRetNoArgMock;
using ProfileSearchIsCompletedMock = RetNoArgMock<bool>;

void profileSearchTurnLeftMockSet(ProfileSearchTurnMoveMock *mock);
void profileSearchTurnRightMockSet(ProfileSearchTurnMoveMock *mock);
void profileSearchTurnAroundMockSet(ProfileSearchTurnMoveMock *mock);
void profileSearchMoveForwardMockSet(ProfileSearchTurnMoveMock *mock);

void profileSearchIsCompletedMockSet(ProfileSearchIsCompletedMock *mock);

#endif /* _PROFILE_MOCKS_HPP_ */

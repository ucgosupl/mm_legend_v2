/*
 * file:	search_mocks.hpp
 * author:	GAndaLF
 * brief:	Mock functions for search module.
 */

#ifndef _PROFILE_MOCKS_HPP_
#define _PROFILE_MOCKS_HPP_

class ProfileSearchTurnMoveMock
{
private:
    int32_t cnt_ = 0;

public:
    ProfileSearchTurnMoveMock() = default;

    int32_t getCount();

    void call();
};

void profileSearchTurnLeftMockSet(ProfileSearchTurnMoveMock *mock);
void profileSearchTurnRightMockSet(ProfileSearchTurnMoveMock *mock);
void profileSearchTurnAroundMockSet(ProfileSearchTurnMoveMock *mock);
void profileSearchMoveForwardMockSet(ProfileSearchTurnMoveMock *mock);

class ProfileSearchIsCompletedMock
{
private:
    int32_t cnt_ = 0;

    bool retVal_ = false;

public:
    ProfileSearchIsCompletedMock() = default;
    ProfileSearchIsCompletedMock(bool retVal);

    int32_t getCount();

    bool call();
};

void profileSearchIsCompletedMockSet(ProfileSearchIsCompletedMock *mock);

#endif /* _PROFILE_MOCKS_HPP_ */

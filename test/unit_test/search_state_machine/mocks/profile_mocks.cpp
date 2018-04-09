/*
 * file:    solver_mocks.cpp
 * author:  GAndaLF
 * brief:   Mock functions for solver module.
 */

#include "platform_specific.h"

extern "C"
{
    #include "profile/profile.h"
}

#include "mock_templates.hpp"
#include "profile_mocks.hpp"

static ProfileSearchTurnMoveMock *profileSearchTurnLeftMock = nullptr;
static ProfileSearchTurnMoveMock *profileSearchTurnRightMock = nullptr;
static ProfileSearchTurnMoveMock *profileSearchTurnAroundMock = nullptr;
static ProfileSearchTurnMoveMock *profileSearchMoveForwardMock = nullptr;

static ProfileSearchIsCompletedMock *profileSearchIsCompletedMock = nullptr;

void profileSearchTurnLeftMockSet(ProfileSearchTurnMoveMock *mock)
{
    profileSearchTurnLeftMock = mock;
}

void profile_search_turn_left(void)
{
    if (nullptr != profileSearchTurnLeftMock)
    {
        profileSearchTurnLeftMock->call();
    }
}

void profileSearchTurnRightMockSet(ProfileSearchTurnMoveMock *mock)
{
    profileSearchTurnRightMock = mock;
}

void profile_search_turn_right(void)
{
    if (nullptr != profileSearchTurnRightMock)
    {
        profileSearchTurnRightMock->call();
    }
}

void profileSearchTurnAroundMockSet(ProfileSearchTurnMoveMock *mock)
{
    profileSearchTurnAroundMock = mock;
}

void profile_search_turn_around(void)
{
    if (nullptr != profileSearchTurnAroundMock)
    {
        profileSearchTurnAroundMock->call();
    }
}

void profileSearchMoveForwardMockSet(ProfileSearchTurnMoveMock *mock)
{
    profileSearchMoveForwardMock = mock;
}

void profile_search_move_forward(void)
{
    if (nullptr != profileSearchMoveForwardMock)
    {
        profileSearchMoveForwardMock->call();
    }
}

void profileSearchIsCompletedMockSet(ProfileSearchIsCompletedMock *mock)
{
    profileSearchIsCompletedMock = mock;
}

bool profile_search_is_completed(void)
{
    if (nullptr != profileSearchIsCompletedMock)
    {
        return profileSearchIsCompletedMock->call();
    }

    return false;
}

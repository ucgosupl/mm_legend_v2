/*
 * file:    solver_mocks.cpp
 * author:  GAndaLF
 * brief:   Mock functions for solver module.
 */

#include "platform_specific.h"

extern "C"
{
    #include "search/search_internal.h"
}

#include "search_mocks.hpp"

static SearchIsWallBlockingMock *searchIsWallBlockingMock = nullptr;
static SearchNextMoveGetMock *searchNextMoveGetMock = nullptr;
static SearchIsFinalPathFoundMock *searchIsFinalPathFoundMock = nullptr;

SearchIsWallBlockingMock::SearchIsWallBlockingMock(bool retVal) : retVal_(retVal) {};

int32_t SearchIsWallBlockingMock::getCount()
{
    return cnt_;
}

int32_t SearchIsWallBlockingMock::getArg1()
{
    return arg1_;
}

int32_t SearchIsWallBlockingMock::getArg2()
{
    return arg2_;
}

bool SearchIsWallBlockingMock::call(int32_t id_current, int32_t id_next)
{
    cnt_++;

    arg1_ = id_current;
    arg2_ = id_next;

    return retVal_;
}

void searchIsWallBlockingMockSet(SearchIsWallBlockingMock *mock)
{
    searchIsWallBlockingMock = mock;
}

bool search_is_wall_blocking(int32_t id_current, int32_t id_next)
{
    if (nullptr != searchIsWallBlockingMock)
    {
        return searchIsWallBlockingMock->call(id_current, id_next);
    }

    return false;
}

SearchNextMoveGetMock::SearchNextMoveGetMock(search_move_t retVal) : retVal_(retVal) {};

int32_t SearchNextMoveGetMock::getCount()
{
    return cnt_;
}

int32_t SearchNextMoveGetMock::getArg1()
{
    return arg1_;
}

int32_t SearchNextMoveGetMock::getArg2()
{
    return arg2_;
}

search_move_t SearchNextMoveGetMock::call(int32_t id_current, int32_t id_next)
{
    cnt_++;

    arg1_ = id_current;
    arg2_ = id_next;

    return retVal_;
}

void searchNextMoveGetMockSet(SearchNextMoveGetMock *mock)
{
    searchNextMoveGetMock = mock;
}

search_move_t search_next_move_get(int32_t id_current, int32_t id_next)
{
    if (nullptr != searchNextMoveGetMock)
    {
        return searchNextMoveGetMock->call(id_current, id_next);
    }

    return SEARCH_MOVE_FORWARD;
}

SearchIsFinalPathFoundMock::SearchIsFinalPathFoundMock(bool retVal) : retVal_(retVal) {};

int32_t SearchIsFinalPathFoundMock::getCount()
{
    return cnt_;
}

bool SearchIsFinalPathFoundMock::call()
{
    cnt_++;

    return retVal_;
}

void searchIsFinalPathFoundMockSet(SearchIsFinalPathFoundMock *mock)
{
    searchIsFinalPathFoundMock = mock;
}

bool search_is_final_path_found(void)
{
    if (nullptr != searchIsFinalPathFoundMock)
    {
        return searchIsFinalPathFoundMock->call();
    }

    return false;
}

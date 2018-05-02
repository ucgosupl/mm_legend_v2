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

#include "mock_templates.hpp"
#include "search_mocks.hpp"

static SearchIsWallBlockingMock *searchIsWallBlockingMock = nullptr;
static SearchNextMoveGetMock *searchNextMoveGetMock = nullptr;
static SearchIsFinalPathFoundMock *searchIsFinalPathFoundMock = nullptr;

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

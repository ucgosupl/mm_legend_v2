/*
 * file:	search_mocks.hpp
 * author:	GAndaLF
 * brief:	Mock functions for search module.
 */

#ifndef _SEARCH_MOCKS_HPP_
#define _SEARCH_MOCKS_HPP_

class SearchIsWallBlockingMock
{
private:
    int32_t cnt_ = 0;

    int32_t arg1_ = -1;
    int32_t arg2_ = -1;

    bool retVal_ = -1;

public:
    SearchIsWallBlockingMock() = default;
    SearchIsWallBlockingMock(bool retVal);

    int32_t getCount();
    int32_t getArg1();
    int32_t getArg2();

    bool call(int32_t id_current, int32_t id_next);
};

void searchIsWallBlockingMockSet(SearchIsWallBlockingMock *mock);

class SearchNextMoveGetMock
{
private:
    int32_t cnt_ = 0;

    int32_t arg1_ = -1;
    int32_t arg2_ = -1;

    search_move_t retVal_ = -1;

public:
    SearchNextMoveGetMock() = default;
    SearchNextMoveGetMock(search_move_t retVal);

    int32_t getCount();
    int32_t getArg1();
    int32_t getArg2();

    search_move_t call(int32_t id_current, int32_t id_next);
};

void searchNextMoveGetMockSet(SearchNextMoveGetMock *mock);

class SearchIsFinalPathFoundMock
{
private:
    int32_t cnt_ = 0;

    bool retVal_ = -1;

public:
    SearchIsFinalPathFoundMock() = default;
    SearchIsFinalPathFoundMock(bool retVal);

    int32_t getCount();

    bool call();
};

void searchIsFinalPathFoundMockSet(SearchIsFinalPathFoundMock *mock);

#endif /* _SEARCH_MOCKS_HPP_ */

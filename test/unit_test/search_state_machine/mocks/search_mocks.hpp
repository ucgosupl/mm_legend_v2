/*
 * file:	search_mocks.hpp
 * author:	GAndaLF
 * brief:	Mock functions for search module.
 */

#ifndef _SEARCH_MOCKS_HPP_
#define _SEARCH_MOCKS_HPP_

using SearchIsWallBlockingMock = Ret2ArgMock<bool, int32_t, int32_t>;
using SearchNextMoveGetMock = Ret2ArgMock<search_move_t, int32_t, int32_t>;
using SearchIsFinalPathFoundMock = RetNoArgMock<bool>;

void searchIsWallBlockingMockSet(SearchIsWallBlockingMock *mock);

void searchNextMoveGetMockSet(SearchNextMoveGetMock *mock);

void searchIsFinalPathFoundMockSet(SearchIsFinalPathFoundMock *mock);

#endif /* _SEARCH_MOCKS_HPP_ */

/*
 * file:	solver_mocks.hpp
 * author:	GAndaLF
 * brief:	Mock functions for solver module.
 */

#ifndef _SOLVER_MOCKS_HPP_
#define _SOLVER_MOCKS_HPP_

using SolverCalcPathMock = NoRetNoArgsMock;
using SolverCellNextGetMock = Ret1ArgMock<int32_t, int32_t>;

void solverCalcPathToCenterMockSet(SolverCalcPathMock *mock);
void solverCalcPathToStartMockSet(SolverCalcPathMock *mock);

void solverCellNextGetMockSet(SolverCellNextGetMock *mock);

#endif /* _SOLVER_MOCKS_HPP_ */

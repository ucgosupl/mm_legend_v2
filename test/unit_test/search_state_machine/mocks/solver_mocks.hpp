/*
 * file:	solver_mocks.hpp
 * author:	GAndaLF
 * brief:	Mock functions for solver module.
 */

#ifndef _SOLVER_MOCKS_HPP_
#define _SOLVER_MOCKS_HPP_

class SolverCalcPathMock
{
private:
    int32_t cnt_ = 0;

public:
    SolverCalcPathMock() = default;

    int32_t getCount();
    void call();
};

void solverCalcPathToCenterMockSet(SolverCalcPathMock *mock);
void solverCalcPathToStartMockSet(SolverCalcPathMock *mock);

class SolverCellNextGetMock
{
private:
    int32_t cnt_ = 0;
    int32_t arg1_ = -1;
    int32_t retVal_ = -1;

public:
    SolverCellNextGetMock() = default;
    SolverCellNextGetMock(int32_t retVal);

    int32_t getCount();
    int32_t getArg1();
    int32_t call(int32_t cell_id);
};

void solverCellNextGetMockSet(SolverCellNextGetMock *mock);

#endif /* _SOLVER_MOCKS_HPP_ */

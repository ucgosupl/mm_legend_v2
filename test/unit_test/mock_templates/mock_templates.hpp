/*
 * file:	mock_templates.hpp
 * author:	GAndaLF
 * brief:	Template for creating mocks.
 */

#ifndef _MOCK_TEMPLATES_HPP_
#define _MOCK_TEMPLATES_HPP_

class BaseMock
{
protected:
    int32_t cnt_ = 0;

public:
    int32_t getCount() {return cnt_;}
};

class NoRetNoArgsMock : public BaseMock
{
public:
    void call() {cnt_++;}
};

template <typename TArg1>
class NoRet1ArgMock : public BaseMock
{
private:
    TArg1 arg1_ = 0;

public:
    TArg1 getArg1() {return arg1_;}

    void call(TArg1 arg1) {cnt_++; arg1_ = arg1;}
};

template <typename TRet, typename TArg1, typename TArg2>
class NoRet2ArgMock : public BaseMock
{
private:
    TArg1 arg1_ = 0;
    TArg2 arg2_ = 0;

public:
    TArg1 getArg1() {return arg1_;}
    TArg1 getArg2() {return arg2_;}

    void call(TArg1 arg1, TArg2 arg2) {cnt_++; arg1_ = arg1; arg2_ = arg2;}
};

template <typename TRet>
class RetNoArgMock : public BaseMock
{
private:
    TRet retVal_;

public:
    RetNoArgMock() = default;
    RetNoArgMock(TRet retVal) : retVal_(retVal) {}
    TRet call() {cnt_++; return retVal_;}
};

template <typename TRet, typename TArg1>
class Ret1ArgMock : public BaseMock
{
private:
    TArg1 arg1_ = 0;

    TRet retVal_;

public:
    Ret1ArgMock() = default;
    Ret1ArgMock(TRet retVal) : retVal_(retVal) {}

    TArg1 getArg1() {return arg1_;}

    TRet call(TArg1 arg1) {cnt_++; arg1_ = arg1; return retVal_;}
};

template <typename TRet, typename TArg1, typename TArg2>
class Ret2ArgMock : public BaseMock
{
private:
    TArg1 arg1_ = 0;
    TArg2 arg2_ = 0;

    TRet retVal_;

public:
    Ret2ArgMock() = default;
    Ret2ArgMock(TRet retVal)  : retVal_(retVal) {}

    TArg1 getArg1() {return arg1_;}
    TArg1 getArg2() {return arg2_;}

    TRet call(TArg1 arg1, TArg2 arg2) {cnt_++; arg1_ = arg1; arg2_ = arg2; return retVal_;}
};

#endif /* _MOCK_TEMPLATES_HPP_ */

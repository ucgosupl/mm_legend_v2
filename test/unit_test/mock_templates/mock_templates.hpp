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

class NoRetNoArgMock : public BaseMock
{
public:
    void call() {cnt_++;}
};

template <typename TArg1>
class NoRet1ArgMock : public BaseMock
{
protected:
    TArg1 arg1_ = TArg1();

public:
    TArg1 getArg1() {return arg1_;}

    void call(TArg1 arg1) {cnt_++; arg1_ = arg1;}
};

template <typename TArg1, typename TArg2>
class NoRet2ArgMock : public BaseMock
{
protected:
    TArg1 arg1_ = TArg1();
    TArg2 arg2_ = TArg2();

public:
    TArg1 getArg1() {return arg1_;}
    TArg2 getArg2() {return arg2_;}

    void call(TArg1 arg1, TArg2 arg2) {cnt_++; arg1_ = arg1; arg2_ = arg2;}
};

template <typename TArg1, typename TArg2, typename TArg3>
class NoRet3ArgMock : public BaseMock
{
protected:
    TArg1 arg1_ = TArg1();
    TArg2 arg2_ = TArg2();
    TArg3 arg3_ = TArg3();

public:
    TArg1 getArg1() {return arg1_;}
    TArg2 getArg2() {return arg2_;}
    TArg3 getArg3() {return arg3_;}

    void call(TArg1 arg1, TArg2 arg2, TArg3 arg3) {cnt_++; arg1_ = arg1; arg2_ = arg2; arg3_ = arg3;}
};

template <typename TRet>
class RetNoArgMock : public BaseMock
{
protected:
    TRet retVal_;

public:
    RetNoArgMock() = default;
    RetNoArgMock(TRet retVal) : retVal_(retVal) {}
    TRet call() {cnt_++; return retVal_;}
};

template <typename TRet, typename TArg1>
class Ret1ArgMock : public BaseMock
{
protected:
    TArg1 arg1_ = TArg1();

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
protected:
    TArg1 arg1_ = TArg1();
    TArg2 arg2_ = TArg2();

    TRet retVal_;

public:
    Ret2ArgMock() = default;
    Ret2ArgMock(TRet retVal)  : retVal_(retVal) {}

    TArg1 getArg1() {return arg1_;}
    TArg2 getArg2() {return arg2_;}

    TRet call(TArg1 arg1, TArg2 arg2) {cnt_++; arg1_ = arg1; arg2_ = arg2; return retVal_;}
};

template <typename TRet, typename TArg1, typename TArg2, typename TArg3>
class Ret3ArgMock : public BaseMock
{
protected:
    TArg1 arg1_ = TArg1();
    TArg2 arg2_ = TArg2();
    TArg3 arg3_ = TArg3();

    TRet retVal_;

public:
    Ret3ArgMock() = default;
    Ret3ArgMock(TRet retVal)  : retVal_(retVal) {}

    TArg1 getArg1() {return arg1_;}
    TArg2 getArg2() {return arg2_;}
    TArg3 getArg3() {return arg3_;}

    TRet call(TArg1 arg1, TArg2 arg2, TArg3 arg3) {cnt_++; arg1_ = arg1; arg2_ = arg2; arg3_ = arg3; return retVal_;}
};

#endif /* _MOCK_TEMPLATES_HPP_ */

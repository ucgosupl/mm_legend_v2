/*
 * file:	led_mocks.hpp
 * author:	GAndaLF
 * brief:	Mock functions for LED hardware driver.
 */

#ifndef _LED_MOCKS_HPP_
#define _LED_MOCKS_HPP_

using LedOnOffMock = NoRet1ArgMock<int32_t>;
using LedAllOffMock = NoRetNoArgMock;

void ledOnMockSet(LedOnOffMock *mock);
void ledOffMockSet(LedOnOffMock *mock);

void ledAllOffMockSet(LedAllOffMock *mock);

#endif /* _LED_MOCKS_HPP_ */

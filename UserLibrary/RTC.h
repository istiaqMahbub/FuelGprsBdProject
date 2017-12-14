// RTC.h

#ifndef _RTC_h
#define _RTC_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif
void RTCInit();
void RTCGettingData();

#endif


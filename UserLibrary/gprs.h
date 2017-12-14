// gprs.h

#ifndef _GPRS_h
#define _GPRS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

class GprsClass
{
 public:
	void init();
	void sendSms(String sms);
};

extern GprsClass;// Gprs;

#endif


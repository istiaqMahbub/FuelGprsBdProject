// batteryVoltage.h

#ifndef _BATTERYVOLTAGE_h
#define _BATTERYVOLTAGE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

class VoltageClass
{
	public:
		//void init(int channel);
		int getVal(int channel);
		float getAvgVal(int channel);
		void showVal(float mulFact);
 
};

extern VoltageClass;
//extern VoltageClass BatteryVoltage;
//extern VoltageClass FuelValue;

#endif


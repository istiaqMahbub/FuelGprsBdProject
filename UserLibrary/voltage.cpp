// 
// 
// 

#include "voltage.h"

double tempVal = 0;

int VoltageClass::getVal (int channel){
	int value = analogRead(channel);
	return(value);
}

float VoltageClass::getAvgVal(int channel){
	tempVal = 0;
	for (int i=0; i<40; i++)
	{
		tempVal += analogRead(channel);
	}
	return(tempVal /= 40);
}
void VoltageClass::showVal(float mulFact){
	Serial.print("Battery Voltage = ");
	Serial.print(tempVal * mulFact);
	Serial.println(" V");
}

//BatteryVoltageClass BatteryVoltage;


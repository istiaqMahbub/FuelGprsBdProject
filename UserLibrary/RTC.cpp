// 
// 
// 

#include "RTC.h"
#include <Wire.h>
#include "RTClib-master/RTClib.h"

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

//EXTERNAL RTC_DS1307 rtc;
RTC_DS1307 rtc;
void RTCGettingData()
{
	DateTime now = rtc.now();
	Serial.print(now.year(), DEC);
	Serial.print('/');
	Serial.print(now.month(), DEC);
	Serial.print('/');
	Serial.print(now.day(), DEC);
	Serial.print(" (");
	Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
	Serial.print(") ");
	Serial.print(now.hour(), DEC);
	Serial.print(':');
	Serial.print(now.minute(), DEC);
	Serial.print(':');
	Serial.print(now.second(), DEC);
	Serial.println();
	
}

void RTCInit()
{
	//RTC Started
	rtc.begin();
	//RTC Settings
	// following line sets the RTC to the date & time this sketch was compiled
	// You can set only below line and it will take data from pc
	rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
	// This line sets the RTC with an explicit date & time, for example to set
	// January 21, 2014 at 3am you would call:
	// rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
}



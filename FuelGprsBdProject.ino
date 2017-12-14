
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include "TimerOne-r11/TimerOne.h"
#include "UserLibrary/voltage.h"
#include "UserLibrary/gprs.h"
#include "UserLibrary/RTC.h"
#include "RTClib-master/RTClib.h"


//Object declaration
VoltageClass BatteryVoltage;
VoltageClass FuelValue;
//LiquidCrystal(rs, enable, d4, d5, d6, d7)
//SoftwareSerial SIM900(10, 11); // RX, TX 
GprsClass gprs;
extern RTC_DS1307 rtc;

#define genOn digitalWrite(powerdownpin,HIGH);
#define genOff digitalWrite(powerdownpin,LOW);
 
const byte interruptPin	= 2; // No:2 pin as interrupt
const byte powerdownpin = 13;// No:13 pin of arduino board as led

//Global variable declaration
volatile uint16_t tick;
volatile byte timerStateFlag = 0;	
volatile byte sendSmsFlag = 0;
 
//Function declaration 
void Initialize();
void PowerDown();
void Callback();
 
void setup()
{
  /* add setup code here */
	Initialize();
}

void loop()
{
  /* add main program code here */
	if(sendSmsFlag == 1){
		sendSmsFlag = 0;
		//This thing for sending the SMS 
		String data = "Gen Run:" + ((String)(tick/60)) + " Min, " + ((String)(tick%60)) + " Sec";
		//If want to send data through sms
		//gprs.sendSms(data);
		Serial.println(data);
	}
	RTCGettingData();
}

void Initialize(){
	//When want to use GPRS
	//gprs.init();
	Serial.begin(9600);
	//lcd.begin(16,2);
	//lcd.print("Hello");
	pinMode(interruptPin, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(interruptPin), PowerDown, CHANGE);
	//Power switching pin setting as output
	pinMode(powerdownpin,OUTPUT);
	//Timer Initialize as 1/2 sec for 16Mhz
	Timer1.initialize(1000000);
	//Timer interrupt calling
	Timer1.attachInterrupt(Callback);
	//Initially generator is off 
	genOff;
	//RTC Started
/*	rtc.begin();
	//RTC Settings
	// following line sets the RTC to the date & time this sketch was compiled
	// You can set only below line and it will take data from pc
	rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
	// This line sets the RTC with an explicit date & time, for example to set
	// January 21, 2014 at 3am you would call:
	// rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));*/
	RTCInit();
}

void PowerDown(){
	
	Serial.println("Ext Interrupt");
	// Giving a delay because by doing it manually there occurs lot of interrupt
	// In real situation, I think we dont need delay
	// Actually for false interrupt time(tick-Variable) goes to 0
	for(unsigned int i = 0; i<19000; i++){
		__asm__("nop\n\t""nop\n\t""nop\n\t""nop\n\t"); 
	}
	//If the pin is LOW --- Thats mean electricity is not available 
	if(!(digitalRead(interruptPin))){
		Serial.println("CHANGE");
		genOn;
		timerStateFlag = 1;
		tick = 0 ;	
	}
	//If the pin is HIGH --- Thats mean electricity is available 
	else{
		genOff;
		timerStateFlag = 0;
		sendSmsFlag = 1;
	}
}

void Callback(){
	if(timerStateFlag == 1){
		tick++;
		Serial.println(tick);	
	}
}
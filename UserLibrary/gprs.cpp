// 
// 
// 

#include "gprs.h"
#include <SoftwareSerial.h>

SoftwareSerial sim900(10, 11); // RX, TX 

void GprsClass::init(){
	// Arduino communicates with SIM900 GSM shield at a baud rate of 19200
	// Make sure that corresponds to the baud rate of your module
	sim900.begin(19200);
	// Give time to your GSM shield log on to network
	delay(20000);
}

void GprsClass::sendSms(String sms)
{
	 // AT command to set SIM900 to SMS mode
	 sim900.print("AT+CMGF=1\r");
	 delay(100);
	 
	 // REPLACE THE X's WITH THE RECIPIENT'S MOBILE NUMBER
	 // USE INTERNATIONAL FORMAT CODE FOR MOBILE NUMBERS
	 sim900.println("AT + CMGS = \"+88XXXXXXXXXX\"");
	 delay(100);
	 
	 // REPLACE WITH YOUR OWN SMS MESSAGE CONTENT
	 sim900.println(sms);
	 delay(100);
	 
	 // End AT command with a ^Z, ASCII code 26
	 sim900.println((char)26);
	 delay(100);
	 sim900.println();
	 // Give module time to send SMS
	 delay(5000);
}


//GprsClass Gprs;


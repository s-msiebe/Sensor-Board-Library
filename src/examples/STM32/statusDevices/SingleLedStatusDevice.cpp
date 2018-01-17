#include "SingleLedStatusDevice.h"

SingleLedStatusDevice::SingleLedStatusDevice(int ledPin)
{
	this->ledPin = ledPin;
}

bool SingleLedStatusDevice::begin()
{
  pinMode(ledPin, OUTPUT);
  return true;
}

bool SingleLedStatusDevice::loop()
{
	
	int currentTime = millis();
			
	if(startTimeLedOn == -1)
	{
		startTimeLedOn = currentTime;
	}
	
	currentTimeLedOn = (currentTime - startTimeLedOn);
	
	switch(currentStatus)
	{
		case Status::OK:
			ledStatus = LOW;
			startTimeLedOn = -1;
			break;
			
		case Status::SETUP_MODE:
			if(currentTimeLedOn > 1000)
			{
				ledStatus = !ledStatus;
				startTimeLedOn = -1;
			}
			break;
		
		case Status::LINKING:
			if(currentTimeLedOn > 50)
			{
				ledStatus = !ledStatus;
				startTimeLedOn = -1;
			}
			break;
		
		case Status::ERROR:
			if(currentTimeLedOn > 5000)
			{
				ledStatus = !ledStatus;
				startTimeLedOn = -1;
			}
			break;
			
		case Status::SEND_MQTT_MESSAGE:
			if(currentTimeLedOn > 100)
			{
				ledStatus = !ledStatus;
				startTimeLedOn = -1;
			}
			break;
			
		case Status::EMPTY:
			if(currentTimeLedOn > 10)
			{
				ledStatus = !ledStatus;
				startTimeLedOn = -1;
			}
			break;
			
		default:
			ledStatus = LOW;
	}
	
	digitalWrite(ledPin, ledStatus);
	
	return true;
	
}


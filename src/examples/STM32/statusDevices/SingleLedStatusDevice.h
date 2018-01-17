#ifndef SINGLE_LED_STATUS_DEVICE_H
#define SINGLE_LED_STATUS_DEVICE_H  

#include <StatusDevice.h>
#include <Arduino.h>

class SingleLedStatusDevice : public StatusDevice
{
	private:
		int ledPin;
		int currentTimeLedOn = 0;
		int startTimeLedOn = -1;
		int ledStatus = LOW;
	
	public:
		SingleLedStatusDevice(int ledPin);
		
		bool begin();

		bool loop();
	
};

#endif //SINGLE_LED_STATUS_DEVICE_H

#ifndef PULL_UP_SETUP_BUTTON_DEVICE_H
#define PULL_UP_SETUP_BUTTON_DEVICE_H  

#include <SetupButtonDevice.h>
#include <Arduino.h>

class PullUpSetupButtonDevice : public SetupButtonDevice
{
	private:
		int buttonPin;
	
	public:
		PullUpSetupButtonDevice(int buttonPin);
		
		bool begin();
		
		bool loop();
		
        bool isPressed();
		
};

#endif //PULL_UP_SETUP_BUTTON_DEVICE_H

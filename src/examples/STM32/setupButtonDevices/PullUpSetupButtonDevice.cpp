#include <PullUpSetupButtonDevice.h>

PullUpSetupButtonDevice::PullUpSetupButtonDevice(int buttonPin)
{
	this->buttonPin = buttonPin;
}

bool PullUpSetupButtonDevice::begin()
{
  pinMode(buttonPin, INPUT_PULLUP);
  return true;
}

bool PullUpSetupButtonDevice::isPressed()
{
	int buttonState = digitalRead(buttonPin); 
	
	if(buttonState == LOW)
		return true;
	else
		return false;
}

bool PullUpSetupButtonDevice::loop()
{
	return true;
}


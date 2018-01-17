#ifndef BRIGHTNESS_SENSOR_HPP
#define BRIGHTNESS_SENSOR_HPP  

#include <SensorDevice.h>
#include <ArduinoJson.h>
#include <stdio.h>

class BrightnessSensor : public SensorDevice
{
	private:
		//TwoWire wire1(1);
		//Adafruit_TSL2561_Unified tslSensor = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345);
		int refTime = 0; 

    public:
        bool begin();
        bool loop();
        JsonObject& getValueToSendAsJson(DynamicJsonBuffer& buffer);
		JsonArray& getTypeAsJson(DynamicJsonBuffer& buffer);
};

#endif //BRIGHTNESS_SENSOR_HPP
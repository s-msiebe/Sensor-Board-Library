#ifndef EMPTY_TEST_RADIO_DEVICE_H  
#define EMPTY_TEST_RADIO_DEVICE_H

#include <RadioDevice.h>
#include <Arduino.h>


class EmptyTestRadioDevice : public RadioDevice
{
  private:
	 char *radioConfig;
		
    public:
		EmptyTestRadioDevice();
        bool begin();
        bool loop();
        bool startRadioDevice();
        bool stopRadioDevice();
        int getMaxMessageLength();
        JsonVariant getTypeAsJson(DynamicJsonBuffer& buffer);
        JsonObject& getConfigAsJson(DynamicJsonBuffer& buffer);
        void setServerConfig(JsonObject& jsonConfig);
        bool sendMessage(String &buffer);
        bool connect();
};


#endif //EMPTY_TEST_RADIO_DEVICE_H

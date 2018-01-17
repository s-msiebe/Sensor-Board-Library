#ifndef STM32_EEPROM_H
#define STM32_EEPROM_H  

#include <StorageDevice.h>
#include <Arduino.h>
#include <ArduinoJson.h>
#include <EEPROM.h>

class Stm32EEPROM : public StorageDevice
{
	public:
	
		String readFromStorage(String key);
		
		bool writeInStorage(String key, String value);
		
		bool removeFromStorage(String key);
		
	private:
		bool saveJsonInEeprom(JsonObject& json);
		
		JsonObject& readJsonFromEeprom(DynamicJsonBuffer& jsonBuffer);
	
};

#endif //STM32_EEPROM_H

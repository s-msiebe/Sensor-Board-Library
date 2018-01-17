#ifndef EMPTY_EEPROM_H
#define EMPTY_EEPROM_H  

#include <StorageDevice.h>

class EmptyEEPROM : public StorageDevice
{
	public:
		String readFromStorage(String key);
		
		bool writeInStorage(String key, String value);
		
		bool removeFromStorage(String key);
	
};

#endif //EMPTY_EEPROM_H

#ifndef LINKEDIOT_STORAGEDEVICE_H
#define LINKEDIOT_STORAGEDEVICE_H

#include <Arduino.h>

class StorageDevice
{
    public:
		/*!
         * Returns the value to the associated key from memory.
         *
         * @param[in] key	key of the value
         *
         * @return value
         */
		virtual String readFromStorage(String key) = 0;
		
		/*!
		 * Permanently saves the value with the associated key in memory.
         *
         * @retval TRUE     Value saved successfully
         * @retval FALSE    Value could't be saved
         */
		virtual bool writeInStorage(String key, String value) = 0;
		
		/*!
         * Removes the value from the memory.
         *
         * @retval TRUE     Value removed successfully
         * @retval FALSE    Value could't be removed
         */
		virtual bool removeFromStorage(String key) = 0;
};


#endif //LINKEDIOT_STORAGEDEVICE_H

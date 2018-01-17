#ifndef LINKEDIOT_SENSORDEVICE_H
#define LINKEDIOT_SENSORDEVICE_H

#include <ArduinoJson.h>

class SensorDevice
{
    public:
        /*!
         * Initialization of the sensor and determination of the output-mode.
         *
         * @retval TRUE     Successful initialization
         * @retval FALSE    Sensor could not be initialized
         */
        virtual bool begin() = 0;

        /*!
         * Is called for every run.
         */
        virtual bool loop() = 0;

        /*!
         * Returns the current value of the sensor as Json-object.
         *
         * @return Current value as Json-object
         */
        virtual JsonObject& getValueToSendAsJson(DynamicJsonBuffer& buffer) = 0;
        
        /*!
         * Returns the type of the sensor as Json-object.
         *
         * @return Type as Json-object
         */
        virtual JsonArray& getTypeAsJson(DynamicJsonBuffer& buffer) = 0;
};


#endif //LINKEDIOT_SENSORDEVICE_H

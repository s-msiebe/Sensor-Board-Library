#ifndef LINKEDIOT_STATUSDEVICE_H
#define LINKEDIOT_STATUSDEVICE_H

#include <Arduino.h>

enum class Status {OK, SETUP_MODE, LINKING, ERROR, SEND_MQTT_MESSAGE, EMPTY};


class StatusDevice
{
    public:
        Status currentStatus;
        
    public:
        /*!
         * Initialization of the status and definition of the output-mode. 
         *
         * @retval TRUE     Successful initialization
         * @retval FALSE    Status could not be initialized
         */
        virtual bool begin() = 0;

        /*!
         * Is called in every turn and returns the current status.
         */
        virtual bool loop() = 0;

        /*!
         * Sets the status.
         *
         * @param[in] status -> the status to be set
         */
        void setStatus(Status status);
};


#endif //LINKEDIOT_STATUSDEVICE_H

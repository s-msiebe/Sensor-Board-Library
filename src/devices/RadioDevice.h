#ifndef LINKEDIOT_RADIODEVICE_H
#define LINKEDIOT_RADIODEVICE_H

#include <ArduinoJson.h>

class RadioDevice
{
    public:
        /*!
         * Initialization of radio module.
         *
         * @retval TRUE     Successful initialization
         * @retval FALSE    Radio module could not be initialized
         */
        virtual bool begin() = 0;
		
		/*!
         * Is called for every run.
         */
        virtual bool loop() = 0;

        /*!
         * Radio module is started.
         *
         * @retval TRUE     Successful start
         * @retval FALSE    Radio module could not be started
         */
        virtual bool startRadioDevice() = 0;

        /*!
         * Radio module is stopped.
         *
         * @retval TRUE     Successful Stop
         * @retval FALSE    Radio module could not be stopped
         */
        virtual bool stopRadioDevice() = 0;

        /*!
         * Returns the maximum length of the messages that can be sent by the radio module.
         *
         * @return maximum message-length
         */
        virtual int getMaxMessageLength() = 0;

        /*!
         * Returns the type of the radio module as Json-object.
         *
         * @return type as Json-object
         */
        virtual JsonVariant getTypeAsJson(DynamicJsonBuffer& buffer) = 0;
		
        /*!
         * Returns the configuration of the radio module as Json-object.
         *
         * @return configuration as Json-object
         */
        virtual JsonObject& getConfigAsJson(DynamicJsonBuffer& buffer) = 0;

        /*!
         * Sets the configuration of the radio module. 
         *
         * @param[in] jsonConfig configuration of the radio module
         */
        virtual void setServerConfig(JsonObject& jsonConfig) = 0;

        /*!
         * Sends the message to the server.
         *
         * @param[in] buffer the sending message
         *
         * @retval TRUE     Message sent successfully
         * @retval FALSE    Message could not be sent
         */
        virtual bool sendMessage(String &buffer) = 0;
         
         /*!
         * The connection to the server is being established.
         *
         * @retval TRUE     Connection is established successfully
         * @retval FALSE    Connection could not be established
         */
        virtual bool connect() = 0;
};


#endif //LINKEDIOT_RADIODEVICE_H

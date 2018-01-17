#ifndef LINKEDIOT_SENSORBOARDDEVICE_H
#define LINKEDIOT_SENSORBOARDDEVICE_H

#include <StatusDevice.h>
#include <SetupButtonDevice.h>
#include <RadioDevice.h>
#include <SensorDevice.h>
#include <StorageDevice.h>
#include <SmallHttp.h>

class SensorBoardDevice
{
    private:
        StatusDevice *status;
        SetupButtonDevice *setupButton;
        SensorDevice *sensor;
		
		StorageDevice *storage;

        RadioDevice *radioModul;
        HttpConnection *connection;
		Stream* connectionStream;

        int setupModePressTime = 4;
        int resetPressTime = 10;

        char *uuid;
        bool setupMode = false;
		int startPressTime = -1;
		int currentPressTime = 0;

    public:
        SensorBoardDevice();
        ~SensorBoardDevice();

        /*!
         * Initialization of the sensor-board.
         *
         * @retval TRUE     Successful initialization
         * @retval FALSE    Sensor-Board could not be initialized
         */
        bool begin();

        /*!
         * This method is run through in every loop in the ino-file.
         *
         * @retval TRUE     Method ran through successfully
         * @retval FALSE    Method failed to run through
         */
        bool loop();

        /*!
         * Sending a message via the radio-module.
         *
         * @param buffer The message to be sent
         * @retval TRUE     Message was sent successfully
         * @retval FALSE    Message could not be sent
         */
        bool sendMessage(String &buffer);
		
    private:
        /*!
         * If the board is in the setup-mode, this method will be run through.
         *
         * @retval TRUE     Method ran through successfully
         * @retval FALSE    Method failed to run through
         */
        bool runSetupMode();

        /*!
         * If the board is resetted, this method will be run through.
         *
         * @retval TRUE     Method ran through successfully
         * @retval FALSE    Method failed to run through
         */
        bool runResetMode();

        /*!
         * Starting the setup-mode.
         *
         * @retval TRUE     Setup-mode was started successfully
         * @retval FALSE    Setup-mode could not be started
         */
        bool startSetupMode();

        /*!
         * Ending the Setup-mode.
         *
         * @retval TRUE     Setup-mode was ended successfully
         * @retval FALSE    Setup-mode could not be ended
         */
        bool endSetupMode();

    public:
		/*!
         * Returns the device for the output of the status.
         *
         * @return statusDevice
         */
        StatusDevice &getStatus();
		/*!
         * Sets the device for the output of the status.
		 *
		 * @param[in] status StatusDevice to be set
         */
		void setStatus(StatusDevice &status);
		
		/*!
         * Returns the button that starts the setup-mode.
         *
         * @return setupButton
         */
        SetupButtonDevice &getSetupButton();
		/*!
         * Sets the button that starts the setup-mode.
		 *
		 * @param[in] setupButton SetupButton to be set
         */
        void setSetupButton(SetupButtonDevice &setupButton);
		
		/*!
         * Returns the radio-module that is used for the connection to the bridge.
         *
         * @return radioModul
         */
        RadioDevice &getRadioModul();
		/*!
         * Sets the radio-module that is used for the connection to the bridge.
		 *
		 * @param[in] radioModul Radio-module to be set
         */
        void setRadioModul( RadioDevice &radioModul);
		
		/*!
         * Returns the sensor that is installed on the sensor-board.
         *
         * @return sensor
         */
		SensorDevice &getSensor();
		/*!
         * Sets the sensor that is installed on the sensor-board.
		 *
		 * @param[in] sensor Sensor to be set
         */
        void setSensor(SensorDevice &sensor);
		
		/*!
		 * Returns the memory, which stored the data permanently.
         *
         * @return storage
         */
        StorageDevice &getStorageDevice();
		/*!
         * Sets the memory, which stored the data permanently.
		 *
		 * @param[in] storage to be set
         */
        void setStorageDevice(StorageDevice &storage);
		
		/*!
         * Returns the http-connection that is used for the connection to the gateway.
         *
         * @return connection
         */
        Stream &getConnectionStream();
		/*!
         * Sets the http-connection that is used for the connection to the gateway.
		 *
		 * @param[in] connection HttpConnection to be set
         */
        void setConnectionStream(Stream *stream);

		/*!
         * Returns the amount of seconds that the button needs to be pressed to enter the setup-mode.
         *
         * @return Time in seconds
         */
        int getSetupModePressTime();
		/*!
         * Sets the amount of seconds that the button needs to be pressed to enter the setup-mode.
		 * Therefore the time for the setup-mode needs to be shorter than the time for the reset-mode.
		 *
		 * @param[in] pressTime Time in seconds
         */
        void setSetupModePressTime(int pressTime);

		/*!
         * Returns the amount of seconds that the button needs to be pressed to enter the reset-mode.
         *
         * @return Time in seconds
         */
        int getResetPressTime();
		/*!
         * Sets the amount of seconds that the button needs to be pressed to enter the reset-mode.
		 * Therefore the time for the reset-mode needs to be longer than the time for the setup-mode.
		 *
		 * @param[in] pressTime Time in seconds
         */
        void setResetPressTime(int pressTime);

		/*!
         * Returns the UUID of the device.
         *
         * @return uuid
         */
        char *getUuid();
		/*!
         * Sets the UUID of the device.
		 *
		 * @param[in] uuid UUID to be set
         */
        void setUuid(const char *uuid);

		/*!
         * Indicating if the sensor-board is in setup-mode.
		 *
         * @retval TRUE     Sensor-Board is in setup-mode
         * @retval FALSE    Sensor-Board is not in setup-mode
         */
        bool isInSetupMode();
		
		/*!
         * Returns the JsonLD-context of the Sensor-Board.
         *
         * @return context as JsonObject
         */
		JsonObject& getContextAsJson(JsonBuffer& buffer);
};


#endif //LINKEDIOT_SENSORBOARDDEVICE_H

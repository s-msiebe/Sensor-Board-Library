#ifndef LINKEDIOT_SETUPBUTTONDEVICE_H
#define LINKEDIOT_SETUPBUTTONDEVICE_H


class SetupButtonDevice
{
    public:
        /*!
         * Initialization of the button and determination of the input-mode for the button.
         *
         * @retval TRUE     Initialization successful
         * @retval FALSE    Button could not be initialized
         */
        virtual bool begin() = 0;

        /*!
         * Is called for every run.
         */
        virtual bool loop() = 0;
		
		/*!
         * Returns, if the button is pressed.
         *
         * @retval TRUE     Button is pressed
         * @retval FALSE    Button is not pressed
         */
        virtual bool isPressed() = 0;
};


#endif //LINKEDIOT_SETUPBUTTONDEVICE_H

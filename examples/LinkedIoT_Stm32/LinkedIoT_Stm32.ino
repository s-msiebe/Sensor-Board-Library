#include <SingleLedStatusDevice.h>
#include <PullUpSetupButtonDevice.h>
#include <EmptyTestRadioDevice.h>
#include <BrightnessSensor.h>
#include <EmptyEEPROM.h>
#include <STM32SensorBoard.h>


SingleLedStatusDevice statusLed(PC13);
PullUpSetupButtonDevice setupButton(PA0);
EmptyTestRadioDevice emptyRadio;
EmptyEEPROM emptyEeprom;
BrightnessSensor brightnessSensor;
STM32SensorBoard sensorboard;


void setup() 
{
  sensorboard.setStatus(statusLed);
  sensorboard.setSetupButton(setupButton);
  sensorboard.setRadioModul(emptyRadio);
  sensorboard.setSensor(brightnessSensor);
  sensorboard.setConnectionStream(&Serial);
  sensorboard.setSetupModePressTime(4);
  sensorboard.setResetPressTime(10);
  sensorboard.setStorageDevice(emptyEeprom);
  
  
  
  sensorboard.begin();
}

void loop() 
{
  sensorboard.loop();
}

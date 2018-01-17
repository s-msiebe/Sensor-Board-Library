#define SENSORTYPE "[\"Device\",\"BrightnessSensor\"]"

#include "BrightnessSensor.h"


bool BrightnessSensor::begin()
{
    /*
	if(!tslSensor.begin(&wire1)) 
	{
      return false;
    } else 
	{
      tslSensor.enableAutoRange(true);
      tslSensor.setIntegrationTime(TSL2561_INTEGRATIONTIME_402MS);
      return true;
    }
	*/
	
	return true;
}

bool BrightnessSensor::loop()
{
	return true;
}

JsonObject& BrightnessSensor::getValueToSendAsJson(DynamicJsonBuffer& buffer)
{
  /*int currentTime = millis();

  if(refTime = 0)
      refTime = currentTime;

  if(currentTime-refTime < 1 * 1000 * 60){
      refTime = 0;
      return NULL;
  }
    
  JsonObject& json = buffer.createObject();

  // TLS2561 Sensor
  sensors_event_t lightEvent;
  tslSensor.getEvent(&lightEvent);

  if (lightEvent.light) {
    json["brightness"] = lightEvent.light;
  }

  return json;
  */
  
  
  JsonObject& json = buffer.createObject();
  return json;
  
}

JsonArray& BrightnessSensor::getTypeAsJson(DynamicJsonBuffer& buffer)
{
	JsonArray& typeArray = buffer.parseArray(SENSORTYPE);
	
    return typeArray;
}


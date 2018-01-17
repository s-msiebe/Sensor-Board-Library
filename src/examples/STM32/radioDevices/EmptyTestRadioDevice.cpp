#include "EmptyTestRadioDevice.h"

#include <stdio.h>
#include <stdlib.h>

EmptyTestRadioDevice::EmptyTestRadioDevice()
{
	radioConfig = new char[500];
}

bool EmptyTestRadioDevice::begin()
{
	//Serial.println("EmptyTestRadioDevice.begin");
	
	String tmpRadioConfig;
	
	DynamicJsonBuffer buffer;
	JsonObject& json = buffer.createObject();
	json["@type"] = "EmptyTestRadioDevice";
	
	json.printTo(tmpRadioConfig);
	
	strcpy(radioConfig, tmpRadioConfig.c_str());
	
	return true;
}

bool EmptyTestRadioDevice::loop()
{
	//Serial.println("EmptyTestRadioDevice.loop");
	return true;
}

bool EmptyTestRadioDevice::startRadioDevice()
{
	//Serial.println("EmptyTestRadioDevice.startRadioDevice");
	return true;
}

bool EmptyTestRadioDevice::stopRadioDevice()
{
	//Serial.println("EmptyTestRadioDevice.stopRadioDevice");
	return true;
}

int EmptyTestRadioDevice::getMaxMessageLength()
{
	//Serial.println("EmptyTestRadioDevice.getMaxMessageLength");
	return -1;
}

JsonVariant EmptyTestRadioDevice::getTypeAsJson(DynamicJsonBuffer& buffer)
{
	String tmpRadioConfig;
	
	String rConfig(radioConfig);
	
	JsonObject& json = buffer.parseObject(rConfig);

	return json;
}

JsonObject& EmptyTestRadioDevice::getConfigAsJson(DynamicJsonBuffer& buffer)
{
	String tmpRadioConfig;
	
	String rConfig(radioConfig);
	
	JsonObject& json = buffer.parseObject(rConfig);

	return json;
}

void EmptyTestRadioDevice::setServerConfig(JsonObject& jsonConfig)
{
	//Serial.println("EmptyTestRadioDevice.setServerConfig");
	
	String tmpRadioConfig;
	
	jsonConfig.printTo(tmpRadioConfig);
	
	int radioConfigSize = strlen(tmpRadioConfig.c_str()) + 1;
	
	strcpy(radioConfig , tmpRadioConfig.c_str());
	
	radioConfig[radioConfigSize] = '\0';
	
	return;
}

bool EmptyTestRadioDevice::sendMessage(String &buffer)
{
	//Serial.println("EmptyTestRadioDevice.sendMessage");
	return true;
}

bool EmptyTestRadioDevice::connect()
{
	//Serial.println("EmptyTestRadioDevice.connect");
	return true;
}
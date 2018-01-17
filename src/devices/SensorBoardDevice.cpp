#include "SensorBoardDevice.h"

SensorBoardDevice::SensorBoardDevice()
{
	
}

SensorBoardDevice::~SensorBoardDevice()
{
	
}

bool SensorBoardDevice::begin()
{
	//Initialization of all devices
		bool error = false;
		
		if(status)
			error = !status->begin() || error;
		else
			error = true;
		
		if(setupButton)
			error = !setupButton->begin() || error;
		else
			error = true;
		
		if(radioModul)
			error = !radioModul->begin() || error;
		else
			error = true;
		
		if(sensor)
			error = !sensor->begin() || error;
		else
			error = true;
		
	//Read in data from EEPROM (Bridge-configuration and uuid)
		String uuid = storage->readFromStorage("@id");
		setUuid(uuid.c_str());
		String radioConf = storage->readFromStorage("radio");
		DynamicJsonBuffer dynamicJsonBuffer;
		JsonObject& radioJson = dynamicJsonBuffer.parseObject(radioConf);
		radioModul->setServerConfig(radioJson);
	
	//Establish connection
		if(radioModul)
		{
			bool connectionStarted = radioModul->startRadioDevice();
			if(connectionStarted)
			{
				error = !radioModul->connect() || error;
			}
			else
			{
				error = true;
			}
		}
		else
			error = true;
	
	//Predefining variables
		setupMode = false;
		
		if(error)
			status->setStatus(Status::ERROR);
		else
			status->setStatus(Status::OK);
	
	return !error;
}

bool SensorBoardDevice::loop()
{
	bool error = false;
	
	//Status has to be running first
	if(status)
		error = !status->loop() || error;
	else
		error = true;
	
	if(setupButton)
		error = !setupButton->loop() || error;
	else
		error = true;
	
	if(radioModul)
			error = !radioModul->loop() || error;
		else
			error = true;
	
	if(sensor)
		error = !sensor->begin() || error;
	else
		error = true;
	
	
	//Check if the button for SetupMode has been pressed
		if(setupButton->isPressed())
		{
			int currentTime = millis();
			
			if(startPressTime == -1)
			{
				startPressTime = currentTime;
			}
			
			currentPressTime = (currentTime - startPressTime);
		}
		else
		{
			if( currentPressTime >= setupModePressTime*1000 && currentPressTime <= resetPressTime*1000 )
			{
				if(setupMode)
					error = !endSetupMode() || error;
				else
					error = !startSetupMode() || error;
				
			}
			else if( currentPressTime >= resetPressTime*1000 )
			{
				//Start of Reset-mode, which will delete all settings (uuid from EEPROM and RDF-Config from EEPROM)
				error = !runResetMode() || error;
			}
				
			//Reset the starting time
				startPressTime = -1;
				currentPressTime = 0;
			
		}
		
	// Run through loop, if in Setup-mode
		if(setupMode)
		{
			error = !runSetupMode() || error;
		}
		
	//Get messages from sensor
		DynamicJsonBuffer buffer;
		JsonObject& sensorValue = sensor->getValueToSendAsJson(buffer);
		String sensorValueAsString;
		sensorValue.printTo(sensorValueAsString);
		
		if(sensorValueAsString)
		{
			sendMessage(sensorValueAsString);
		}
		
	
	if(error)
		status->setStatus(Status::ERROR);
	status->loop();
	
	return error;
}

bool SensorBoardDevice::sendMessage(String &buffer)
{
	return radioModul->sendMessage(buffer);
}
		
bool SensorBoardDevice::runSetupMode()
{
	bool error = false;
	
	if(connection->handle())
	{
		HttpRequest& req = connection->request;
		HttpResponse& res = connection->response;
		
		res.headers = 0;
		
	
		if (req.method == "GET" && req.target == "/") 
		{
			//Create JSON-LD Response
				DynamicJsonBuffer  bufferGET;
				JsonObject& jsonGET = bufferGET.createObject();
				
				jsonGET.set("@context", getContextAsJson(bufferGET));
				jsonGET.set("@id", getUuid());
				jsonGET["@type"] = sensor->getTypeAsJson(bufferGET);
				jsonGET.set("radio", radioModul->getTypeAsJson(bufferGET));
				
				res.setHeader("content-type", "application/json");
				res.setHeader("content-length", String(jsonGET.measureLength()));
				res.setHeader("Access-Control-Allow-Origin", "*");
				
			//send Headers
				res.sendHeaders();
				
			//send JSON-LD Response	
				jsonGET.printTo(res.connection);
		}
		else if (req.method == "PUT" && req.target == "/")
		{
			DynamicJsonBuffer bufferPUT;
			JsonObject& jsonPUT = bufferPUT.parseObject(req.connection);
			
			String stringId = jsonPUT["@id"];
			
			//save UUID
				setUuid(stringId.c_str());
								
			//save UUID in EEPROM
				String key = "@id";
				
				error = !( storage->writeInStorage(key, stringId) );
		
			//Response with status code 204
				if(!error)
				{
					res.statusCode = 204;
					
					//create JSON-LD Response
						DynamicJsonBuffer  bufferPUTResponse;
						JsonObject& jsonPUTResponse = bufferPUTResponse.createObject();
						
						jsonPUTResponse.set ("@id", getUuid());
						
						res.setHeader("content-type", "application/json");
						res.setHeader("content-length", String(jsonPUTResponse.measureLength()));
						res.setHeader("Access-Control-Allow-Origin", "*");
						
						
					//send Headers
						res.sendHeaders();
						
					//send JSON-LD Response	
						jsonPUTResponse.printTo(res.connection);
				}
				else
				{
					res.statusCode = 500;
					
					DynamicJsonBuffer  bufferPUTResponseError;
					JsonObject& jsonError = bufferPUTResponseError.createObject();
					jsonError["error-message"] = "Could not save uuid";
					
					res.setHeader("content-type", "application/json");
					res.setHeader("content-length", String(jsonError.measureLength()));
					res.setHeader("Access-Control-Allow-Origin", "*");
					
					//send Headers
						res.sendHeaders();
				
					//send JSON-LD Response	
						jsonError.printTo(res.connection);
				}
		}
		else if (req.method == "POST" && req.target == "/")
		{
			DynamicJsonBuffer buffer;
			JsonObject& json = buffer.parseObject(req.connection);
			
			//save Radio-Config
				radioModul->setServerConfig(json["radio"]);
				
			//save Radio-Config in EEPROM
				String key = "radio";
				String value = json["radio"].as<String>();
				error = !( storage->writeInStorage(key, value) );
			
			//Response with status code 204 and changed value as content
				if(!error)
				{
					res.statusCode = 204;
					
					//create JSON-LD Response
						DynamicJsonBuffer bufferPOSTResponse;
						JsonObject& jsonPOSTResponse = bufferPOSTResponse.createObject();
						
						jsonPOSTResponse.set("radio", radioModul->getConfigAsJson(bufferPOSTResponse));
						
						res.setHeader("content-type", "application/json");
						res.setHeader("content-length", String(jsonPOSTResponse.measureLength()));
						res.setHeader("Access-Control-Allow-Origin", "*");
						
						
					//send Headers
						res.sendHeaders();
						
					//send JSON-LD Response	
						jsonPOSTResponse.printTo(res.connection);
				}
				else
				{
					res.statusCode = 500;
					
					DynamicJsonBuffer  bufferPOSTResponseError;
					JsonObject& jsonError = bufferPOSTResponseError.createObject();
					jsonError["error-message"] = "Could not save config";
					
					res.setHeader("content-type", "application/json");
					res.setHeader("content-length", String(jsonError.measureLength()));
					res.setHeader("Access-Control-Allow-Origin", "*");
					
					//send Headers
						res.sendHeaders();
				
					//send JSON-LD Response	
						jsonError.printTo(res.connection);
				}
		}
		else if (req.method == "OPTIONS" && req.target == "/")
		{
			res.setHeader("Access-Control-Allow-Headers", "Content-Type,Accept");
			res.setHeader("Access-Control-Allow-Methods:", "POST,GET,PUT,OPTIONS");
			res.setHeader("Access-Control-Allow-Origin", "*");
			
			res.statusCode = 200;
			res.sendHeaders();
		}
		else
		{
			res.statusCode = 404;
			res.sendHeaders();
		}
		
		//send Response
			connection->flush();
			connection->releaseRequest();
			
	}
	
	
	return !error;
}

bool SensorBoardDevice::runResetMode()
{
	String key = "@id";
	return storage->removeFromStorage(key);
}

bool SensorBoardDevice::startSetupMode()
{
	setupMode = true;
	status->setStatus(Status::SETUP_MODE);
	
	//open Serial-Port
		connection = new HttpConnection(connectionStream, 1024);
	
	return true;
}

bool SensorBoardDevice::endSetupMode()
{
	setupMode = false;
	status->setStatus(Status::OK);
	
	//close Serial-Port
		delete connection;
	
	return true;
}

StatusDevice & SensorBoardDevice::getStatus()
{
	return *status;
}
void SensorBoardDevice::setStatus(StatusDevice &status)
{
	this->status = &status;
}

SetupButtonDevice & SensorBoardDevice::getSetupButton()
{
	return *setupButton;
}
void SensorBoardDevice::setSetupButton(SetupButtonDevice &setupButton)
{
	this->setupButton = &setupButton;
}

RadioDevice & SensorBoardDevice::getRadioModul()
{
	return *radioModul;
}
void SensorBoardDevice::setRadioModul( RadioDevice &radioModul)
{
	this->radioModul = &radioModul;
}
		
SensorDevice & SensorBoardDevice::getSensor()
{
	return *sensor;
}
void SensorBoardDevice::setSensor(SensorDevice &sensor)
{
	this->sensor = &sensor;
}

StorageDevice &SensorBoardDevice::getStorageDevice()
{
	return *storage;
}
void SensorBoardDevice::setStorageDevice(StorageDevice &storage)
{
	this->storage = &storage;
}
		
Stream & SensorBoardDevice::getConnectionStream()
{
	return *connectionStream;
}
void SensorBoardDevice::setConnectionStream(Stream *connectionStream)
{
	this->connectionStream = connectionStream;
}

int SensorBoardDevice::getSetupModePressTime()
{
	return setupModePressTime;
}
void SensorBoardDevice::setSetupModePressTime(int pressTime)
{
	setupModePressTime = pressTime;
}

int SensorBoardDevice::getResetPressTime()
{
	return resetPressTime;
}
void SensorBoardDevice::setResetPressTime(int pressTime)
{
	resetPressTime = pressTime;
}

char *SensorBoardDevice::getUuid()
{
	return uuid;
}
void SensorBoardDevice::setUuid(const char *uuid)
{
	this->uuid = new char[strlen(uuid) + 1];
    strcpy(this->uuid , uuid);
}

bool SensorBoardDevice::isInSetupMode()
{
	return setupMode;
}

JsonObject& SensorBoardDevice::getContextAsJson(JsonBuffer& buffer)
{
	JsonObject& json = buffer.createObject();
	
	json["@vocab"] = "https://ns.bergnet.org/dark-horse/";
	
    return json;
}



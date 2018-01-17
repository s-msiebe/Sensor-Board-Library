#include <SingleLedStatusDevice.h>

SingleLedStatusDevice statusLed(PC13);


void setup() {
  statusLed.begin();
  
  statusLed.setStatus(Status::OK);
}

void loop() {
  statusLed.loop();
}

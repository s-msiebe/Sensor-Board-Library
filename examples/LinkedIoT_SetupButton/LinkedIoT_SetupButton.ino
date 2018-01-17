#include <PullUpSetupButtonDevice.h>

PullUpSetupButtonDevice setupButton(PA0);


void setup() {
  setupButton.begin();
  pinMode(PC13, OUTPUT);
}

void loop() {
  digitalWrite(PC13, HIGH);
  
  if(setupButton.isPressed())
  {
    digitalWrite(PC13, LOW);
  }
}

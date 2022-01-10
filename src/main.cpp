
#include <Arduino.h>
#include "./Time/TimeHandler.h"
#include "./SPI/TMC/CurtainHandler.h"

TimeHandler timeHandler;
CurtainHandler curtainHandler;

void setup() {
  Serial.begin(9600);
  delay(3000);
  Serial.println("starting");
  timeHandler.initializeTime();
  Serial.println(timeHandler.printTime());
}

void loop() {
  // Every hour, update the time from NTP server
if ((unsigned long)(millis() - timeHandler._lastUpdate) > 3600000) {
  timeHandler.updateTime();
}

// Open curtains if time to
if ((timeHandler.getHours() * 100 + timeHandler.getMinutes()) == 900) {
  curtainHandler.openCurtains();
}

delay(25000);
}

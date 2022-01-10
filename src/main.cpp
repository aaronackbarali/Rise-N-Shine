#include <Arduino.h>
#include "./Time/TimeHandler.h"

TimeHandler timeHandler;

void setup() {
  Serial.begin(9600);
  delay(3000);
  Serial.println("starting");
  timeHandler.initializeTime();
  Serial.println(timeHandler.printTime());
}

void loop() {
  delay(1000);
}

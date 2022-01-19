
#include <Arduino.h>
#include "./Time/TimeHandler.h"
#include "./SPI/SPI_Handler.h"

TimeHandler timeHandler;
SPI_Handler spi_Handler;

void setup() {
  Serial.begin(9600);
  delay(10000);

  //spi_Handler.openCurtains();
  spi_Handler.printTime();

  // Serial.println("starting");
  // timeHandler.initializeTime();
  // Serial.println(timeHandler.printTime());
}

void loop() {
  // // Every hour, update the time from NTP server
  // if ((unsigned long)(millis() - timeHandler._lastUpdate) > 3600000) {
  //   timeHandler.updateTime();
  // }
  //
  // // Open curtains if time to
  // if ((timeHandler.getHours() * 100 + timeHandler.getMinutes()) == 900) {
  //   curtainHandler.openCurtains();
  // }

  delay(25000);
}

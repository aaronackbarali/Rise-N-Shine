
#include <Arduino.h>
#include "./SPI/SPI_Handler.h"

SPI_Handler spi_Handler;

void setup() {
  delay(10000);

  spi_Handler.initializeTime();
  spi_Handler.initializeDisplay();
  spi_Handler.printTime(true);
}

int fullRefreshTrigger = 0;

void loop() {
  delay(60000);
  fullRefreshTrigger++;

  if(fullRefreshTrigger == 5){
    spi_Handler.printTime(true);
    fullRefreshTrigger = 0;
  } else {
    spi_Handler.printTime(false);
  }
}

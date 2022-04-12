
#include <Arduino.h>
#include "./SPI/SPI_Handler.h"

SPI_Handler spi_Handler;

int fullRefreshTrigger = 0;
int vNow = 0;
int delta = 2;   // alarm window = vNow +/- delta
int alarm = 855; // alarm time 24h format HHMM

void setup() {
  delay(10000);

  spi_Handler.initializeTime();
  spi_Handler.initializeDisplay();
  spi_Handler.printTime(true);
}

void loop() {
  // Print time to display, full refresh every 5th print
  delay(60000);
  fullRefreshTrigger++;

  if(fullRefreshTrigger == 5){
    spi_Handler.printTime(true);
    fullRefreshTrigger = 0;
  } else {
    spi_Handler.printTime(false);
  }

  // If you're within a 2 minute window of the alarm, start opening
  vNow = spi_Handler.getTime();

  if (alarm - delta <= vNow && vNow <= alarm + delta ) {
    spi_Handler.openCurtains();
    fullRefreshTrigger = 5;
  }
}

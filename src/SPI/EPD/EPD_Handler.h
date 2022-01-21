
#ifndef EPDHNDLER_H
#define EPDHNDLER_H

#include <Arduino.h>
#include "./SPI/pinDef.h"
#include "EPD_SPI.h"
#include "Paint.h"
#include "./Time/TimeHandler.h"

// Class: abstracts e-paper display commands away from the SPI Handler
class EPD_Handler{
public:
  //  Constructor:
  EPD_Handler(SPIClass& spi = SPI);

  // Method:
  void initializeDisplay();

  // Method: Clears display
  void clearDisplay();

  // Method:
  void initializeTime();

  // Method: Prints current time HH:MM
  void printTime(bool full);

private:
	EPD_SPI _epd;
  Paint _paint;
  TimeHandler _timeHandler;
};

#endif

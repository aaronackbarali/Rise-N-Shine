
#ifndef EPDHNDLER_H
#define EPDHNDLER_H

#include <Arduino.h>
#include "./SPI/pinDef.h"
#include "EPD_SPI.h"
#include "Paint.h"
#include "./Time/TimeHandler.h"

// Class: Abstracts e-paper display commands away from the SPI Handler
class EPD_Handler{
public:
  //  Constructor:
  EPD_Handler(SPIClass& spi = SPI);

  // Method: Initializes and clears display
  void initializeDisplay();

  // Method: Initilizes time
  void initializeTime();

  // Method: Prints current time HH:MM
  int getTime();

  // Method: Prints current time HH:MM
  void printTime(bool full);

  // Method: Prints a string, font 24pt
  void print24(String str);

private:
	EPD_SPI _epd;
  Paint _paint;
  TimeHandler _timeHandler;
};

#endif

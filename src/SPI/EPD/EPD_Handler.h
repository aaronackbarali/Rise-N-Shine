
#ifndef EPDHNDLER_H
#define EPDHNDLER_H

#include <Arduino.h>
#include "./SPI/pinDef.h"
#include "EPD_SPI.h"
#include "Paint.h"

// Class: abstracts e-paper display commands away from the SPI Handler
class EPD_Handler{
public:
  //  Constructor:
  EPD_Handler(SPIClass& spi = SPI);

  // Method: Clears display
  void clearDisplay();

  // Method: Prints current time HH:MM
  void printTime();

private:
	EPD_SPI _epd;
  Paint _paint;
};

#endif

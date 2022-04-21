
#ifndef EPDHNDLER_H
#define EPDHNDLER_H

#include <Arduino.h>
#include "./SPI/pinDef.h"
#include "EPD.h"
#include "Paint.h"

// Class: Abstracts e-paper display commands away from the SPI Handler
class EPD_Handler{
public:
  //  Constructor:
  EPD_Handler(SPIClass& spi = SPI);

  // Method: Initializes and clears display
  void initializeDisplay();

  // Method: Prints a string, font 64pt
  void print64(String str, bool full);

  // Method: Prints a string, font 24pt
  void print24(String str);

private:
	EPD _epd;
  Paint _paint;
};

#endif


#ifndef EPDHNDLER_H
#define EPDHNDLER_H

#include "EPD.h"

// Class: Abstracts e-paper display commands away from the SPI Handler
class EPD_Handler{
  public:
  	EPD epd;

    // Constructor:
    EPD_Handler(SPIClass &spi);

    // Method: Initializes and clears display
    void initializeDisplay();

    // Method: Prints a string, font 64pt
    void print64(String str, bool full);
};

#endif

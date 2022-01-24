
#ifndef SPIHANDLER_H
#define SPIHANDLER_H

#include <SPI.h>
#include "./TMC/CurtainHandler.h"
#include "./EPD/EPD_Handler.h"

// Class: Handles all SPI peripherals
class SPI_Handler {
  public:
    static SPIClassSAMD mySPI;
    static CurtainHandler curtainHandler;
    static EPD_Handler epdHandler;

    // Constructor: Initializes SPI pins and settings
    SPI_Handler();

    // Method: Handles curtain opening
    static void openCurtains();

    // Method:
    static void initializeDisplay();

    // Method:
    static void initializeTime();

    // Method:
    static void printTime(bool full);
};

#endif


#ifndef SPIHANDLER_H
#define SPIHANDLER_H

#include <SPI.h>
#include "./SPI/TMC/CurtainHandler.h"

// Class: Handles all SPI peripherals
class SPI_Handler {
  public:
    static SPIClassSAMD mySPI;
    static CurtainHandler curtainHandler;

    // Constructor: Initializes SPI pins and settings
    SPI_Handler();

    // Method: Handles curtain opening
    static void openCurtains();
};

#endif

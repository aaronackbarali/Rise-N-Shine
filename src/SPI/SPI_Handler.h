
#ifndef SPIHANDLER_H
#define SPIHANDLER_H

#include <SPI.h>
#include "./SPI/TMC/CurtainHandler.h"

class SPI_Handler {
  public:
    static SPIClassSAMD mySPI;
    static CurtainHandler curtainHandler;

    SPI_Handler();
    static void openCurtains();
};

#endif

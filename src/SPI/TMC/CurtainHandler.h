
#ifndef CURTAINAHNDLER_H
#define CURTAINAHNDLER_H

#include "TMC5160.h"

// Class: abstracts curtain checks and motor control away from the SPI Handler
class CurtainHandler{
  public:
  	TMC5160 motor;

    //  Constructor:
    CurtainHandler(SPIClass &spi);

    // Method: Opens curtains
    void openCurtains();
};

#endif

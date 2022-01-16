
#ifndef CURTAINAHNDLER_H
#define CURTAINAHNDLER_H

#include <Arduino.h>
#include "./SPI/pinDef.h"
#include "TMC5160_SPI.h"

// Class: abstracts curtain checks and motor control away from the SPI Handler
class CurtainHandler{
public:
  // Time (HHMM) to start pulling open curtains.
  // Cannot be near syncTime. Default: 9am
  int curtainStartTime  = 900;

  //  Constructor:
  CurtainHandler(SPIClass& spi = SPI);

  // Method: Opens curtains
  void openCurtains();

private:
	TMC5160_SPI _motor;
};

#endif

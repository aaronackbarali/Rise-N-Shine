
#ifndef CURTAINAHNDLER_H
#define CURTAINAHNDLER_H

#include "TMC5160_SPI.h"

class CurtainHandler{
public:
  int curtainStartTime  = 900;  // Time (HHMM) to start pulling open curtains, cannot be near syncTime. Default: 9am

  CurtainHandler(SPIClass& spi = SPI);

  void openCurtains();

private:
	TMC5160_SPI _motor;
};

#endif

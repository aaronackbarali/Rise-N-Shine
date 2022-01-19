
#include "EPD_Handler.h"

#define COLORED     1
#define UNCOLORED   0

// Constructor: calls motor constructor
EPD_Handler::EPD_Handler(SPIClass &spi) :
  _epd(
    EPD_CS_PIN,
    EPD_DC_PIN,
    EPD_RST_PIN,
    EPD_BUSY_PIN,
    spi
  ),
  _paint(){
}

void EPD_Handler::printTime(){
  _epd.Init();

  _epd.ClearFrameMemory(0xFF);
  _epd.DisplayFrame();

  delay(2000);

  _paint.SetRotate(ROTATE_90);
  _paint.SetWidth(64); // height since rotated 90
  _paint.SetHeight(96); // width since rotated 90

  _paint.Clear(UNCOLORED);
  _paint.DrawStringAt(0, 0, "12", &fontLS_64, COLORED);

  _epd.SetFrameMemory(_paint.GetImage(), 0, 0, _paint.GetWidth(), _paint.GetHeight());
  _epd.DisplayFrame();
}

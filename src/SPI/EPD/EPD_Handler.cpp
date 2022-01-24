
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
  ), _paint(), _timeHandler(){
}

void EPD_Handler::initializeDisplay(){
  _epd.Init();
  _epd.ClearFrameMemory(0xFF);
  _epd.DisplayFrame();
}

void EPD_Handler::initializeTime(){
  _timeHandler.initializeTime();
}

void EPD_Handler::printTime(bool full){
  _epd.Init();

  String vTime = _timeHandler.printTime();

  _paint.SetRotate(ROTATE_90);
  _paint.SetWidth(64); // height since rotated 90
  _paint.SetHeight(240); // width since rotated 90

  _paint.Clear(UNCOLORED);
  _paint.DrawStringAt(0, 0, vTime, &fontLS_64, COLORED);

  if(full){
    _epd.SetFrameMemory(_paint.GetImage(), 0, 0, _paint.GetWidth(), _paint.GetHeight());
    _epd.DisplayFrame();
  } else {
    _epd.SetFrameMemory_Partial(_paint.GetImage(), 0, 0, _paint.GetWidth(), _paint.GetHeight());
    _epd.DisplayFrame_Partial();
  }

  _epd.SetFrameMemory_Base(_paint.GetImage(), 0, 0, _paint.GetWidth(), _paint.GetHeight());
  _epd.Sleep();
}

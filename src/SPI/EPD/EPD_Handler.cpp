
#include "EPD_Handler.h"

#define COLORED     1
#define UNCOLORED   0

// Constructor:
EPD_Handler::EPD_Handler(SPIClass &spi) : _epd(spi), _paint() {
}

void EPD_Handler::initializeDisplay(){
  _epd.Init();
  _epd.ClearFrameMemory(0xFF);
  _epd.DisplayFrame();
}

void EPD_Handler::print64(String str, bool full){
  _epd.Init();

  _paint.SetRotate(ROTATE_90);
  _paint.SetWidth(64); // height since rotated 90
  _paint.SetHeight(240); // width since rotated 90

  _paint.Clear(UNCOLORED);
  _paint.DrawStringAt(0, 0, str, &fontLS_64, COLORED);

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

void EPD_Handler::print24(String str){
  _epd.Init();

  _paint.SetRotate(ROTATE_90);
  _paint.SetWidth(24); // height since rotated 90
  _paint.SetHeight(296); // width since rotated 90

  _paint.Clear(UNCOLORED);
  _paint.DrawStringAt(0, 0, str, &fontLS_24, COLORED);

  _epd.SetFrameMemory(_paint.GetImage(), 0, 0, _paint.GetWidth(), _paint.GetHeight());
  _epd.DisplayFrame();

  _epd.SetFrameMemory_Base(_paint.GetImage(), 0, 0, _paint.GetWidth(), _paint.GetHeight());
  _epd.Sleep();
}

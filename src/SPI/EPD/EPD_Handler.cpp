
#include "EPD_Handler.h"
#include "Paint.h"

#define COLORED     1
#define UNCOLORED   0

Paint paint;

// Constructor:
EPD_Handler::EPD_Handler(SPIClass &spi) : epd(spi) {
}

void EPD_Handler::initializeDisplay(){
  epd.Init();
  epd.ClearFrameMemory(0xFF);
  epd.DisplayFrame();
}

void EPD_Handler::print64(String str, bool full){
  epd.Init();

  paint.SetRotate(ROTATE_90);
  paint.SetWidth(64); // height since rotated 90
  paint.SetHeight(240); // width since rotated 90

  paint.Clear(UNCOLORED);
  paint.DrawStringAt(0, 0, str, &fontLS_64, COLORED);

  if (full) {
    epd.SetFrameMemory(paint.GetImage(), 0, 0, paint.GetWidth(), paint.GetHeight());
    epd.DisplayFrame();
  } else {
    epd.SetFrameMemory_Partial(paint.GetImage(), 0, 0, paint.GetWidth(), paint.GetHeight());
    epd.DisplayFrame_Partial();
  }

  epd.SetFrameMemory_Base(paint.GetImage(), 0, 0, paint.GetWidth(), paint.GetHeight());
  epd.Sleep();
}

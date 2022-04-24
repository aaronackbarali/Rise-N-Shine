
#include "EPD_Handler.h"
#include "Paint.h"

#define COLORED     1
#define UNCOLORED   0

Paint paint;
int printCount = 0;

// Constructor:
EPD_Handler::EPD_Handler(SPIClass &spi) : epd(spi) {
}

// Method: Initializes and clears display
void EPD_Handler::initializeDisplay(){
  epd.Init();
  epd.ClearFrameMemory(0xFF);
  epd.DisplayFrame();
}

// Method: Prints a string, font 64pt. Refreshes every 5th print
void EPD_Handler::print64(String str){
  printCount++;

  epd.Init();

  paint.SetRotate(ROTATE_90);
  paint.SetWidth(64); // height since rotated 90
  paint.SetHeight(240); // width since rotated 90

  paint.Clear(UNCOLORED);
  paint.DrawStringAt(0, 0, str, &fontLS_64, COLORED);

  if (printCount == 5) {
    epd.SetFrameMemory(paint.GetImage(), 0, 0, paint.GetWidth(), paint.GetHeight());
    epd.DisplayFrame();
    printCount = 0;
  } else {
    epd.SetFrameMemory_Partial(paint.GetImage(), 0, 0, paint.GetWidth(), paint.GetHeight());
    epd.DisplayFrame_Partial();
  }

  epd.SetFrameMemory_Base(paint.GetImage(), 0, 0, paint.GetWidth(), paint.GetHeight());
  epd.Sleep();
}

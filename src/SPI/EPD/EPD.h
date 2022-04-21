
#ifndef EPD2IN9_V2_H
#define EPD2IN9_V2_H

#include <SPI.h>

// Display resolution
#define EPD_WIDTH       128
#define EPD_HEIGHT      296

class EPD {
  public:
    unsigned char buffer[4736];
    unsigned long width;
    unsigned long height;

    EPD(SPIClass& spi = SPI);
    void Init();
    void SendCommand(unsigned char command);
    void SendData(unsigned char data);
    void WaitUntilIdle();
    void Reset();
    void SetFrameMemory(
      const unsigned char* image_buffer,
      unsigned int x,
      unsigned int y,
      unsigned int image_width,
      unsigned int image_height
    );
    void SetFrameMemory_Partial(
      const unsigned char* image_buffer,
      unsigned int x,
      unsigned int y,
      unsigned int image_width,
      unsigned int image_height
    );
    void SetFrameMemory_Base(
      const unsigned char* image_buffer,
      unsigned int x,
      unsigned int y,
      unsigned int image_width,
      unsigned int image_height
    );
    void SetFrameMemory(const unsigned char* image_buffer);
    void SetFrameMemory_Base(const unsigned char* image_buffer);
    void ClearFrameMemory(unsigned char color);
    void DisplayFrame();
    void DisplayFrame_Partial();
    void Sleep();

  private:
    SPIClass *_spi;

    void SetLut(unsigned char *lut);
    void SetLut_by_host(unsigned char *lut);
    void SetMemoryArea(int x_start, int y_start, int x_end, int y_end);
    void SetMemoryPointer(int x, int y);
};

#endif

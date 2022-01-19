
#ifndef EPD2IN9_V2_H
#define EPD2IN9_V2_H

#include <Arduino.h>
#include <SPI.h>

// Display resolution
#define EPD_WIDTH       128
#define EPD_HEIGHT      296

class EPD {
  public:
    unsigned long width;
    unsigned long height;

    EPD();
    void Init();
    virtual void SendCommand(unsigned char command) = 0;
    virtual void SendData(unsigned char data) = 0;
    virtual void WaitUntilIdle() = 0;
    virtual void Reset() = 0;
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
    void SetFrameMemory(const unsigned char* image_buffer);
    void SetFrameMemory_Base(const unsigned char* image_buffer);
    void ClearFrameMemory(unsigned char color);
    void DisplayFrame();
    void DisplayFrame_Partial();
    void Sleep();

  private:
    unsigned int reset_pin;
    unsigned int dc_pin;
    unsigned int cs_pin;
    unsigned int busy_pin;

    void SetLut(unsigned char *lut);
    void SetLut_by_host(unsigned char *lut);
    void SetMemoryArea(int x_start, int y_start, int x_end, int y_end);
    void SetMemoryPointer(int x, int y);
};

#endif

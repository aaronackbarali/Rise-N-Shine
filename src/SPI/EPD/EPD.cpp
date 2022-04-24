
#include <stdlib.h>
#include "EPD.h"
#include "imageData.h"
#include "./SPI/pinDef.h"

unsigned char buffer[4736];
unsigned long width;
unsigned long height;

EPD::EPD(SPIClass &spi) : spi(&spi) {
  width = EPD_WIDTH;
  height = EPD_HEIGHT;
};

// Method: Send a command to the EPD
void EPD::SendCommand(unsigned char command) {
  digitalWrite(EPD_DC_PIN, LOW);
  digitalWrite(EPD_CS_PIN, LOW);
  spi->transfer(command);
  digitalWrite(EPD_CS_PIN, HIGH);
}

// Method: Send a byte of data to the EPD
void EPD::SendData(unsigned char dat) {
  digitalWrite(EPD_DC_PIN, HIGH);
  digitalWrite(EPD_CS_PIN, LOW);
  spi->transfer(dat);
  digitalWrite(EPD_CS_PIN, HIGH);
}

// Method: Wait until the busy_pin goes LOW
void EPD::WaitUntilIdle() {
  while (1) {	 //=1 BUSY
    if (digitalRead(EPD_BUSY_PIN) == LOW)
      break;
    delay(5);
  }
  delay(5);
}

// Method: Module reset. Used to awaken the module in deep sleep. See Epd::Sleep();
void EPD::Reset() {
  digitalWrite(EPD_RST_PIN, HIGH);
  delay(20);
  digitalWrite(EPD_RST_PIN, LOW);
  delay(5);
  digitalWrite(EPD_RST_PIN, HIGH);
  delay(20);
}

// Method: Wakes and initializes display
void EPD::Init() {
  Reset();

  WaitUntilIdle();
  SendCommand(0x12);  // Software reset
  WaitUntilIdle();

  SendCommand(0x01); // Driver output control
  SendData(0x27);
  SendData(0x01);
  SendData(0x00);

  SendCommand(0x11); // Data entry mode
  SendData(0x03);
  SetMemoryArea(0, 0, width - 1, height - 1);

  SendCommand(0x21); // Display update control
  SendData(0x00);
  SendData(0x80);

  SetMemoryPointer(0, 0);
  WaitUntilIdle();

  SetLut_by_host(WS_20_30);
}

// Method: Enter deep sleep. Use Init() to wake
void EPD::Sleep() {
  SendCommand(0x10);
  SendData(0x01);
}

// Method: sets frame memory on epd ram
void EPD::SetFrameMemory(
  const unsigned char* image_buffer,
  unsigned int x,
  unsigned int y,
  unsigned int image_width,
  unsigned int image_height
) {
  int x_end, y_end;

  if (
    image_buffer == NULL ||
    x < 0 || image_width < 0 ||
    y < 0 || image_height < 0
  ) {
    return;
  }
  /* x point must be the multiple of 8 or the last 3 bits will be ignored */
  x &= 0xF8;
  image_width &= 0xF8;
  if (x + image_width >= width) {
    x_end = width - 1;
  } else {
    x_end = x + image_width - 1;
  }
  if (y + image_height >= height) {
    y_end = height - 1;
  } else {
    y_end = y + image_height - 1;
  }
  SetMemoryArea(x, y, x_end, y_end);
  SetMemoryPointer(x, y);
  SendCommand(0x24);
  /* send the image data */
  for (unsigned int j = 0; j < y_end - y + 1; j++) {
    for (unsigned int i = 0; i < (x_end - x + 1) / 8; i++) {
      SendData(image_buffer[i + j * (image_width / 8)]);
    }
  }
}

void EPD::SetFrameMemory_Partial(
  const unsigned char* image_buffer,
  unsigned int x,
  unsigned int y,
  unsigned int image_width,
  unsigned int image_height
) {
  int x_end;
  int y_end;

  if (
    image_buffer == NULL ||
    x < 0 || image_width < 0 ||
    y < 0 || image_height < 0
  ) {
    return;
  }
  /* x point must be the multiple of 8 or the last 3 bits will be ignored */
  x &= 0xF8;
  image_width &= 0xF8;
  if (x + image_width >= width) {
    x_end = width - 1;
  } else {
    x_end = x + image_width - 1;
  }
  if (y + image_height >= height) {
    y_end = height - 1;
  } else {
    y_end = y + image_height - 1;
  }

  digitalWrite(EPD_RST_PIN, LOW);
  delay(2);
  digitalWrite(EPD_RST_PIN, HIGH);
  delay(2);

  SetLut(_WF_PARTIAL_2IN9);
  SendCommand(0x37);
  SendData(0x00);
  SendData(0x00);
  SendData(0x00);
  SendData(0x00);
  SendData(0x00);
  SendData(0x40);
  SendData(0x00);
  SendData(0x00);
  SendData(0x00);
  SendData(0x00);

  SendCommand(0x3C); //BorderWavefrom
  SendData(0x80);

  SendCommand(0x22);
  SendData(0xC0);
  SendCommand(0x20);
  WaitUntilIdle();

  SetMemoryArea(x, y, x_end, y_end);
  SetMemoryPointer(x, y);
  SendCommand(0x24);
  /* send the image data */
  for (unsigned int j = 0; j < y_end - y + 1; j++) {
    for (unsigned int i = 0; i < (x_end - x + 1) / 8; i++) {
      SendData(image_buffer[i + j * (image_width / 8)]);
    }
  }
}

// Method: sets frame memory on epd ram and buffer
void EPD::SetFrameMemory_Base(
  const unsigned char* image_buffer,
  unsigned int x,
  unsigned int y,
  unsigned int image_width,
  unsigned int image_height
) {
  int x_end, y_end;

  if (
    image_buffer == NULL ||
    x < 0 || image_width < 0 ||
    y < 0 || image_height < 0
  ) {
    return;
  }
  /* x point must be the multiple of 8 or the last 3 bits will be ignored */
  x &= 0xF8;
  image_width &= 0xF8;
  if (x + image_width >= width) {
    x_end = width - 1;
  } else {
    x_end = x + image_width - 1;
  }
  if (y + image_height >= height) {
    y_end = height - 1;
  } else {
    y_end = y + image_height - 1;
  }
  SetMemoryArea(x, y, x_end, y_end);
  SetMemoryPointer(x, y);
  SendCommand(0x24);
  /* send the image data */
  for (unsigned int j = 0; j < y_end - y + 1; j++) {
    for (unsigned int i = 0; i < (x_end - x + 1) / 8; i++) {
      SendData(image_buffer[i + j * (image_width / 8)]);
    }
  }

  SetMemoryArea(x, y, x_end, y_end);
  SetMemoryPointer(x, y);
  SendCommand(0x26);
  /* send the image data */
  for (unsigned int j = 0; j < y_end - y + 1; j++) {
    for (unsigned int i = 0; i < (x_end - x + 1) / 8; i++) {
      SendData(image_buffer[i + j * (image_width / 8)]);
    }
  }
}

/**
    @brief: clear the frame memory with the specified color.
            this won't update the display.
*/
void EPD::ClearFrameMemory(unsigned char color) {
  SetMemoryArea(0, 0, width - 1, height - 1);
  SetMemoryPointer(0, 0);
  SendCommand(0x24);
  /* send the color data */
  for (unsigned int i = 0; i < width / 8 * height; i++) {
    SendData(color);
  }
}

/**
    @brief: update the display
            there are 2 memory areas embedded in the e-paper display
            but once this function is called,
            the the next action of SetFrameMemory or ClearFrame will
            set the other memory area.
*/
void EPD::DisplayFrame(void) {
  SendCommand(0x22);
  SendData(0xc7);
  SendCommand(0x20);
  WaitUntilIdle();
}

void EPD::DisplayFrame_Partial(void) {
  SendCommand(0x22);
  SendData(0x0F);
  SendCommand(0x20);
  WaitUntilIdle();
}

void EPD::SetLut(unsigned char *lut) {
  unsigned char count;
  SendCommand(0x32);
  for (count = 0; count < 153; count++)
    SendData(lut[count]);
  WaitUntilIdle();
}

void EPD::SetLut_by_host(unsigned char *lut) {
  SetLut((unsigned char *)lut);
  SendCommand(0x3f);
  SendData(*(lut + 153));
  SendCommand(0x03);	// gate voltage
  SendData(*(lut + 154));
  SendCommand(0x04);	// source voltage
  SendData(*(lut + 155));	// VSH
  SendData(*(lut + 156));	// VSH2
  SendData(*(lut + 157));	// VSL
  SendCommand(0x2c);		// VCOM
  SendData(*(lut + 158));
}

/**
    @brief: private function to specify the memory area for data R/W
*/
void EPD::SetMemoryArea(int x_start, int y_start, int x_end, int y_end) {
  SendCommand(0x44);
  /* x point must be the multiple of 8 or the last 3 bits will be ignored */
  SendData((x_start >> 3) & 0xFF);
  SendData((x_end >> 3) & 0xFF);
  SendCommand(0x45);
  SendData(y_start & 0xFF);
  SendData((y_start >> 8) & 0xFF);
  SendData(y_end & 0xFF);
  SendData((y_end >> 8) & 0xFF);
}

/**
    @brief: private function to specify the start point for data R/W
*/
void EPD::SetMemoryPointer(int x, int y) {
  SendCommand(0x4E);
  /* x point must be the multiple of 8 or the last 3 bits will be ignored */
  SendData((x >> 3) & 0xFF);
  SendCommand(0x4F);
  SendData(y & 0xFF);
  SendData((y >> 8) & 0xFF);
  WaitUntilIdle();
}

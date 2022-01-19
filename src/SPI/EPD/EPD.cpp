
#include <stdlib.h>
#include "EPD.h"
#include "imageData.h"

EPD::EPD() {
  width = EPD_WIDTH;
  height = EPD_HEIGHT;
};

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

/**
    @brief: put an image buffer to the frame memory.
            this won't update the display.
*/
void EPD::SetFrameMemory(
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
  if (x + image_width >= this->width) {
    x_end = this->width - 1;
  } else {
    x_end = x + image_width - 1;
  }
  if (y + image_height >= this->height) {
    y_end = this->height - 1;
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
  if (x + image_width >= this->width) {
    x_end = this->width - 1;
  } else {
    x_end = x + image_width - 1;
  }
  if (y + image_height >= this->height) {
    y_end = this->height - 1;
  } else {
    y_end = y + image_height - 1;
  }

  digitalWrite(reset_pin, LOW);
  delay(2);
  digitalWrite(reset_pin, HIGH);
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

/**
    @brief: put an image buffer to the frame memory.
            this won't update the display.

            Question: When do you use this function instead of
            void SetFrameMemory(
                const unsigned char* image_buffer,
                int x,
                int y,
                int image_width,
                int image_height
            );
            Answer: SetFrameMemory with parameters only reads image data
            from the RAM but not from the flash in AVR chips (for AVR chips,
            you have to use the function pgm_read_byte to read buffers
            from the flash).
*/
void EPD::SetFrameMemory(const unsigned char* image_buffer) {
  SetMemoryArea(0, 0, this->width - 1, this->height - 1);
  SetMemoryPointer(0, 0);
  SendCommand(0x24);
  /* send the image data */
  for (unsigned int i = 0; i < this->width / 8 * this->height; i++) {
    SendData(pgm_read_byte(&image_buffer[i]));
  }
}
void EPD::SetFrameMemory_Base(const unsigned char* image_buffer) {
  SetMemoryArea(0, 0, this->width - 1, this->height - 1);
  SetMemoryPointer(0, 0);
  SendCommand(0x24);
  /* send the image data */
  for (unsigned int i = 0; i < this->width / 8 * this->height; i++) {
    SendData(pgm_read_byte(&image_buffer[i]));
  }
  SendCommand(0x26);
  /* send the image data */
  for (unsigned int i = 0; i < this->width / 8 * this->height; i++) {
    SendData(pgm_read_byte(&image_buffer[i]));
  }
}

/**
    @brief: clear the frame memory with the specified color.
            this won't update the display.
*/
void EPD::ClearFrameMemory(unsigned char color) {
  SetMemoryArea(0, 0, this->width - 1, this->height - 1);
  SetMemoryPointer(0, 0);
  SendCommand(0x24);
  /* send the color data */
  for (unsigned int i = 0; i < this->width / 8 * this->height; i++) {
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

/**
    @brief: After this command is transmitted, the chip would enter the
            deep-sleep mode to save power.
            The deep sleep mode would return to standby by hardware reset.
            You can use EPD::Init() to awaken
*/
void EPD::Sleep() {
  SendCommand(0x10);
  SendData(0x01);
}

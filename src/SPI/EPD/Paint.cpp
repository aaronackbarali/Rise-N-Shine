
#include "Paint.h"

unsigned char* Paint::GetImage() {
  return this->image;
}

int Paint::GetWidth(void) {
  return this->width;
}

void Paint::SetWidth(int width) {
  this->width = width % 8 ? width + 8 - (width % 8) : width;
}

int Paint::GetHeight(void) {
  return this->height;
}

void Paint::SetHeight(int height) {
  this->height = height;
}

int Paint::GetRotate(void) {
  return this->rotate;
}

void Paint::SetRotate(int rotate) {
  this->rotate = rotate;
}

// Method: this draws a pixel by absolute coordinates
// this function won't be affected by the rotate parameter
void Paint::DrawAbsolutePixel(int x, int y, int colored) {
  if (x < 0 || x >= this->width || y < 0 || y >= this->height) {
    return;
  }

  if (colored) {
    image[(x + y * this->width) / 8] &= ~(0x80 >> (x % 8));
  } else {
    image[(x + y * this->width) / 8] |= 0x80 >> (x % 8);
  }
}

/**
    @brief: this draws a pixel by the coordinates
*/
void Paint::DrawPixel(int x, int y, int colored) {
  int point_temp;
  if (this->rotate == ROTATE_0) {
    if (x < 0 || x >= this->width || y < 0 || y >= this->height) {
      return;
    }
    DrawAbsolutePixel(x, y, colored);
  } else if (this->rotate == ROTATE_90) {
    if (x < 0 || x >= this->height || y < 0 || y >= this->width) {
      return;
    }
    point_temp = x;
    x = this->width - y;
    y = point_temp;
    DrawAbsolutePixel(x, y, colored);
  } else if (this->rotate == ROTATE_180) {
    if (x < 0 || x >= this->width || y < 0 || y >= this->height) {
      return;
    }
    x = this->width - x;
    y = this->height - y;
    DrawAbsolutePixel(x, y, colored);
  } else if (this->rotate == ROTATE_270) {
    if (x < 0 || x >= this->height || y < 0 || y >= this->width) {
      return;
    }
    point_temp = x;
    x = y;
    y = this->height - point_temp;
    DrawAbsolutePixel(x, y, colored);
  }
}

/**
    @brief: this draws a charactor on the frame buffer but not refresh
*/
void Paint::DrawCharAt(int x, int y, char ascii_char, sFONT* font, int colored) {
  uint16_t height = (*font).Height;
  uint16_t width  = (*font).Width;

  unsigned int char_offset = (ascii_char - ' ') * height * (width / 8 + (width % 8 ? 1 : 0));
  const unsigned char* ptr = &font->table[char_offset];

  for (int j = 0; j < height; j++) {
    for (int i = 0; i < width; i++) {
      if (pgm_read_byte(ptr) & (0x80 >> (i % 8))) {
        DrawPixel(x + i, y + j, colored);
      }

      if (i % 8 == 7) {
        ptr++;
      }
    }

    if (width % 8 != 0) {
      ptr++;
    }
  }
}

/**
   @brief: this displays a string on the frame buffer but not refresh
*/
void Paint::DrawStringAt(int x, int y, String text, sFONT* font, int colored) {
   int refcolumn = x;

  // Send the string character by character on EPD
  for (unsigned int i = 0; i < text.length();i++) {
    DrawCharAt(refcolumn, y, text.charAt(i), font, colored);
    refcolumn += font->Width;     // Decrement the column position by 16
  }
}

// Method: clear the image
void Paint::Clear(int colored) {
  for (int x = 0; x < this->width; x++) {
    for (int y = 0; y < this->height; y++) {
      DrawAbsolutePixel(x, y, colored);
    }
  }
}

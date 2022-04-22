
#ifndef __FONTS_H
#define __FONTS_H

#include <stdint.h>

struct sFONT {
  const uint8_t *table;
  uint16_t Width;
  uint16_t Height;
};

extern sFONT fontLS_24;
extern sFONT fontLS_64;

#endif

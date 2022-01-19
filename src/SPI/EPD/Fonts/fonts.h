
#ifndef __FONTS_H
#define __FONTS_H

/* Max size of bitmap will based on a font24 (17x24) */
#define MAX_HEIGHT_FONT         24
#define MAX_WIDTH_FONT          17
#define OFFSET_BITMAP           54

#include <stdint.h>

struct sFONT {
  const uint8_t *table;
  uint16_t Width;
  uint16_t Height;
};

extern sFONT fontLS_24;
extern sFONT fontLS_64;

#endif

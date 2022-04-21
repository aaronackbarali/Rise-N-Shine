
#ifndef SPIHANDLER_H
#define SPIHANDLER_H

#include <SPI.h>

// Class: Handles all SPI peripherals
class SPI_Handler {
  public:
    // Constructor: Initializes non-SPI but comms req pins
    SPI_Handler();

    // Method: Initial time sync, exits loop only when sync achieved
    static void initializeTime();

    // Method: Gets internal time (format HHMM). Will sync time if 30min since last synced
    static int getTime();

    // Method: Returns time formatted as HH:MM
    static String formatTime();

    // Method: Handles curtain opening
    static void openCurtains();

    // Method: Initializes display, soft reset
    static void initializeDisplay();

    // Method: Prints string, 64pt. Boolean for full or patrial refresh
    static void print64(String str, bool full);
};

#endif

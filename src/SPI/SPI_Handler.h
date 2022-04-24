
#ifndef SPIHANDLER_H
#define SPIHANDLER_H

#include <Arduino.h>

// Class: Handles all SPI peripherals
class SPI_Handler {
  public:
    // Constructor: Initializes pins
    SPI_Handler();

    // Method: Initial time sync, exits loop only when sync achieved
    void initializeTime();

    // Method: Gets internal time (format HHMM). Will sync time if 30min since last synced
    int getTime();

    // Method: Returns time formatted as HH:MM
    String formatTime();

    // Method: Handles curtain opening
    void openCurtains();

    // Method: Initializes display, soft reset
    void initializeDisplay();

    // Method: Prints string, 64pt. Boolean for full or patrial refresh
    void print64(String str);
};

#endif

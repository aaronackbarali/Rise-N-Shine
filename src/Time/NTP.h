
#ifndef NTP_H
#define NTP_H

#include "WiFiInterface.h"

class NTP : public WiFiInterface {
public:
  unsigned long _currentEpoc    = 0; // In s
  unsigned long _lastUpdate     = 0; // In ms

  // Method: Get NTP Epoch by looping getNTPTime()
  void updateTime(boolean startup);

  // Method: Get
  boolean getNTPTime();

  // Method:
  void sendNTPPacket();
};

#endif

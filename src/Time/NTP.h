
#ifndef NTP_H
#define NTP_H

#include "WiFiInterface.h"

class NTP : public WiFiInterface {
public:
  unsigned long _currentEpoc    = 0; // In s
  unsigned long _lastUpdate     = 0; // In ms

  // Get NTP Epoch
  void updateTime(boolean startup);

  boolean getNTPTime();

  void sendNTPPacket();
};

#endif

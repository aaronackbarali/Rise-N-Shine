
#ifndef WIFIINTERFACE_H
#define WIFIINTERFACE_H

#include <WiFiNINA.h>

class WiFiInterface {
public:
  WiFiUDP ntpUDP;

  // Attempt to connect to WiFi network. Retry every 10 seconds. 10 retries. Start udp client. Minimum delay 10s.
  int connectToWifi();

// Disconnect Wifi. Stop udp client. Hardcoded delay of 3s
  void disconnectFromWifi();

// Get WiFi status. 1 is connected, 0 otherwise.
  int getWifiStatus();
};

#endif

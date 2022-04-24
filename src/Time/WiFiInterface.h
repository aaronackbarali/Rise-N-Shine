
#ifndef WIFIINTERFACE_H
#define WIFIINTERFACE_H

#include <WiFiNINA.h>

class WiFiInterface {
public:
  WiFiUDP ntpUDP; // UDP object here for inheritance access

  // Method: Attempt to connect to WiFi network. Retry every 10 seconds. 10 retries. Start udp client. Minimum delay 10s.
  int connectToWifi();

  // Method: Disconnect Wifi. Stop udp client. Hardcoded delay of 3s
  void disconnectFromWifi();
};

#endif

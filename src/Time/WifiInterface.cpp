
#include "WiFiInterface.h"
#include "Secrets.h"

// Attempt to connect to WiFi network. Retry every 10 seconds. 10 retries. Start udp client. Minimum delay 10s.
int WiFiInterface::connectToWifi() {
  WiFi.begin(SECRET_SSID, SECRET_PASS);

  if (WiFi.status() == WL_CONNECTED) {
    ntpUDP.begin(1337); // port 1337
    return 0;
  }

  return 1; // Wifi failed to connect
}

// Disconnect Wifi. Stop udp client.
void WiFiInterface::disconnectFromWifi() {
  if (WiFi.status() == WL_CONNECTED) {
    ntpUDP.stop();
    WiFi.disconnect();
    WiFi.end();
  }
}

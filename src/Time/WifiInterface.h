
#ifndef WIFIINTERFACE_H
#define WIFIINTERFACE_H

#include <Arduino.h>
#include <WiFiNINA.h>
#include "Secrets.h"

class WiFiInterface {
public:

  WiFiUDP ntpUDP;

  // Attempt to connect to WiFi network. Retry every 10 seconds. 10 retries. Start udp client. Minimum delay 10s.
  int connectToWifi() {
    WiFi.begin(SECRET_SSID, SECRET_PASS);

    if (WiFi.status() == WL_CONNECTED) {
      ntpUDP.begin(1337); // port 1337
      return 0;
    }

    return 1; // Wifi failed to connect
  }

// Disconnect Wifi. Stop udp client. Hardcoded delay of 3s
  void disconnectFromWifi() {
    ntpUDP.stop();
    delay(1000);

    if (WiFi.status() == WL_CONNECTED) {
      WiFi.disconnect();
      delay(1000);
    }

    WiFi.end();
    delay(1000);
  }

// Get WiFi status. 1 is connected, 0 otherwise.
  int getWifiStatus(){
    return WiFi.status() == WL_CONNECTED ? 1 : 0;
  }

  // Send emails for notifying startup status and verbose errors
  // void sendEmail(String notification) {
  //   EMailSender::EMailMessage message;
  //   message.subject = "RiseNShine - Notification";
  //   message.message = notification;
  //   emailSender.send("aarona493@gmail.com", message);
  //
  //   delay(5000);
  // }
};

#endif

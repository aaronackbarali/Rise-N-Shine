
#define SEVENTYYEARS 2208988800UL
#define NTP_PACKET_SIZE 48

#include "NTP.h"

byte _packetBuffer[NTP_PACKET_SIZE];
IPAddress _poolServerIP = IPAddress(192, 168, 1, 11); // Synology IP address

// Get NTP Epoch
void NTP::updateTime(boolean startup) {
  connectToWifi();

  // When starting up, loop until time is retrieved
  if (startup) {
    while (true) {
      if (getNTPTime()) {
        break;
      }
      delay(1000);
    }
  } else {
    // Try getting time 10 times
    for (byte i = 0; i < 10; i++) {
      if (getNTPTime()) {
        break;
      }
      delay(1000);
    }
  }

  disconnectFromWifi();
}

boolean NTP::getNTPTime() {
  // Flush any existing packets
  while (ntpUDP.parsePacket() != 0) {
    ntpUDP.flush();
  }

  sendNTPPacket();

  byte timeout = 0;
  int cb = ntpUDP.parsePacket();

  // Retry 100 times then timeout after 10s
  while (cb == 0) {
    delay(100);

    cb = ntpUDP.parsePacket();

    if (timeout > 100) {
      //digitalWrite(errorBit1, HIGH);
      return false;
    }

    timeout++;
  }

  _lastUpdate = millis();

  ntpUDP.read(_packetBuffer, NTP_PACKET_SIZE);

  // Combine the four bytes (two words) into a long integer. This is NTP time (seconds since Jan 1 1900)
  unsigned long highWord = word(_packetBuffer[40], _packetBuffer[41]);
  unsigned long lowWord = word(_packetBuffer[42], _packetBuffer[43]);
  unsigned long secsSince1900 = highWord << 16 | lowWord;

  _currentEpoc = secsSince1900 - SEVENTYYEARS;

  // digitalWrite(errorBit1, LOW); // Clear errors if any
  return true;
}

void NTP::sendNTPPacket() {
  // set all bytes in the buffer to 0
  memset(_packetBuffer, 0, NTP_PACKET_SIZE);

  // Initialize values needed to form NTP request
  _packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  _packetBuffer[1] = 0;     // Stratum, or type of clock
  _packetBuffer[2] = 6;     // Polling Interval
  _packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  _packetBuffer[12]  = 49;
  _packetBuffer[13]  = 0x4E;
  _packetBuffer[14]  = 49;
  _packetBuffer[15]  = 52;

  // All NTP fields have been given values, send packet requesting a timestamp
  ntpUDP.beginPacket(_poolServerIP, 123);

  ntpUDP.write(_packetBuffer, NTP_PACKET_SIZE);
  ntpUDP.endPacket();

  delay(10);
}


#ifndef TIMEHANDLER_H
#define TIMEHANDLER_H

#include <Arduino.h>
#include "NTP.h"

#define SEVENTYYEARS 2208988800UL
#define NTP_PACKET_SIZE 48

class TimeHandler : public NTP {
public:

  // TimeChangeRule usEDT  = {"EDT", Second, Sun, Mar, 2, -240};  // Eastern Daylight Time = UTC - 4 hours
  // TimeChangeRule usEST  = {"EST", First, Sun, Nov, 2, -300};   // Eastern Standard Time = UTC - 5 hours
  // Timezone *usET        = new Timezone(usEDT, usEST);

  void initializeTime(){
    NTP::updateTime(true);
  }

  void updateTime(){
    NTP::updateTime(false);
  }

  // Return Internal clock time to as a string
  String printTime() {
    String HH = getHours() < 10 ? "0" : "";
    HH.concat(getHours());

    String MM = getMinutes() < 10 ? "0" : "";
    MM.concat(getMinutes());

    String vTime = "";
    vTime.concat(HH);
    vTime.concat(":");
    vTime.concat(MM);
    return vTime;
  }

  int getHours() {
    return ((easternTime()  % 86400L) / 3600);
  }

  int getMinutes() {
    return ((easternTime() % 3600) / 60);
  }

  int getSeconds() {
    return (easternTime() % 60);
  }

  unsigned long easternTime() {
    return getEpochTime();
    // return usET->toLocal(getEpochTime());
  }

  unsigned long getEpochTime() {
    return _currentEpoc + // Epoch returned by the NTP server
           ((millis() - _lastUpdate) / 1000); // Time since last update
  }

};

#endif

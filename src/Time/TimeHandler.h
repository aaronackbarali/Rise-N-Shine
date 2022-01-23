
#ifndef TIMEHANDLER_H
#define TIMEHANDLER_H

#include <TimeLib.h>
#include "NTP.h"
#include "DST_LUT.h"

class TimeHandler : public NTP {
public:
  // EDT from second Sunday in March to first Sunday in November
  int EDT_Offset = -14400; // UTC-4 hours
  int EST_Offset = -18000; // UTC-5 hours

  // Method: Return the epoch
  unsigned long getEpochTime() {
    return _currentEpoc + // Epoch returned by the NTP server
           ((millis() - _lastUpdate) / 1000); // Time since last update
  }

  // Method: Loop that only exits once the time is updated
  void initializeTime(){
    NTP::updateTime(true);
    setTime(getEpochTime());
  }

  // Method: Try to update the time (10 tries)
  void updateTime(){
    NTP::updateTime(false);
    setTime(getEpochTime());
  }

  // return date as MMDDhhmm
  int UTC_Timestamp(){
    int timestamp = month() * 1000000;
    timestamp += day() * 10000;
    timestamp += hour() * 100;
    timestamp += minute();
    return timestamp;
  }

  int DST_Offset(){
    int vDate = UTC_Timestamp();

    // 03DD0159 where DD is the second Sunday of March
    int ssom = 3000000 + DST_LUT[year() % 400] * 10000 + 159;

    // 11DD0159 where DD is the first Sunday of November
    int fson = 11000000 + (DST_LUT[year() % 400] - 7) * 10000 + 200;

    if(vDate > ssom && vDate < fson){
      return EDT_Offset;
    }

    return EST_Offset;
  }

  unsigned long easternTime() {
    return getEpochTime() + DST_Offset();
  }

  int getHours() {
    return ((easternTime() % 86400L) / 3600);
  }

  int getMinutes() {
    return ((easternTime() % 3600) / 60);
  }

  int getSeconds() {
    return (easternTime() % 60);
  }

  int getFormattedTime(){
    return getHours() * 100 + getMinutes();
  }

  // Return internal clock time as a string
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
};

#endif

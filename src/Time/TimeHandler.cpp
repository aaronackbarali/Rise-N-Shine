
#include <TimeLib.h>
#include "TimeHandler.h"
#include "DST_LUT.h"

// EDT from second Sunday in March to first Sunday in November
const int EDT_Offset = -14400; // UTC-4 hours
const int EST_Offset = -18000; // UTC-5 hours

// Method: Return the epoch
unsigned long TimeHandler::getEpochTime() {
  return _currentEpoc + // Epoch returned by the NTP server
         ((millis() - _lastUpdate) / 1000); // Time since last update
}

// Method: Loop that only exits once the time is updated
void TimeHandler::initializeTime(){
  NTP::updateTime(true);
  setTime(getEpochTime());
}

// Method: Returns date as MMDDhhmm
int TimeHandler::UTC_Timestamp(){
  int timestamp = month() * 1000000;
  timestamp += day() * 10000;
  timestamp += hour() * 100;
  timestamp += minute();
  return timestamp;
}

// Method: Returns the offset needed for eastern timezone
int TimeHandler::DST_Offset(){
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

// Method: Gets internal time, returns in eastern timezone
unsigned long TimeHandler::easternTime() {
  return getEpochTime() + DST_Offset();
}

// Method: Gets internal hours
int TimeHandler::getHours() {
  return ((easternTime() % 86400L) / 3600);
}

// Method: Gets internal minutes
int TimeHandler::getMinutes() {
  return ((easternTime() % 3600) / 60);
}

// Method: Gets time HHMM
int TimeHandler::getTime() {
  // Update time if last update was more than 30 minutes ago
  if( (millis() - _lastUpdate) > 1800000 ){
    NTP::updateTime(false);
    setTime(getEpochTime());
  }

  return getHours() * 100 + getMinutes();
}

// Method: Returns internal time formatted as HH:MM
String TimeHandler::formatTime() {
  String vTime = getHours() < 10 ? "0" : "";
  vTime.concat(getHours());
  vTime.concat(":");
  vTime.concat(getMinutes() < 10 ? "0" : "");
  vTime.concat(getMinutes());

  return vTime;
}


#ifndef TIMEHANDLER_H
#define TIMEHANDLER_H

#include "NTP.h"

class TimeHandler : public NTP {
public:
  // Method: Return the epoch
  unsigned long getEpochTime();

  // Method: Loop that only exits once the time is updated
  void initializeTime();

  // Method: Returns date as MMDDhhmm
  int UTC_Timestamp();

  // Method: Returns the offset needed for eastern timezone
  int DST_Offset();

  // Method: Gets internal time, returns in eastern timezone
  unsigned long easternTime();

  // Method: Gets internal hours
  int getHours();

  // Method: Gets internal minutes
  int getMinutes();

  // Method: Gets time HHMM
  int getTime();

  // Method: Returns internal time formatted as HH:MM
  String formatTime();
};

#endif

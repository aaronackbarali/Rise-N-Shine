
#include "./SPI/SPI_Handler.h"

static SPI_Handler spi_Handler;

static int fullRefreshTrigger = 0;
static int vNow = 0;    // time HHMM
static int delta = 2;   // alarm window = vNow +/- delta
static String vNowFmtd = "00:00"; // time formatted HH:MM

static const int alarm = 855; // alarm time 24h format HHMM

void setup() {
  delay(10000);

  spi_Handler.initializeTime();
  spi_Handler.initializeDisplay();
  spi_Handler.print64(spi_Handler.formatTime(), true);
}

// Every minute, print time to display, full refresh every 5th print
void loop() {
  delay(60000);

  // getTime syncs every 30 min, format time is internal time formatted
  vNow = spi_Handler.getTime();
  vNowFmtd = spi_Handler.formatTime();

  // Print time to epd
  if (fullRefreshTrigger == 5) {
    spi_Handler.print64(vNowFmtd, true);
    fullRefreshTrigger = 0;
  } else {
    spi_Handler.print64(vNowFmtd, false);
    fullRefreshTrigger++;
  }

  // If you're within a 2 minute window of the alarm, start opening
  if (alarm - delta <= vNow && vNow <= alarm + delta ) {
    spi_Handler.openCurtains();
    fullRefreshTrigger = 5;
  }
}

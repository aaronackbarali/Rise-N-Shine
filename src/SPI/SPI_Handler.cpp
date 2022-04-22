
#include "SPI_Handler.h"
#include "wiring_private.h"

#include "EPD/EPD_Handler.h"
#include "TMC/CurtainHandler.h"
#include "Time/TimeHandler.h"

static SPIClassSAMD mySPI(&sercom1, SPI_CIPO, SPI_SCK, SPI_COPI, SPI_PAD_0_SCK_1, SERCOM_RX_PAD_3);
static CurtainHandler curtainHandler(mySPI);
static EPD_Handler epdHandler(mySPI);
static TimeHandler timeHandler;

// Constructor: Initializes req pins
SPI_Handler::SPI_Handler(){
  pinMode(EPD_BUSY_PIN, INPUT);

  pinMode(EPD_CS_PIN, OUTPUT);
  pinMode(EPD_RST_PIN, OUTPUT);
  pinMode(EPD_DC_PIN, OUTPUT);

  pinMode(TMC_PWR_A, OUTPUT);
  pinMode(TMC_PWR_B, OUTPUT);
  pinMode(TMC_PWR_C, OUTPUT);
  pinMode(TMC_CS_PIN, OUTPUT);

  digitalWrite(TMC_PWR_A, LOW);
  digitalWrite(TMC_PWR_B, LOW);
  digitalWrite(TMC_PWR_C, LOW);
  digitalWrite(TMC_CS_PIN, LOW);

  SPI.begin();

  pinPeripheral(SPI_COPI, PIO_SERCOM);
  pinPeripheral(SPI_CIPO, PIO_SERCOM);
  pinPeripheral(SPI_SCK, PIO_SERCOM);
}

// Method: Initial time sync, exits loop only when sync achieved
void SPI_Handler::initializeTime(){
  timeHandler.initializeTime();
}

// Method: Gets internal time (format HHMM). Will sync time if 30min since last synced
int SPI_Handler::getTime(){
  return timeHandler.getTime();
}

// Method: Returns internal time formatted as HH:MM
String SPI_Handler::formatTime(){
  return timeHandler.formatTime();
}

// Method: starts SPI, calls curtainHandler.OpenCurtains, ends SPI
void SPI_Handler::openCurtains(){
  mySPI.beginTransaction(SPISettings(2000000, MSBFIRST, SPI_MODE0));

  curtainHandler.openCurtains();

  mySPI.endTransaction();
}

// Method: Initializes display, soft reset
void SPI_Handler::initializeDisplay(){
  mySPI.beginTransaction(SPISettings(2000000, MSBFIRST, SPI_MODE0));

  epdHandler.initializeDisplay();

  mySPI.endTransaction();
}

// Method: Prints string, 64pt. Boolean for full or patrial refresh
void SPI_Handler::print64(String str, bool full){
  mySPI.beginTransaction(SPISettings(2000000, MSBFIRST, SPI_MODE0));

  epdHandler.print64(str, full);

  mySPI.endTransaction();
}

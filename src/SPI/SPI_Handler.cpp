
#include <SPI.h>
#include "SPI_Handler.h"
#include "wiring_private.h"
#include "pinDef.h"

SPIClassSAMD SPI_Handler::mySPI (&sercom1, SPI_CIPO, SPI_SCK, SPI_COPI, SPI_PAD_0_SCK_1, SERCOM_RX_PAD_3);
CurtainHandler SPI_Handler::curtainHandler (SPI_Handler::mySPI);

SPI_Handler::SPI_Handler() {
  pinMode(EPD_CS_PIN, OUTPUT);
  pinMode(EPD_RST_PIN, OUTPUT);
  pinMode(EPD_DC_PIN, OUTPUT);
  pinMode(EPD_BUSY_PIN, INPUT);

  pinMode(TMC_DRV_ENN_PIN, OUTPUT);
  pinMode(TMC_CS_PIN, OUTPUT);

  digitalWrite(TMC_DRV_ENN_PIN, HIGH);

  SPI.begin();
  pinPeripheral(SPI_COPI, PIO_SERCOM); // COPI
  pinPeripheral(SPI_CIPO, PIO_SERCOM); // CIPO
  pinPeripheral(SPI_SCK, PIO_SERCOM);  // SCK
  //SPI.beginTransaction(SPISettings(2000000, MSBFIRST, SPI_MODE0));
}

void SPI_Handler::openCurtains(){
  curtainHandler.openCurtains();
}

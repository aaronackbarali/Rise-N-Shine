
#include "EPD_SPI.h"

uint8_t EPD_SPI::CS; // EPD Chip Select Pin #
uint8_t EPD_SPI::DC; // EPD Data(HIGH)/Command(LOW) Pin #
uint8_t EPD_SPI::RST; // EPD Rest Pin #
uint8_t EPD_SPI::BSY; // EPD Busy Pin #

// Constructor: Sets chip select pin and gets SPI object for transfers
EPD_SPI::EPD_SPI(
  uint8_t chipSelectPin,
  uint8_t dcPin,
  uint8_t resetPin,
  uint8_t busyPin,
  SPIClass &spi
) : _spi(&spi) {
	CS = chipSelectPin;
  DC = dcPin;
  RST = resetPin;
  BSY = busyPin;
}

// Method: Send a command to the EPD
void EPD_SPI::SendCommand(unsigned char command) {
  digitalWrite(DC, LOW);
  digitalWrite(CS, LOW);
  _spi->transfer(command);
  digitalWrite(CS, HIGH);
}

// Method: Send a byte of data to the EPD
void EPD_SPI::SendData(unsigned char dat) {
  digitalWrite(DC, HIGH);
  digitalWrite(CS, LOW);
  _spi->transfer(dat);
  digitalWrite(CS, HIGH);
}

// Method: Module reset. Used to awaken the module in deep sleep. See Epd::Sleep();
void EPD_SPI::Reset() {
  digitalWrite(RST, HIGH);
  delay(20);
  digitalWrite(RST, LOW);
  delay(5);
  digitalWrite(RST, HIGH);
  delay(20);
}

// Method: Wait until the busy_pin goes LOW
void EPD_SPI::WaitUntilIdle() {
  while (1) {	 //=1 BUSY
    if (digitalRead(BSY) == LOW)
      break;
    delay(5);
  }
  delay(5);
}

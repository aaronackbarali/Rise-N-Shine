
#include "TMC5160.h"
#include "TMC5160_SPI.h"

uint8_t CS;

TMC5160_SPI::TMC5160_SPI(uint8_t chipSelectPin, SPIClass &spi) : _spi(&spi) {
	CS = chipSelectPin;
}

void TMC5160_SPI::writeRegister(uint8_t address, uint32_t data){
	// Select TMC
	digitalWrite(CS, LOW);
	delay(1);

	// Send new register value
	_spi->transfer(address | WRITE_ACCESS);
	_spi->transfer((data & 0xFF000000) >> 24);
	_spi->transfer((data & 0xFF0000) >> 16);
	_spi->transfer((data & 0xFF00) >> 8);
	_spi->transfer(data & 0xFF);

	// Unselect TMC
	digitalWrite(CS, HIGH);
}

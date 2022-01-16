
#include "TMC5160.h"
#include "TMC5160_SPI.h"

uint8_t CS; // TMC5160 Chip Select Pin #

// Constructor: Sets chip select pin and gets SPI object for transfers
TMC5160_SPI::TMC5160_SPI(uint8_t chipSelectPin, SPIClass &spi) : _spi(&spi) {
	CS = chipSelectPin;
}

// Method: Transfers data to the TMC5160
void TMC5160_SPI::writeRegister(uint8_t address, uint32_t data){
	// Select TMC5160 (active:LOW)
	digitalWrite(CS, LOW);
	delay(1);

	// Send new register value
	_spi->transfer(address | WRITE_ACCESS);
	_spi->transfer((data & 0xFF000000) >> 24);
	_spi->transfer((data & 0xFF0000) >> 16);
	_spi->transfer((data & 0xFF00) >> 8);
	_spi->transfer(data & 0xFF);

	// Unselect TMC5160 (active:LOW)
	digitalWrite(CS, HIGH);
}


#include "TMC5160.h"
#include "TMC5160_SPI.h"

uint8_t CS;

TMC5160_SPI::TMC5160_SPI(uint8_t chipSelectPin, SPIClass &spi)
: _spiSettings(SPISettings(1000000, MSBFIRST, SPI_MODE0)), _spi(&spi) {
	CS = chipSelectPin;
}

uint8_t TMC5160_SPI::writeRegister(uint8_t address, uint32_t data){
	// address register
	digitalWrite(CS, LOW);
	delay(1);
	_spi->beginTransaction(_spiSettings);
	uint8_t status = _spi->transfer(address | WRITE_ACCESS);

	// send new register value
	_spi->transfer((data & 0xFF000000) >> 24);
	_spi->transfer((data & 0xFF0000) >> 16);
	_spi->transfer((data & 0xFF00) >> 8);
	_spi->transfer(data & 0xFF);

	_spi->endTransaction();
	digitalWrite(CS, HIGH);

	return status;
}

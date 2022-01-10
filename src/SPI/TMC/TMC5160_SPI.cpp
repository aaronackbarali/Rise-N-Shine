
#include "TMC5160.h"
#include "TMC5160_SPI.h"

TMC5160_SPI::TMC5160_SPI( uint8_t chipSelectPin, const SPISettings &spiSettings, SPIClass &spi )
: _CS(chipSelectPin), _spiSettings(spiSettings), _spi(&spi)
{
	pinMode(chipSelectPin, OUTPUT);
}


// calls to read/write registers must be bracketed by the begin/endTransaction calls

void _chipSelect( uint8_t pin, bool select )
{
	digitalWrite(pin, select?LOW:HIGH);
	if( select )
		delayMicroseconds(100);   // per spec, settling time is 100us
}

void TMC5160_SPI::_beginTransaction()
{
	_spi->beginTransaction(_spiSettings);
	_chipSelect(_CS, true);
}

void TMC5160_SPI::_endTransaction()
{
	_chipSelect(_CS, false);
	_spi->endTransaction();
}

uint8_t TMC5160_SPI::writeRegister(uint8_t address, uint32_t data)
{
	// address register
	_beginTransaction();
	uint8_t status = _spi->transfer(address | WRITE_ACCESS);

	// send new register value
	_spi->transfer((data & 0xFF000000) >> 24);
	_spi->transfer((data & 0xFF0000) >> 16);
	_spi->transfer((data & 0xFF00) >> 8);
	_spi->transfer(data & 0xFF);
	_endTransaction();

	return status;
}

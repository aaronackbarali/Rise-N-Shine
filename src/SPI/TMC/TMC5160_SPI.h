
#include "TMC5160.h"

/* SPI interface : 
 * the TMC5160 SWSEL input has to be low (default state).
 */
class TMC5160_SPI : public TMC5160 {
public:
	TMC5160_SPI( uint8_t chipSelectPin,	// pin to use for the SPI bus SS line
		const SPISettings &spiSettings = SPISettings(1000000, MSBFIRST, SPI_MODE0), // spi bus settings to use
		SPIClass& spi = SPI ); // spi class to use

	uint8_t  writeRegister(uint8_t address, uint32_t data);

private:
	uint8_t _CS;
	SPISettings _spiSettings;
	SPIClass *_spi;

	void _beginTransaction();
	void _endTransaction();
};

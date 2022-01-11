
#include "TMC5160.h"

/* SPI interface : 
 * the TMC5160 SWSEL input has to be low (default state).
 */
class TMC5160_SPI : public TMC5160 {
public:
	TMC5160_SPI( uint8_t chipSelectPin,	// pin to use for the SPI bus SS line
		SPIClass& spi = SPI ); // spi class to use

	uint8_t  writeRegister(uint8_t address, uint32_t data);
private:
	SPISettings _spiSettings;
	SPIClass *_spi;
};

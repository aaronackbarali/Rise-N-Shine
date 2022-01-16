
#include "TMC5160.h"

/* SPI interface : 
 * the TMC5160 SWSEL input has to be low (default state).
 */
class TMC5160_SPI : public TMC5160 {
public:
	TMC5160_SPI( uint8_t chipSelectPin, SPIClass& spi = SPI );

	void writeRegister(uint8_t address, uint32_t data);
private:
	//SPISettings _spiSettings;
	SPIClass *_spi;
};

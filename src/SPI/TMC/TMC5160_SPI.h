
#include "TMC5160.h"

// Class: Extends TMC5160, adding the SPI write layer
class TMC5160_SPI : public TMC5160 {
public:
	// Constructor:
	TMC5160_SPI(uint8_t chipSelectPin, SPIClass& spi = SPI);

	// Method: Transfers data to the TMC5160
	void writeRegister(uint8_t address, uint32_t data);
private:
	SPIClass *_spi;
	static uint8_t CS;

};

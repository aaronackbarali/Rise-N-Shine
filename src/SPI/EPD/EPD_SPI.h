
#include "EPD.h"

// Class: Extends TMC5160, adding the SPI write layer
class EPD_SPI : public EPD {
public:
	// Constructor:
	EPD_SPI(
		uint8_t chipSelectPin,
		uint8_t dcPin,
		uint8_t resetPin,
		uint8_t busyPin,
		SPIClass& spi = SPI
	);

	// Method: Transfers data to the TMC5160
	void SendCommand(unsigned char command);
	void SendData(unsigned char dat);
	void Reset();
	void WaitUntilIdle();
private:
	SPIClass *_spi;
	static uint8_t CS; // EPD Chip Select Pin #
	static uint8_t DC; // EPD Data(HIGH)/Command(LOW) Pin #
	static uint8_t RST; // EPD Rest Pin #
	static uint8_t BSY; // EPD Busy Pin #
};


#ifndef TMC5160_H
#define TMC5160_H

#include <Arduino.h>
#include <SPI.h>
#include "TMC5160_registers.h"

class TMC5160 {
public:
	static constexpr uint8_t IC_VERSION = 0x30;
	static constexpr uint32_t DEFAULT_F_CLK = 12000000; // Typical internal clock frequency in Hz.

	enum MotorDirection { NORMAL_MOTOR_DIRECTION =	0x00, INVERSE_MOTOR_DIRECTION = 0x1 };
	enum RampMode { POSITIONING_MODE, VELOCITY_MODE, HOLD_MODE };

	struct PowerStageParameters {
		uint8_t drvStrength = 0; // MOSFET gate driver current (0 to 3)
		uint8_t bbmTime = 0; // "Break Before Make" duration specified in ns (0 to 24)
		uint8_t bbmClks = 4; // "Break Before Make" duration specified in clock cycles (0 to 15).
	};

	struct MotorParameters {
		uint16_t globalScaler = 32; // global current scaling (32 to 256)
		uint8_t irun = 16; // motor run current (0 to 31). For best performance don't set lower than 16
		uint8_t ihold = 1; // standstill current (0 to 31). Set 70% of irun or lower.
		TMC5160_Reg::PWMCONF_freewheel_Values freewheeling = TMC5160_Reg::FREEWHEEL_NORMAL; // Freewheeling / passive braking of ihold = 0
		uint8_t pwmOfsInitial = 30; // initial stealthChop PWM amplitude offset (0-255)
		uint8_t pwmGradInitial = 0; // initial stealthChop velocity dependent gradient for PWM amplitude
	};

	/* Start the motor driver using the specified parameters.
	 * These should be tuned according to the power stage and motor used.
	 * Look in the examples for a config wizard.
	 * powerParams : power stage parameters
	 * motorParams : motor current parameters
	 * stepperDirection : normal / inverted
	 */

	virtual bool begin(const PowerStageParameters &powerParams, const MotorParameters &motorParams, MotorDirection stepperDirection);

	virtual void writeRegister(uint8_t address, uint32_t data) = 0;

	/* Ramp mode selection :
		- Positioning mode : autonomous move to XTARGET using all A, D and V parameters.
		- Velocity mode : follows VMAX and AMAX. Call setMaxSpeed() AFTER switching to velocity mode.
		- Hold mode : Keep current velocity until a stop event occurs.
	*/
	void setRampMode(RampMode mode);

	void setCurrentPosition(float position, bool updateEncoderPos = false); // Set the current internal position (steps) and optionally update the encoder counter as well to keep them in sync.
	void setTargetPosition(float position); // Set the target position /!\ Set all other motion profile parameters before
	void setMaxSpeed(float speed); // Set the max speed VMAX (steps/second)
	void setRampSpeeds(float startSpeed, float stopSpeed, float transitionSpeed); // Set the ramp start speed VSTART, ramp stop speed VSTOP, acceleration transition speed V1 (steps / second). /!\ Set VSTOP >= VSTART, VSTOP >= 0.1
	void setAcceleration(float maxAccel); // Set the ramp acceleration / deceleration (steps / second^2)

protected:
	static constexpr uint8_t WRITE_ACCESS = 0x80;	//Register write access for spi / uart communication

private:
	uint32_t _fclk = DEFAULT_F_CLK;
	RampMode _currentRampMode;
	static constexpr uint16_t _uStepCount = 256; // Number of microsteps per step
	TMC5160_Reg::CHOPCONF_Register _chopConf = { 0 }; //CHOPCONF register (saved here to be restored when disabling / enabling driver)

	// Following §14.1 Real world unit conversions
	// v[Hz] = v[5160A] * ( f CLK [Hz]/2 / 2^23 )
	long speedFromHz(float speedHz) { return (long)(speedHz / ((float)_fclk / (float)(1ul << 24)) * (float)_uStepCount); }

	// Following §14.1 Real world unit conversions
	// a[Hz/s] = a[5160A] * f CLK [Hz]^2 / (512*256) / 2^24
	long accelFromHz(float accelHz) { return (long)(accelHz / ((float)_fclk * (float)_fclk / (512.0*256.0) / (float)(1ul<<24)) * (float)_uStepCount); }
};

#endif // TMC5160_H

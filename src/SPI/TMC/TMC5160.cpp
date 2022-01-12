
#include "TMC5160.h"

bool TMC5160::begin(const PowerStageParameters &powerParams, const MotorParameters &motorParams, MotorDirection stepperDirection )
{
	/* Clear the reset and charge pump undervoltage flags */
	TMC5160_Reg::GSTAT_Register gstat = { 0 };
	gstat.reset = true;
	gstat.uv_cp = true;
	writeRegister(TMC5160_Reg::GSTAT, gstat.value);

	TMC5160_Reg::DRV_CONF_Register drvConf = { 0 };
	drvConf.drvstrength = constrain(powerParams.drvStrength, 0, 3);
	drvConf.bbmtime = constrain(powerParams.bbmTime, 0, 24);
	drvConf.bbmclks = constrain(powerParams.bbmClks, 0, 15);
	writeRegister(TMC5160_Reg::DRV_CONF, drvConf.value);

	writeRegister(TMC5160_Reg::GLOBAL_SCALER, constrain(motorParams.globalScaler, 32, 256));

	// set initial currents and delay
	TMC5160_Reg::IHOLD_IRUN_Register iholdrun = { 0 };
	iholdrun.ihold = constrain(motorParams.ihold, 0, 31);
	iholdrun.irun = constrain(motorParams.irun, 0, 31);
	iholdrun.iholddelay = 7;
	writeRegister(TMC5160_Reg::IHOLD_IRUN, iholdrun.value);

	// Set initial PWM values
	TMC5160_Reg::PWMCONF_Register pwmconf = { 0 };
	pwmconf.value = 0xC40C001E; //Reset default
	pwmconf.pwm_autoscale = false; //Temp to set OFS and GRAD initial values
	if (_fclk > DEFAULT_F_CLK)
		pwmconf.pwm_freq = 0;
	else
		pwmconf.pwm_freq = 0b01; // recommended : 35kHz with internal typ. 12MHZ clock. 0b01 => 2/683 * f_clk
	pwmconf.pwm_grad = motorParams.pwmGradInitial;
	pwmconf.pwm_ofs = motorParams.pwmOfsInitial;
	pwmconf.freewheel = motorParams.freewheeling;
	writeRegister(TMC5160_Reg::PWMCONF, pwmconf.value);

	pwmconf.pwm_autoscale = true;
	pwmconf.pwm_autograd = true;
	writeRegister(TMC5160_Reg::PWMCONF, pwmconf.value);

	// Recommended settings in quick config guide
	_chopConf.toff = 5;
	_chopConf.tbl = 2;
	_chopConf.hstrt_tfd = 4;
	_chopConf.hend_offset = 0;
	writeRegister(TMC5160_Reg::CHOPCONF, _chopConf.value);

	// use position mode
	setRampMode(POSITIONING_MODE);

	TMC5160_Reg::GCONF_Register gconf = { 0 };
	gconf.en_pwm_mode = true; //Enable stealthChop PWM mode
	gconf.shaft = stepperDirection;
	writeRegister(TMC5160_Reg::GCONF, gconf.value);

	//Set default start, stop, threshold speeds.
	setRampSpeeds(0, 0.1, 0); //Start, stop, threshold speeds */

	return false;
}

void TMC5160::setRampMode(TMC5160::RampMode mode){
	switch (mode){
		case POSITIONING_MODE:
		writeRegister(TMC5160_Reg::RAMPMODE, TMC5160_Reg::POSITIONING_MODE);
		break;

		case VELOCITY_MODE:
		setMaxSpeed(0); // There is no way to know if we should move in the positive or negative direction => set speed to 0.
		writeRegister(TMC5160_Reg::RAMPMODE, TMC5160_Reg::VELOCITY_MODE_POS);
		break;

		case HOLD_MODE:
		writeRegister(TMC5160_Reg::RAMPMODE, TMC5160_Reg::HOLD_MODE);
		break;
	}

	_currentRampMode = mode;
}

void TMC5160::setCurrentPosition(float position, bool updateEncoderPos){
	writeRegister(TMC5160_Reg::XACTUAL, (int)(position * (float)_uStepCount));
}

void TMC5160::setTargetPosition(float position){
	writeRegister(TMC5160_Reg::XTARGET, (int)(position * (float)_uStepCount));
}

void TMC5160::setMaxSpeed(float speed){
	writeRegister(TMC5160_Reg::VMAX, speedFromHz(fabs(speed)));

	if (_currentRampMode == VELOCITY_MODE){
		writeRegister(TMC5160_Reg::RAMPMODE, speed < 0.0f ? TMC5160_Reg::VELOCITY_MODE_NEG : TMC5160_Reg::VELOCITY_MODE_POS);
	}
}

void TMC5160::setRampSpeeds(float startSpeed, float stopSpeed, float transitionSpeed){
	writeRegister(TMC5160_Reg::VSTART, speedFromHz(fabs(startSpeed)));
	writeRegister(TMC5160_Reg::VSTOP, speedFromHz(fabs(stopSpeed)));
	writeRegister(TMC5160_Reg::V_1, speedFromHz(fabs(transitionSpeed)));
}

void TMC5160::setAcceleration(float maxAccel){
	writeRegister(TMC5160_Reg::AMAX, accelFromHz(fabs(maxAccel)));
	writeRegister(TMC5160_Reg::DMAX, accelFromHz(fabs(maxAccel)));
	writeRegister(TMC5160_Reg::A_1, accelFromHz(fabs(maxAccel)));
	writeRegister(TMC5160_Reg::D_1, accelFromHz(fabs(maxAccel)));
}

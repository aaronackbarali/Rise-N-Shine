
#ifndef CURTAINAHNDLER_H
#define CURTAINAHNDLER_H

#include <Arduino.h>
#include "TMC5160_SPI.h"
#include "./SPI/pinDef.h"
#include "./SPI/SPI_Handler.h"

class CurtainHandler{
public:

  int curtainStartTime  = 900;  // Time (HHMM) to start pulling open curtains, cannot be near syncTime. Default: 9am

  TMC5160_SPI motor = TMC5160_SPI(TMC_CS_PIN, 12000000, SPISettings(2000000, MSBFIRST, SPI_MODE0), SPI_Handler::mySPI);

  // Spool motor in then out 23 full rotations
  void openCurtains() {
    digitalWrite(TMC_DRV_ENN_PIN, HIGH);
    delay(1000);

    TMC5160::PowerStageParameters powerStageParams; // Defaults.
    TMC5160::MotorParameters motorParams;

    motor.begin(powerStageParams, motorParams, TMC5160::NORMAL_MOTOR_DIRECTION);

    // ramp definition
    motor.setRampMode(TMC5160::POSITIONING_MODE);
    motor.setMaxSpeed(20);     // Steps per second
    motor.setAcceleration(20);  // Steps per second^2

    delay(1000); // Standstill for automatic tuning

    motor.setTargetPosition(23 * 200); // 23 turns
    delay(23 * 10 * 1000 + 10000); // (23 revs * 10s/rev) + 10s (acc)deceleration buffer
    motor.setTargetPosition(0); // 23 turns back
    delay(23 * 10 * 1000 + 10000);

    digitalWrite(TMC_DRV_ENN_PIN, LOW);
    delay(1000);
  }

};

#endif

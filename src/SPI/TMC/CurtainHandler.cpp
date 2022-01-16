
#include "CurtainHandler.h"

// Constructor: calls motor constructor
CurtainHandler::CurtainHandler(SPIClass &spi) : _motor(TMC_CS_PIN, spi){
  digitalWrite(TMC_DRV_ENN_PIN, HIGH);
}

// Method: Spool motor in then out 23 full rotations
void CurtainHandler::openCurtains() {
  // Enable drive (active: LOW)
  digitalWrite(TMC_DRV_ENN_PIN, LOW);
  delay(1000);

  TMC5160::PowerStageParameters powerStageParams;
  TMC5160::MotorParameters motorParams;

  _motor.begin(powerStageParams, motorParams, TMC5160::NORMAL_MOTOR_DIRECTION);

  // motor.setMaxSpeed(20);     // Steps per second
  // motor.setAcceleration(20);  // Steps per second^2
  _motor.setMaxSpeed(200);     // Steps per second
  _motor.setAcceleration(20);

  delay(1000); // Standstill for automatic tuning
  // motor.setTargetPosition(23 * 200); // 23 turns
  // delay(23 * 10 * 1000 + 10000); // (23 revs * 10s/rev) + 10s (acc)deceleration buffer
  // motor.setTargetPosition(0); // 23 turns back
  // delay(23 * 10 * 1000 + 10000);
  _motor.setTargetPosition(10 * 200);
  delay(20000);

  // Disable drive (active: LOW)
  digitalWrite(TMC_DRV_ENN_PIN, HIGH);
  delay(1000);
}

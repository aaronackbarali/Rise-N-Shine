
#include "CurtainHandler.h"

// Constructor: calls motor constructor
CurtainHandler::CurtainHandler(SPIClass &spi) : motor(spi){
}

// Method: Spool motor in then out 23 full rotations
void CurtainHandler::openCurtains() {
  // Enable power
  digitalWrite(TMC_PWR_A, HIGH);
  digitalWrite(TMC_PWR_B, HIGH);
  digitalWrite(TMC_PWR_C, HIGH);
  delay(5000);

  TMC5160::PowerStageParameters powerStageParams;
  TMC5160::MotorParameters motorParams;

  motor.begin(powerStageParams, motorParams, TMC5160::NORMAL_MOTOR_DIRECTION);

  motor.setMaxSpeed(20);     // Steps per second
  motor.setAcceleration(20);  // Steps per second^2

  delay(1000); // Standstill for automatic tuning
  // motor.setTargetPosition(23 * 200); // 23 turns
  // delay(23 * 10 * 1000 + 10000); // (23 revs * 10s/rev) + 10s (acc)deceleration buffer
  // motor.setTargetPosition(0); // 23 turns back
  // delay(23 * 10 * 1000 + 10000);
  motor.setTargetPosition(100);
  delay(10000);

  // Disable power
  digitalWrite(TMC_PWR_A, LOW);
  digitalWrite(TMC_PWR_B, LOW);
  digitalWrite(TMC_PWR_C, LOW);
  delay(1000);
}

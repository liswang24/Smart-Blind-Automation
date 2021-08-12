void moveBlindsUp(void){
  digitalWrite(MOTOR_SPEED, SPEED);
  digitalWrite(MOTOR_IN1, LOW);
  digitalWrite(MOTOR_IN2, HIGH);
}
 
void moveBlindsDown(void){
  digitalWrite(MOTOR_SPEED, SPEED);
  digitalWrite(MOTOR_IN1, HIGH);
  digitalWrite(MOTOR_IN2, LOW);
}

void stopBlinds(void){
  digitalWrite(MOTOR_IN1, LOW);
  digitalWrite(MOTOR_IN2, LOW);
}

void moveBlindsToDesiredPosition(int desiredPosition) {
  Serial.print("Moving blinds to: ");
  Serial.println(desiredPosition);

  while (blindsPosition < desiredPosition) {
    Serial.println("Moving blinds up!");
    Serial.print("Current Position: ");
    Serial.println(blindsPosition);

    moveBlindsUp();
  }
  
  while (blindsPosition > desiredPosition) {
    Serial.println("Moving blinds down!");
    Serial.print("Current Position: ");
    Serial.println(blindsPosition);

    moveBlindsDown();
  }
}

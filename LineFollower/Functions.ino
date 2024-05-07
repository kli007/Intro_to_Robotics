void ISR_ChangeColor1() {
  Serial.println("Bob");
  timeNow = millis();
  deltaTime = timeNow - timePast;
  if (deltaTime>buttonDelay){
    button0 = 1;
    timePast=timeNow;
}
  
}

void ISR_ChangeColor2() {
  Serial.println("Fred");
  button1 = 1;

}

void followLine() {
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("Following line!");
  display.display();
  calculatePID();
}

void moveMotors( int leftMotorPower, int rightMotorPower){
  Serial.println("Here");
  if (leftMotorPower <0) {
    myLeftMotor->run(BACKWARD);
    leftMotorPower = - leftMotorPower;
  } else {myLeftMotor->run(FORWARD);}
  if (rightMotorPower <0) {
    myRightMotor->run(BACKWARD);
    rightMotorPower = - rightMotorPower;
  } else {myRightMotor->run(FORWARD);}
  if (leftMotorPower > 255) {
    leftMotorPower = 255;
  }
  if (rightMotorPower > 255) {
    rightMotorPower = 255; 
  }
   myLeftMotor->setSpeed(leftMotorPower);
   myRightMotor->setSpeed(rightMotorPower);
   Serial.println(leftMotorPower);
   Serial.println("Done");
}

void calculatePID() {
  uint16_t r, g, b, c;
  int PID;
  apds.getColorData(&r, &g, &b, &c);
  error = nominalValue - c;
  deltaError = error-previousError;
  sumError = sumError + error;
  PID = kp*error + kd*deltaError + ki*sumError;
  previousError = error;
  moveMotors ((speed+PID),(speed-PID));

  display.clearDisplay();
  display.setCursor(0,0);
  display.println("Following...");
  display.println();
  display.print("Error = ");
  display.println(error);
  display.display();
}
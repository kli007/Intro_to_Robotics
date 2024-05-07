void spin(){
  //1st 
  
  drive(FIRST_RIGHT_SPEED, FIRST_LEFT_SPEED, 5000);

  //2nd
  drive(SECOND_RIGHT_SPEED, SECOND_LEFT_SPEED, 5000);

  //3rd
  drive(THIRD_RIGHT_SPEED, THIRD_LEFT_SPEED, 5000);

  wheelOn=false;
  pixels.setPixelColor(0, pixels.Color(0, 150, 150));
  delay(200);
  pixels.show();
  delay(300);
}

void drive(int rSpeed, int lSpeed, int time){
  long prevTime=millis();
  if (rSpeed>=0){
    rightMotor->run(FORWARD);
  }
  else{
    rightMotor->run(BACKWARD);
    rSpeed=-rSpeed;
  }
  if (lSpeed>=0){
    leftMotor->run(FORWARD);
  }
  else{
    leftMotor->run(BACKWARD);
    lSpeed=-lSpeed;
  }
  rightMotor->setSpeed(rSpeed);
  leftMotor->setSpeed(lSpeed);
  while(millis()-prevTime<=time){
    calculateOmega();
  }
  rightMotor->setSpeed(0);
  leftMotor->setSpeed(0);
}

void ISR_ChangeColor1(){
  pixels.setPixelColor(0, pixels.Color(0,0,150));
  wheelOn=true;
}
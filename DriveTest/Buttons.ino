void spin(){
  //Forward 10cm
  drive(FORWARD, FORWARD, 150, 667);
  delay(3000);
  //Backward 10cm
  drive(BACKWARD, BACKWARD, 160, 667);
  delay(3000);
  //Turn Right 90
  drive(BACKWARD, FORWARD, 150, 640);
  delay(3000);
  //Turn Left 180
  drive(FORWARD, BACKWARD, 150, 1270);
  delay(3000);
  //Turn Left 90
  drive(FORWARD, BACKWARD, 150, 640);
  delay(3000);
  //Turn Right 18000
  drive(BACKWARD, FORWARD, 150, 1280);
  delay(3000);
 
  wheelOn=false;
  pixels.setPixelColor(0, pixels.Color(0, 150, 150));
  delay(200);
  pixels.show();
  delay(300);
}

void dance(){
  for(int i=0; i<=1; i++){
    //spin right
    drive(FORWARD, BACKWARD, 150, 2420);
    delay(500);

    //point right
    drive(FORWARD, BACKWARD, 150, 334);
    delay(300);

    //spin left
    drive(BACKWARD, FORWARD, 150, 2800);
    delay(500);

    //point left
    drive(BACKWARD, FORWARD, 150, 334);
    delay(300);

    //rapid spin right
    drive(FORWARD, BACKWARD, 135, 6720);
    delay(500);

    //moonwalk
    for (int x=0;x<=2;x++){
      drive(BACKWARD, BACKWARD, 135, 1100);
      delay(200);
      drive(BACKWARD, BACKWARD, 190, 400);
      delay(500);
    }

  //final left spin
    drive(BACKWARD, FORWARD, 180, 6250);
    delay(500);
  }
  moves=false;
}

void ISR_ChangeColor1(){
  pixels.setPixelColor(0, pixels.Color(0,0,150));
  wheelOn=true;
}

void ISR_ChangeColor2(){
  pixels.setPixelColor(1, pixels.Color(0,150,0));
  moves=true;
}

void drive(int RDir, int LDir, int speed, int time){
  rightMotor->run(RDir);
  leftMotor->run(LDir);
  rightMotor->setSpeed(speed);
  leftMotor->setSpeed(speed);
  delay(time);
  rightMotor->setSpeed(0);
  leftMotor->setSpeed(0);
}
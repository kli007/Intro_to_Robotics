void encoderCount(){
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("Position:");
  display.print(x);
  display.print(", ");
  display.println(y);
  display.print("Angle: ");
  display.println(theta*(180/3.141593));
  display.display();
  delay(5);
}

void updateRightEncoder(){
  int MSB = digitalRead(RH_ENCODER_A); //MSB = most significant bit
  int LSB = digitalRead(RH_ENCODER_B); //LSB = least significant bit

  int encoded = (MSB << 1) |LSB; //converting the 2 pin value to single number
  int sum  = (lastRightEncoded << 2) | encoded; //adding it to the previous encoded value

  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) rightEncoderValue--;
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) rightEncoderValue++;

  lastRightEncoded = encoded; //store this value for next time
}

void updateLeftEncoder(){
  int MSB = digitalRead(LH_ENCODER_A); //MSB = most significant bit
  int LSB = digitalRead(LH_ENCODER_B); //LSB = least significant bit

  int encoded = (MSB << 1) |LSB; //converting the 2 pin value to single number
  int sum  = (lastLeftEncoded << 2) | encoded; //adding it to the previous encoded value

  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) leftEncoderValue++;
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) leftEncoderValue--;

  lastLeftEncoded = encoded; //store this value for next time
}

void calculateOmega(){
  long currentMillis=millis();
  deltaMillis=currentMillis-preMillis;
  deltaMillis=deltaMillis/1000;
  preMillis=currentMillis;

  deltaRight=rightEncoderValue-prevRightEncoder;
  omegaRight=deltaRight/deltaMillis;
  omegaRight=omegaRight*(6.283185/1589.5);
  prevRightEncoder=rightEncoderValue;
  
  deltaLeft=leftEncoderValue-prevLeftEncoder; 
  omegaLeft=deltaLeft/deltaMillis;
  Serial.println(deltaLeft/deltaMillis);
  omegaLeft=omegaLeft*(6.283186/1430.13);
  prevLeftEncoder=leftEncoderValue;

  globalCoord();
}

void globalCoord(){
  float leftVelocity=.0325*omegaLeft;
  float rightVelocity=.0325*omegaRight;
  float velocity=(leftVelocity+rightVelocity)/2;
  float omega=rightVelocity-leftVelocity;
  omega=omega/.1063;
  float k00=velocity*cos(theta);
  float k01=velocity*sin(theta);
  float k10=velocity*cos(theta+((deltaMillis/2)*theta));
  float k11=velocity*sin(theta+((deltaMillis/2)*theta));
  float k30=velocity*cos(theta+(deltaMillis*theta));
  float k31=velocity*sin(theta+(deltaMillis*theta));
  x=x+((deltaMillis/6)*(k00+(2*(k10+k10))+k30));
  y=y+((deltaMillis/6)*(k01+(2*(k11+k11))+k31));
  theta=theta+((deltaMillis/6)*(omega+(2*(omega+omega))+omega));
  encoderCount();
}
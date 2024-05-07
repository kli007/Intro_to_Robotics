void pathFinder(){
  int space[5];
  int compare1;
  int compare2;
  int direction;
  
  //scanning the surroundings(north south east west) of the bot's location and their value according to the wavefront planner
  //setting those values and if they are at a grid or an object, that value will be set to 100
  if(botLocationX==0){
    space[4]=100;
  }
  else{
    space[4]=grid[botLocationX-1][botLocationY];
  }
  if(botLocationX==23){
    space[2]=100;
  }
  else{
    space[2]=grid[botLocationX+1][botLocationY];
  }
  if(botLocationY==0){
    space[1]=100;
  }
  else{
    space[1]=grid[botLocationX][botLocationY-1];
  }
  if(botLocationY==11){
    space[3]=100;
  }
  else{
    space[3]=grid[botLocationX][botLocationY+1];
  }
  

  if(space[1]==0){
    space[1]=100;
  }
  if(space[2]==0){
    space[2]=100;
  }
  if(space[3]==0){
    space[3]=100;
  }
  if(space[4]==0){
    space[4]=100;
  }

  //comparing the 4 spaces to determine which is the closest according to their value and them setting them to the movement subroutine
  if(space[2]<=space[4]){
    compare1=2;
  }
  else{
    compare1=4;
  }
  if(space[1]<=space[3]){
    compare2=1;
  }
  else{
    compare2=3;
  }
  if(space[compare1]<=space[compare2]){
    movement(compare1);
  }
  else{
    movement(compare2);
  }
}

void movement(int direction){
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("Position:");
  display.print(botLocationX);
  display.print(", ");
  display.println(botLocationY);

  //taking the determined space and changing directions until the bot is facing the same direction and then moving forward
  if(position<direction){
      turnRight();
      Serial.println("Turn Right");
    
  }
  else if(position>direction){
   
      turnLeft();
      Serial.println("Turn Left");
    
  }
  if(position==direction){
    
      moveForward();
      Serial.println("Move Forward");
     
  }

  //readjusting the values of the bot's location
  if(direction==1){
    botLocationY=botLocationY-1;
  }
  if(direction==2){
    botLocationX=botLocationX+1;
  }
  if(direction==3){
    botLocationY=botLocationY+1;
  }
  if(direction==4){
    botLocationX=botLocationX-1;
  }
  Serial.print("Move To : (");
  Serial.print(botLocationX);
  Serial.print(",");
  Serial.print(botLocationY);
  Serial.println(")");  
  display.display();
}
 
//subroutines for actually moving the bot
void moveForward(){
  leftSpeed=120;
  rightSpeed=120;
  rightMotor->run(FORWARD);
  leftMotor->run(FORWARD);
  rightMotor->setSpeed(120);
  leftMotor->setSpeed(120);

  moveLeft=700.7;
  moveRight=778.78;
}

void turnLeft(){
  leftSpeed=120;
  rightSpeed=120;
  rightMotor->run(FORWARD);
  leftMotor->run(BACKWARD);
  rightMotor->setSpeed(120);
  leftMotor->setSpeed(120);

  moveLeft=620;
  moveRight=675;
  position=position-1;
    if(position<1){
    position=4;
  }
}

void turnRight(){
  leftSpeed=120;
  rightSpeed=120;
  rightMotor->run(BACKWARD);
  leftMotor->run(FORWARD);
  rightMotor->setSpeed(120);
  leftMotor->setSpeed(120);

  moveLeft=620;
  moveRight=675;
  position=position+1;
  if(position>4){
    position=1;
  }
}

void ISR_ChangeColor1(){
  pixels.setPixelColor(0, pixels.Color(0,0,150));
  wheelOn=true;
}
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <math.h>
#include <Adafruit_MotorShield.h>
#include <Adafruit_NeoPixel.h>


Adafruit_SH1107 display = Adafruit_SH1107(64, 128, &Wire);
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

Adafruit_DCMotor *rightMotor = AFMS.getMotor(4);
Adafruit_DCMotor *leftMotor = AFMS.getMotor(3);

// pins for the encoder inputs
#define RH_ENCODER_A 10
#define RH_ENCODER_B 11
#define LH_ENCODER_A 13
#define LH_ENCODER_B 12

#define PIN 9
#define NUMPIXELS 2

//defines the parameters of the grid
#define X_OF_GRID 24
#define Y_OF_GRID 12

//defines the position of the goal
#define X_OF_GOAL 16
#define Y_OF_GOAL 2

//defines the position of the start position
#define X_OF_START 4
#define Y_OF_START 7

int grid[X_OF_GRID][Y_OF_GRID];
int pointOfInterest[2][288];
int placeholder=0;

//the direction the bot is facing, 1= North, 2=East, 3=South, 4=West
int position = 1;

int botLocationX=X_OF_START;
int botLocationY=Y_OF_START;

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

bool wheelOn=false;

volatile int lastRightEncoded = 0;
volatile int lastLeftEncoded = 0;
long rightEncoderValue = 0;
long leftEncoderValue = 0;

long prevRightEncoder = 0;
long prevLeftEncoder = 0;

long deltaRight = 0;
long deltaLeft = 0;

int leftSpeed=0;
int rightSpeed=0;

// variables to store the number of encoder pulses
// for each motor
volatile long leftCount = 0;
volatile long rightCount = 0;

long moveRight=0;
long moveLeft=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LH_ENCODER_A, INPUT_PULLUP);
  pinMode(LH_ENCODER_B, INPUT_PULLUP);
  pinMode(RH_ENCODER_A, INPUT_PULLUP);
  pinMode(RH_ENCODER_B, INPUT_PULLUP);
  display.begin(0x3C, true); // Address 0x3C default
  display.display();
  delay(1000);
  // Clear the buffer.
  display.clearDisplay();
  display.display();
  display.setRotation(-1);
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0,0);

  AFMS.begin();

  attachInterrupt(RH_ENCODER_A , updateRightEncoder, CHANGE);
  attachInterrupt(RH_ENCODER_B , updateRightEncoder, CHANGE);
  attachInterrupt(LH_ENCODER_A , updateLeftEncoder, CHANGE);
  attachInterrupt(LH_ENCODER_B , updateLeftEncoder, CHANGE);
  delay(2000);
  rightMotor->setSpeed(150);
  rightMotor->run(FORWARD);
  rightMotor->run(RELEASE);

  leftMotor->setSpeed(150);
  leftMotor->run(FORWARD);
  leftMotor->run(RELEASE);

  pixels.begin();

  pixels.setPixelColor(0, pixels.Color(250, 80, 0));
  pixels.setPixelColor(1, pixels.Color(150, 0, 150));
  
  pixels.show();
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);

  if (!AFMS.begin()) {         // create with the default frequency 1.6KHz

  // if (!AFMS.begin(1000)) {  // OR with a different frequency, say 1KHz

    Serial.println("Could not find Motor Shield. Check wiring.");

    while (1);

  }
  delay(2000);

  //the waverfront planner subroutines
  initializeGrid();
  createPOI();
  createObject();
  wavefront();
  displayGrid();
}

void loop() {
  // put your main code here, to run repeatedly:
  display.clearDisplay();
  display.setCursor(0,0);
  //if the bot isn't on the goal, the bot will continue to move, else it will stay still
  if (wheelOn == true) {
    delay(500);
    pathFinder();
    if(grid[botLocationX][botLocationY]==1){
      wheelOn=false;
    }
  }
  pixels.setPixelColor(0, pixels.Color(250, 80, 0));
  pixels.setPixelColor(1, pixels.Color(150, 0, 150));
  if(digitalRead(7)==LOW){
    ISR_ChangeColor1();
  }
  pixels.show();
  delay(50);
}
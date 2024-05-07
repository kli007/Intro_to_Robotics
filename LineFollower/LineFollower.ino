#include <Adafruit_NeoPixel.h>
#include "Adafruit_APDS9960.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <Adafruit_MotorShield.h>

Adafruit_APDS9960 apds;
Adafruit_SH1107 display = Adafruit_SH1107(64, 128, &Wire);
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// OLED FeatherWing buttons map to different pins depending on board:
#if defined(ESP8266)
  #define BUTTON_A  0
  #define BUTTON_B 16
  #define BUTTON_C  2
#elif defined(ESP32) && !defined(ARDUINO_ADAFRUIT_FEATHER_ESP32S2)
  #define BUTTON_A 15
  #define BUTTON_B 32
  #define BUTTON_C 14
#elif defined(ARDUINO_STM32_FEATHER)
  #define BUTTON_A PA15
  #define BUTTON_B PC7
  #define BUTTON_C PC5
#elif defined(TEENSYDUINO)
  #define BUTTON_A  4
  #define BUTTON_B  3
  #define BUTTON_C  8
#elif defined(ARDUINO_NRF52832_FEATHER)
  #define BUTTON_A 31
  #define BUTTON_B 30
  #define BUTTON_C 27
#else // 32u4, M0, M4, nrf52840, esp32-s2 and 328p
  #define BUTTON_A  9
  #define BUTTON_B  6
  #define BUTTON_C  5
#endif


// Which pin on the Arduino is connected to the NeoPixels?
#define PIN 9 
#define NUMPIXELS 2
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

Adafruit_DCMotor *myLED = AFMS.getMotor(1);
Adafruit_DCMotor *myLeftMotor = AFMS.getMotor(3);
Adafruit_DCMotor *myRightMotor = AFMS.getMotor(4);


int button0 = 0;
int button1 = 0;
int getWhite = 0;
int averageWhite = 0;
int getBlack = 0;
int runLine = 0;
int averageBlack = 0;
int nominalValue = 0;
long timeNow = 0;
long timePast = 0;
long buttonDelay = 500;

float kp = 1.8; 
float ki = .0019;
float kd = 1.95;

float error = 0;
float deltaError = 0;
float sumError = 0;
float previousError = 0;

int speed = 150; 

long deltaTime = 0;





void setup() {
  Serial.begin(9600);
  delay (2000);
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
  // put your setup code here, to run once:
  pixels.begin();
  pixels.setPixelColor(0, pixels.Color(150, 150, 150));
  pixels.setPixelColor(1, pixels.Color(150, 0, 150));
  pixels.show();
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  attachInterrupt(7, ISR_ChangeColor1, RISING);
  attachInterrupt(8, ISR_ChangeColor2, RISING);

  if(!apds.begin()){
    Serial.println("failed to initialize device! Please check your wiring.");
  }
  else Serial.println("Device initialized!");
  apds.enableColor(true);

  if (!AFMS.begin()) {         // create with the default frequency 1.6KHz
  // if (!AFMS.begin(1000)) {  // OR with a different frequency, say 1KHz
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
  Serial.println("Motor Shield found.");

  myLED->run(BACKWARD);
  myLED->setSpeed(255);
  Serial.println(apds.getADCIntegrationTime());
  //apds.setADCIntegrationTime(apds.setLED();

  display.print("Measure white.");
  display.display();
  timePast = millis();
}



void loop() {
  uint16_t r, g, b, c;
  // put your main code here, to run repeatedly:
  if (button0== 1) {
    
      if (getWhite == 1 && getBlack == 1) {
        pixels.setPixelColor(0, pixels.Color(0,255,0));
        pixels.show();
        //followLine();
        runLine = 1;
        button0 = 0; 
      }
      else if (getWhite == 1 && getBlack == 0) {
        button0=0;
        getBlack = 1;
        pixels.setPixelColor(0, pixels.Color(230,230,0));
        for (int i=0; i<5; i++){
          while(!apds.colorDataReady()){
          delay(5);
        }
          apds.getColorData(&r, &g, &b, &c);
          averageBlack = averageBlack + c;
        }
        averageBlack = averageBlack/5;
        nominalValue = (averageWhite-averageBlack)/2;
        display.clearDisplay();
        display.setCursor(0,0);
        display.print("Average white = ");
        display.println(averageWhite);
        display.print("Average black = ");
        display.println(averageBlack);
        display.print("Nominal Value = ");
        display.println(nominalValue);
        display.print("Ready to run.");
        display.display();
        Serial.println(averageWhite);
      }
      else if (getWhite == 0){
        button0=0;
        getWhite = 1;
        pixels.setPixelColor(0, pixels.Color(0,0,255));
        for (int i=0; i<5; i++){
          while(!apds.colorDataReady()){
          delay(5);
        }
          apds.getColorData(&r, &g, &b, &c);
          averageWhite = averageWhite + c;
        }
        averageWhite = averageWhite/5;
        display.clearDisplay();
        display.setCursor(0,0);
        display.print("Average white = ");
        display.println(averageWhite);
        display.print("Measure black.");
        display.display();
        Serial.println(averageWhite);
      }
    }
    
    
    
  if (runLine==1){
    followLine();
  }


  if (button1 == 1){
    moveMotors(0,0);
    display.clearDisplay();
    display.setCursor(0,0);
    display.print("Stopped!");
    display.display();
    runLine = 0;
  }


  pixels.show();

}
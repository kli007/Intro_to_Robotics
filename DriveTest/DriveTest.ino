
#include <Adafruit_MotorShield.h>
#include <Adafruit_NeoPixel.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *rightMotor = AFMS.getMotor(4);
Adafruit_DCMotor *leftMotor = AFMS.getMotor(3);

#define PIN 9
#define NUMPIXELS 2

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

bool wheelOn=false;
bool moves=false;


void setup() {
  Serial.begin(9600);  // set up Serial library at 9600 bps
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");

  if (!AFMS.begin()) {  // create with the default frequency 1.6KHz
                        // if (!AFMS.begin(1000)) {  // OR with a different frequency, say 1KHz
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1)
      ;
  }
  Serial.println("Motor Shield found.");

  // Set the speed to start, from 0 (off) to 255 (max speed)
  rightMotor->setSpeed(150);
  rightMotor->run(FORWARD);
  rightMotor->run(RELEASE);

  leftMotor->setSpeed(150);
  leftMotor->run(FORWARD);
  leftMotor->run(RELEASE);

  pixels.begin();
  delay(2000);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
}

void loop() {
  if (wheelOn == true) {
    delay(500);
    spin();
  }
  if (moves == true) {
    delay(500);
    dance();
  }
  
  pixels.setPixelColor(0, pixels.Color(250, 80, 0));
  pixels.setPixelColor(1, pixels.Color(150, 0, 150));

  if(digitalRead(7)==LOW){
    ISR_ChangeColor1();
  }
  if(digitalRead(8)==LOW){
    ISR_ChangeColor2();
  }
  pixels.show();
}

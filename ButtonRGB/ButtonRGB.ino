// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library

#include <Adafruit_NeoPixel.h>

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN 9 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 2 

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pixels.begin(); 
  delay(2000);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
}

void loop() {
  pixels.setPixelColor(0, pixels.Color(250,100,0));
  pixels.setPixelColor(1, pixels.Color(150,0,150));

  attachInterrupt(7, ISR_ChangeColor1, RISING);
  attachInterrupt(8, ISR_ChangeColor2, RISING);
  delay(500);
  pixels.show();
  delay(300); 
}

void ISR_ChangeColor1(){
  pixels.setPixelColor(0, pixels.Color(0,0,150));
}

void ISR_ChangeColor2(){
  pixels.setPixelColor(1, pixels.Color(0,150,0));
}
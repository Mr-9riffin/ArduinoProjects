#include <Adafruit_CircuitPlayground.h>

bool leftButtonPressed;

void setup() {
  CircuitPlayground.begin();
}

void loop() {
  leftButtonPressed = CircuitPlayground.leftButton();
  if (leftButtonPressed) {
    for (int i = 0; i < 10; i++) 
      CircuitPlayground.setPixelColor(i, 100,   100,   100);
    CircuitPlayground.playTone(523, 90);
    CircuitPlayground.clearPixels();
    delay(10);
    for (int i = 0; i < 10; i++) 
      CircuitPlayground.setPixelColor(i, 170,   170,   170);
    CircuitPlayground.playTone(587, 90);
    CircuitPlayground.clearPixels();
    delay(10);
    for (int i = 0; i < 10; i++) 
      CircuitPlayground.setPixelColor(i, 255,   255,   255);
    CircuitPlayground.playTone(659, 100);
    CircuitPlayground.setPixelColor(0, 255,   0,   0);
    CircuitPlayground.clearPixels();
    delay(100);
    
    for (int i = 0; i < 10; i++) 
      CircuitPlayground.setPixelColor(i, 170,   170,   170);
    CircuitPlayground.playTone(739, 90);
    CircuitPlayground.clearPixels();
    delay(10);
    for (int i = 0; i < 10; i++) 
      CircuitPlayground.setPixelColor(i, 255,   255,   255);
    CircuitPlayground.playTone(830, 100);
    CircuitPlayground.setPixelColor(0, 255,   0,   0);
    CircuitPlayground.clearPixels();
    delay(100);
    
    for (int i = 0; i < 10; i++) 
      CircuitPlayground.setPixelColor(i, 255,   255,   255);
    CircuitPlayground.playTone(739, 100);
    CircuitPlayground.setPixelColor(0, 255,   0,   0);
    CircuitPlayground.clearPixels();
    delay(100);
    
    for (int i = 0; i < 10; i++) 
      CircuitPlayground.setPixelColor(i, 170,   170,   170);
    CircuitPlayground.playTone(659, 90);
    CircuitPlayground.clearPixels();
    delay(10);
    for (int i = 0; i < 10; i++) 
      CircuitPlayground.setPixelColor(i, 255,   255,   255);
    CircuitPlayground.playTone(587, 100);
    CircuitPlayground.setPixelColor(0, 255,   0,   0);
    CircuitPlayground.clearPixels();
    delay(100);
  }
}

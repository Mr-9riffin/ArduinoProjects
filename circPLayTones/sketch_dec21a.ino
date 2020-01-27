#include <Adafruit_CircuitPlayground.h>

bool leftButtonPressed;

void setup() {
  CircuitPlayground.begin();
}

void loop() {
  leftButtonPressed = CircuitPlayground.leftButton();
  if (leftButtonPressed) {
    for (int i = 1; i < 20; i++) {
      
      CircuitPlayground.playTone(100 * i, 100);
      
    }
  }
}

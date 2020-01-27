#include <Adafruit_CircuitPlayground.h>
#include <Keyboard.h>

float X, Y, Z;

void setup() {
  Serial.begin(9600);
  CircuitPlayground.begin();
}

void loop() {
  X = CircuitPlayground.motionX();
  Y = CircuitPlayground.motionY();
  Z = CircuitPlayground.motionZ();

  Serial.print("X: ");
  Serial.print(X);
  Serial.print("  Y: ");
  Serial.print(Y);
  Serial.print("  Z: ");
  Serial.println(Z);

  if (Z > 13) {
    Keyboard.press(KEY_UP_ARROW);
  }
  else {
    Keyboard.release(KEY_UP_ARROW);
    }

  delay(100);
}

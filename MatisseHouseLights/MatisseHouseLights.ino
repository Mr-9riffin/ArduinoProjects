#include <Adafruit_CircuitPlayground.h>

bool slideSwitch;

void setup() {
  Serial.begin(9600);
  CircuitPlayground.begin();
  pinMode(3, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(0, OUTPUT);
  pinMode(12, OUTPUT);

  digitalWrite(3, LOW);
  digitalWrite(2, LOW);
  digitalWrite(1, LOW);
  digitalWrite(0, LOW);
  digitalWrite(12, LOW);

}

void loop() {

  digitalWrite(12, HIGH);

  delay(750);
  
  digitalWrite(3, HIGH);

  delay(750);

  digitalWrite(0, HIGH);

  delay(750);

  digitalWrite(1, HIGH);

  delay(750);

  digitalWrite(2, HIGH);

  delay(750);


  digitalWrite(2, LOW);

  delay(750);
  
  digitalWrite(1, LOW);

  delay(750);

  digitalWrite(0, LOW);

  delay(750);

  digitalWrite(3, LOW);

  delay(750);

  digitalWrite(12, LOW);

  delay(750);
}

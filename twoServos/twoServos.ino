#include <Servo.h>

#define SERVO_SPEED 25  //(minimum number of milliseconds per degree)
const int SW_pin = 2;   // digital pin connected to switch output
const int X_pin = 0;    // analog pin connected to X output
const int Y_pin = 1;    // analog pin connected to Y output
Servo servoX;  // create servo object to control a servo
Servo servoY;  // create servo object to control a servo
// twelve servo objects can be created on most boards

void setup() {
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
  Serial.begin(9600);
  servoX.attach(9);   // attaches the servo on pin 9 to the servo object
  servoX.write(110);  // Sets initial position of X servo
  servoY.attach(10);  // attaches the servo on pin 10 to the servo object
  servoY.write(110);  // Sets initial position of Y servo
}

void loop() {
  static unsigned long servo_time;
 
 // check time since last servo position update 
 if ((millis()-servo_time) >= SERVO_SPEED) {
   servo_time = millis(); // save time reference for next position update
   
    int servoXpos = 70 + analogRead(X_pin)/13;
    int servoYpos = 70 + analogRead(Y_pin)/13;
    /*Serial.print("X-axis: ");
    Serial.print(xpos);
    Serial.print("\n");*/

     // update servoX position
     // if desired position is different from current position move one step left or right
     if (servoXpos > servoX.read()) servoX.write(servoX.read() + 1);
     else if (servoXpos < servoX.read()) servoX.write(servoX.read() - 1);
  
     // update servoY position
     // if desired position is different from current position move one step left or right
     if (servoYpos > servoY.read()) servoY.write(servoY.read() + 1);
     else if (servoYpos < servoY.read()) servoY.write(servoY.read() - 1);
    
 }
}

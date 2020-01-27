int inPin = 0;  // the number of the input pin
int reading;    // the current reading from the input pin
int led1 = 3;  
int led2 = 4;
int buzz = 1; // Buzzer Pin

void setup() {
  pinMode(inPin, INPUT_PULLUP);
  pinMode(buzz, OUTPUT);
}

void loop() {

  reading = digitalRead(inPin);

  if (reading == 1){
    one();
  }
  if (reading == 0){
    analogWrite(led1,0);
    analogWrite(led2,0);
    noTone(buzz);
  }


}

void one() { 
  //This function produces the 1st siren sound with ON/OFF led transition.
  analogWrite(led2,0);
  analogWrite(led1,255);
  // Whoop up
  for(int hz = 440; hz < 1000; hz+=5){
    tone(buzz, hz);
    delay(15);
  }
  analogWrite(led1,0);
  analogWrite(led2,255);
  // Whoop down
  for(int hz = 1000; hz > 440; hz-=5){
    tone(buzz, hz);
    delay(15);
  }
  }

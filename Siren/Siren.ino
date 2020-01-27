int inPin = 2;  // the number of the input pin
int fireIn = 3;
int reading;           // the current reading from the input pin
int input=0;
int buzz=13; // Buzzer Pin
int j=3;
int k=12;

void setup() {
  Serial.begin(9600);
  pinMode(inPin, INPUT_PULLUP);
}

void loop() {

  reading = digitalRead(inPin);
  Serial.println(reading);

  

  if (reading == 1){
    one();
  }
  if (reading == 0){
    analogWrite(5,0);
    analogWrite(6,0);
  }


}

void one() { 
  //This function produces the 1st siren sound with ON/OFF led transition.
  analogWrite(5,0);
  analogWrite(6,255);
  // Whoop up
  for(int hz = 440; hz < 1000; hz+=5){
    tone(buzz, hz, 50);
    delay(5);
  }
  analogWrite(6,0);
  analogWrite(5,255);
  // Whoop down
  for(int hz = 1000; hz > 440; hz-=5){
    tone(buzz, hz, 50);
    delay(5);
  }
  }

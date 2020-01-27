//#include <SoftwareSerial.h>
 
//SoftwareSerial Monitor(5, 3);
int pinData= 0;
unsigned long lengthHeader;
unsigned long bit;
int byteValue;
int Rmotor1 = 1;
int Rmotor2 = 2;
int Lmotor1 = 4;
int Lmotor2 = 3;
int buttonPressed = 0;
const int Rbutton = 67; //ProRem 21  EleRem 67
const int Lbutton = 68; //ProRem 71  EleRem 68
const int Fbutton = 70; //ProRem 70  EleRem 70
const int buttonHeld = 255;
int duration = 250;

void setup() {
  
  //Monitor.begin(9600); 
  pinMode(Rmotor1, OUTPUT);
  pinMode(Lmotor1, OUTPUT);
  pinMode(Rmotor2, OUTPUT);
  pinMode(Lmotor2, OUTPUT);
  //pinMode(5, INPUT);
  pinMode(pinData, INPUT);
}

void loop() {
  lengthHeader = pulseIn(pinData, LOW);
  
  if(lengthHeader > 1500) {
    
    for(int i = 1; i <= 32; i++) {
      
      bit = pulseIn(pinData, HIGH);
      if (i > 16 && i <= 24)
        if(bit > 1000)
          byteValue = byteValue + (1 << (i - 17)); 
    }
    
    //Monitor.println(byteValue);
    buttonPressed = byteValue;
    byteValue=0;
    
  }

  switch (buttonPressed) {
    case Rbutton:
      digitalWrite(Rmotor1, HIGH);
      digitalWrite(Rmotor2, HIGH);
      delay(duration);
      buttonPressed = 0;
      break;
    case Lbutton:
      digitalWrite(Lmotor1, HIGH);
      digitalWrite(Lmotor2, HIGH);
      delay(duration);
      buttonPressed = 0;
      break;
    case Fbutton:
      digitalWrite(Rmotor1, HIGH);
      digitalWrite(Rmotor2, HIGH);
      digitalWrite(Lmotor1, HIGH);
      digitalWrite(Lmotor2, HIGH);
      delay(duration);
      buttonPressed = 0;
      break;
    case buttonHeld:
      delay(duration);
      buttonPressed = 0;
      break;
    default: 
      digitalWrite(Rmotor1, LOW);
      digitalWrite(Rmotor2, LOW);
      digitalWrite(Lmotor1, LOW);
      digitalWrite(Lmotor2, LOW);
      delay(duration);
    break;
  }
}

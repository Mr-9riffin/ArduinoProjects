#include <SD.h> // need to include the SD library
//#include <SDfatlib.h>

#define SD_ChipSelectPin 5  //example uses hardware SS pin 53 on Mega2560

#include <TMRpcm.h>           //  also need to include this library...
#include <SPI.h>

TMRpcm tmrpcm;   // create an object for use in this sketch

int knockSensor = 0;  
int knockSensor1 = 1;

byte val  = 0;
byte val1 = 0;

int THRESHOLD = 50;


void setup() {
  // put your setup code here, to run once:

 Serial.begin(9600);

  tmrpcm.speakerPin = 6; //5,6,11 or 46 on Mega, 9 on Uno, Nano, etc

  //Serial.begin(9600);
  pinMode(6,OUTPUT);
  //digitalWrite(46,HIGH);
  if (!SD.begin(SD_ChipSelectPin)) {  // see if the card is present and can be initialized:
    Serial.println("SD fail");  
    return;   // don't do anything more if not
  }
  else{
    Serial.println("Done");
  }
 // tmrpcm.volume(12);
  //tmrpcm.play("m.wav"); //the sound file "music" will play each time the arduino powers up, or is reset
  tmrpcm.play("Snare.wav");

}

void loop() {
  // put your main code here, to run repeatedly:
 val = analogRead(knockSensor);    
 val1 = analogRead(knockSensor1); 


  if (val >= THRESHOLD) {
    tmrpcm.play("Kick.wav");
    Serial.println("Thrash!");
    delay(10);
  }
     
  if (val1 >= THRESHOLD) {
    tmrpcm.play("Snare.wav");
    Serial.println("Snare!");
    delay(10);
  }
  delay(50);  // we have to make a delay to avoid overloading the serial port
}

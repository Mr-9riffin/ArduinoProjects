#include <SdFat.h>
//#include <SD.h>
#include "TMRpcm.h"
#include "SPI.h"

#define SD_ChipSelectPin 4

TMRpcm tmrpcm;
SdFat SD;

//bool isPlaying1 = tmrpcm.isPlaying(0);
//bool isPlaying2 = tmrpcm.isPlaying(1);
bool button1;
bool button2;
bool button3;
bool button4;

void setup(){
  tmrpcm.speakerPin = 9;
  pinMode(10, OUTPUT);
  pinMode(2, INPUT_PULLUP);
  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  tmrpcm.setVolume(5);
  Serial.begin(9600);
  
  
  if (!SD.begin(SD_ChipSelectPin)) {
    Serial.println("SD fail");
    return;
  }
  
}

void loop(){ 
  
  //isPlaying1 = tmrpcm.isPlaying(0);
  //isPlaying2 = tmrpcm.isPlaying(1);
  button1 = digitalRead(2);
  button2 = digitalRead(7);
  button3 = digitalRead(A0);
  button4 = digitalRead(A1);
  
  if (button1 == LOW)
  {
    tmrpcm.play("Crash2.wav");
    Serial.println("Crash");
    delay(50);
  }

  if (button2 == LOW)
  {
    tmrpcm.play("Snare1.wav", 1);
    Serial.println("Snare");
    delay(50);
  }

Serial.println(freeRam());
}

int freeRam () {
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}

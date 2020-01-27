#include <SdFat.h>
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
bool chan = 1;
int counter1 = 0;
int counter2 = 0;
int counter3 = 0;
int counter4 = 0;
int counterLimit = 2000;

void setup(){
  tmrpcm.speakerPin = 9;
  pinMode(10, OUTPUT);
  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  pinMode(A3, INPUT_PULLUP);
  tmrpcm.setVolume(4.8);
  //Serial.begin(9600);
  
  
  if (!SD.begin(SD_ChipSelectPin)) {
    Serial.println("SD fail");
    return;
  }
  
}

void loop(){ 
  
  if (counter1 == 0) button1 = digitalRead(A0);
  if (counter2 == 0) button2 = digitalRead(A1);
  if (counter3 == 0) button3 = digitalRead(A2);
  if (counter4 == 0) button4 = digitalRead(A3);
  
  if (button1 == LOW)
  {
      tmrpcm.play("Crash2.wav", chan);
      if(chan == 1) chan = 0;
      else chan = 1;
      counter1 = counterLimit;
      button1 = HIGH;
  }

  if (button2 == LOW)
  {
      tmrpcm.play("Snare1.wav", chan);
      if(chan == 1) chan = 0;
      else chan = 1;
      counter2 = counterLimit;
      button2 = HIGH;
  }

  if (button3 == LOW)
  {
      tmrpcm.play("Kick1.wav", chan);
      if(chan == 1) chan = 0;
      else chan = 1;
      counter3 = counterLimit;
      button3 = HIGH;
  }

  if (button4 == LOW)
  {
      tmrpcm.play("Tom1.wav", chan);
      if(chan == 1) chan = 0;
      else chan = 1;
      counter4 = counterLimit;
      button4 = HIGH;
    }

if (counter1 != 0) counter1--;
if (counter2 != 0) counter2--;
if (counter3 != 0) counter3--;
if (counter4 != 0) counter4--;
  

//Serial.println(freeRam());
}

/*int freeRam () {
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}*/

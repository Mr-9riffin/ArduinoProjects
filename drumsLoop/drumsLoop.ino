#include <SD.h>
#include "TMRpcm.h"
#include "SPI.h"

#define SD_ChipSelectPin 4

TMRpcm tmrpcm;

void setup(){
tmrpcm.speakerPin = 9;
pinMode(10, OUTPUT);
Serial.begin(9600);
if (!SD.begin(SD_ChipSelectPin)) {
Serial.println("SD fail");
return;
}

}

void loop(){ 
  tmrpcm.setVolume(5);
  tmrpcm.play("Crash1.wav"); 
  delay(1000);
  tmrpcm.play("Snare1.wav",1); 
  delay(3000);

Serial.println(freeRam());
}

int freeRam () {
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}





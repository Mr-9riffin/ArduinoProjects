#include <Adafruit_CircuitPlayground.h>




int X, Y;
int red, green, blue;


void setup() {
  CircuitPlayground.begin();
  
}

void loop() {
    
    for(int j = 0; j < 10; j++) {
      
          X = abs(CircuitPlayground.motionX());  
          Y = abs(CircuitPlayground.motionY());  
          
          red = abs(X) * 20;
          green = 0;
          blue = abs(Y) * 20;
          for(int k = 0; k < 10; k++) {
          CircuitPlayground.setPixelColor(k, red,   green, blue);
          }
          CircuitPlayground.playTone(X * 100 + 400, Y * 10);
          delay(30);
       }
       CircuitPlayground.clearPixels();
    } 


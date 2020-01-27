/* insert sound code into setup to play once, main loop to repeat, or into sound() function to call when wanted (button push, etc...)// Speaker must be on pin 8, see setup here: http://www.arduino.cc/en/Tutorial/PlayMelody
*/

#include "pitches.h"  // must include open source pitches.h found online in libraries folder

void setup() {
  // do nothing
}

void loop() {
  // Play coin sound   
  tone(8,NOTE_B5,100);
  delay(100);
  tone(8,NOTE_E6,850);
  delay(800);
  noTone(8);
  
  delay(2000);  // pause 2 seconds

  // Play 1-up sound
  tone(8,NOTE_E6,125);
  delay(130);
  tone(8,NOTE_G6,125);
  delay(130);
  tone(8,NOTE_E7,125);
  delay(130);
  tone(8,NOTE_C7,125);
  delay(130);
  tone(8,NOTE_D7,125);
  delay(130);
  tone(8,NOTE_G7,125);
  delay(125);
  noTone(8);

  delay(2000);  // pause 2 seconds

  // Play Fireball sound
  tone(8,NOTE_G4,35);
  delay(35);
  tone(8,NOTE_G5,35);
  delay(35);
  tone(8,NOTE_G6,35);
  delay(35);
  noTone(8);
  
  delay(2000);  // pause 2 seconds

}

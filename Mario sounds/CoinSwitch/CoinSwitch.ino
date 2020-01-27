/* Better Debouncer
 * 
 * This debouncing circuit is more rugged, and will work with tilt switches!
 *
 * http://www.ladyada.net/learn/sensor/tilt.html
 */
 
int inPin = 2;  // the number of the input pin
int fireIn = 3;
int reading;           // the current reading from the input pin
 
// the following variables are long because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.

 
void setup()
{
  Serial.begin(9600);
  pinMode(inPin, INPUT_PULLUP);
  pinMode(fireIn, INPUT_PULLUP);
}
 
void loop()
{
 
  reading = digitalRead(inPin);
  Serial.println(reading);

  

  if (reading == 0){
    // Play coin sound   
  tone(8,988,100);
  delay(100);
  tone(8,1319,500);
  delay(800);
  noTone(8);
  delay(2000);
  }

  if ( digitalRead(fireIn) == 0){
    // Play Fireball sound
  tone(8,392,35);
  delay(35);
  tone(8,784,35);
  delay(35);
  tone(8,1568,35);
  delay(35);
  noTone(8);
  delay(50);
  }
 

}

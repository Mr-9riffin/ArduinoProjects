#include <SoftwareSerial.h>
 
SoftwareSerial Monitor(5, 4);
int pinData= 1;
unsigned long lengthHeader;
unsigned long bit;
int byteValue;

void setup() {
  
Monitor.begin(9600); 
pinMode(0, OUTPUT);
pinMode(4, OUTPUT);
pinMode(5, INPUT);
pinMode(pinData, INPUT);
}

void loop() {
  lengthHeader = pulseIn(pinData, LOW);

if(lengthHeader > 1500)
{


for(int i = 1; i <= 32; i++)
{
bit = pulseIn(pinData, HIGH);


if (i > 16 && i <= 24)
if(bit > 1000)
byteValue = byteValue + (1 << (i - 17)); 

}
Monitor.println(byteValue);

byteValue=0;

delay(250);
}

  //digitalWrite(0, HIGH);
  //Monitor.println("LED on");
  //delay(1000);
  //digitalWrite(0, LOW);

}

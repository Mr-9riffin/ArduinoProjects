

int pinData= 11;
unsigned long lengthHeader;
unsigned long bit;
int byteValue;

void setup()
{
Serial.begin(9600);
pinMode(pinData, INPUT);

}

void loop()
{

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
}
Serial.println(byteValue);

byteValue=0;

delay(250);
}


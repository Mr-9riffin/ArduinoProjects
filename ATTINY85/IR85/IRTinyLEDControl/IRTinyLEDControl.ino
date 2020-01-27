
int pinData = 0;
int RED_LED = 4;
int YELLOW_LED = 2; 

unsigned long lengthHeader;
unsigned long bit;
int byteValue;

void setup()
{
//Serial.begin(9600);
pinMode(pinData, INPUT);
analogWrite(RED_LED, 255);
analogWrite(YELLOW_LED, 255);
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
//Serial.println(byteValue);
if(byteValue == 67) {
      analogWrite(RED_LED, 0);
    } else if(byteValue == 68) {
      analogWrite(YELLOW_LED, 255);
    }

byteValue=0;

delay(20);
}


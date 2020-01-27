
void setup() {
  pinMode(A0, INPUT);
  Serial.begin(9600);
}

void loop() {
    
  Serial.println(analogRead(pulseIn(A0,LOW)));
  // put your main code here, to run repeatedly:

}

//DS3231:  SDA pin   -> Arduino Analog 4 or the dedicated SDA pin
//          SCL pin   -> Arduino Analog 5 or the dedicated SCL pin

//SD card attached to SPI bus as follows:
//  MOSI - pin 11
//  MISO - pin 12
//  CLK - pin 13
//  CS - pin 4 (for MKRZero SD: SDCARD_SS_PIN)

#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>
#include <SPI.h>
#include <SD.h>

File myFile;

void setup() {
  Serial.begin(9600);
  while (!Serial) ; // wait for serial
  delay(200);
  Serial.println("DS1307RTC Read Test");
  Serial.println("-------------------");

  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");
}

void loop() {
  tmElements_t tm;
  RTC.read(tm);
  String currentDate = "";
  String picTime;
  int currentMins = tm.Minute;
  String amPic = "";
  String pmPic = "";
  String dateData = "";

  currentDate += 
    print2digits(tm.Hour) + ":" +
    print2digits(tm.Minute) + ":" +
    print2digits(tm.Second) + ", Date (D/M/Y) = " +
    tm.Day + '/' + tm.Month + '/' + tmYearToCalendar(tm.Year);
    Serial.println("loop start " + currentDate);
  
  /*if (RTC.read(tm)) {
    Serial.print("Ok, Time = ");
    currentDate += 
    print2digits(tm.Hour) + ":" +
    print2digits(tm.Minute) + ":" +
    print2digits(tm.Second) + ", Date (D/M/Y) = " +
    tm.Day + '/' + tm.Month + '/' + tmYearToCalendar(tm.Year);
    Serial.println(currentDate);
  } else {
    if (RTC.chipPresent()) {
      Serial.println("The DS3132 is stopped.  Please run the SetTime");
      Serial.println("example to initialize the time and begin running.");
      Serial.println();
    } else {
      Serial.println("DS3132 read error!  Please check the circuitry.");
      Serial.println();
    }
    delay(9000);
  }
  delay(1000);*/

  //open the file for reading:
  myFile = SD.open("test.txt");
  if (myFile) {
    Serial.println("test.txt opened");

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      dateData = myFile.read();
      if(dateData.substring(0, 2).equals(print2digits(currentMins))){
        amPic = dateData.substring(3,5);
        pmPic = dateData.substring(6);
        break;
      }
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
  
  while(currentMins == tm.Minute){
    RTC.read(tm);
    if(print2digits(tm.Second).equals(amPic)){
      Serial.println("take amPic");
      break;
    }
  }
  while(currentMins == tm.Minute){
   RTC.read(tm);
   if(print2digits(tm.Second).equals(pmPic)){
     Serial.println("take pmPic");
     break;
     } 
  }

  currentMins = (currentMins + 1) % 60;
}



String print2digits(int number) {
  String digits = "";
  if (number >= 0 && number < 10) {
    digits += "0";
  }
  digits += String(number);
  return digits;
}

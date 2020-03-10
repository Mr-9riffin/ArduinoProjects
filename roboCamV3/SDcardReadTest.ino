/*
  SD card read/write

  This example shows how to read and write data to and from an SD card file
  The circuit:
   SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4 (for MKRZero SD: SDCARD_SS_PIN)

  created   Nov 2010
  by David A. Mellis
  modified 9 Apr 2012
  by Tom Igoe

  This example code is in the public domain.

*/

//#include <DS3232RTC.h>

#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>
#include <SPI.h>
//#include <SD.h>

#include "SdFat.h"
SdFat SD;

#define SD_CS_PIN SS

File myFile;
tmElements_t tm;
String output = "";
char data;

byte amHour;
byte amMin;
byte pmHour;
byte pmMin;
byte cHour;
byte cMin;
byte m;
byte d;
boolean timesFound = false;
byte currentDay  = 0;
boolean newDay = true;
boolean amPicTaken;
boolean pmPicTaken;
boolean noonPicTaken;
boolean DST;
const byte power = 8;
const byte shutter = 9;
const byte pResistor = A3;
int picNumber = 1;



void setup() {
  pinMode(pResistor, INPUT);
  pinMode(power, OUTPUT);
  pinMode(shutter, OUTPUT);

  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ;// wait for serial port to connect. Needed for native USB port only
  }

  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  DST = isItDST();
}

void loop() {
  initializeDate();
  if (newDay) {
    newDay = false;
    setPicTimes();
  }

  Serial.print(F("am, pm: "));
  Serial.println(String(amHour) + ":" + amMin + ", " + pmHour + ":" + pmMin);
  cHour = tm.Hour;
  cMin = tm.Minute;
  Serial.println(String(cHour) + ":" + cMin);
  delay(2000);
  if (cHour == amHour && cMin == amMin && !amPicTaken) {
    Serial.println(F("take AM"));
    takePic();
    amPicTaken = true;
  }
  if (cHour == (pmHour + amHour) / 2 && cMin == (amMin + pmMin) / 2 && !noonPicTaken) {
    Serial.println(F("take Noon"));
    takePic();
    noonPicTaken = true;
  }
  if (cHour == pmHour && cMin == pmMin && !pmPicTaken) {
    Serial.println(F("take PM"));
    takePic();
    pmPicTaken = true;
  }
}

// if a new day has come today is set to the new date
// pics taken and times found are reset to false
void initializeDate() {
  RTC.read(tm);
  d = tm.Day;
  //only initialize if a new day has come
  if (d != currentDay) {
    m = tm.Month;
    currentDay = d;
    Serial.print(F("Date: "));
    Serial.println(String(m) + "/" + d);
    newDay = true;
  }
}
// end of initializeDate

void setPicTimes() {
  // re-open the file for reading:
  myFile = SD.open("times2.txt");
  if (myFile) {
    // read from the file until there's nothing else in it:
    while (myFile.available() && !timesFound) {
      data = myFile.read();
      do {
        output += data;
        data = myFile.read();
      } while (data != '\n' && data != '\r');
      Serial.println(output);
      checkDate();
      output = "";
      data = myFile.read();
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println(F("error opening test.txt"));
  }
  amPicTaken = false;
  pmPicTaken = false;
  noonPicTaken = false;
}//end of read stuff

void checkDate() {
  if (output.substring(0, output.indexOf('/')).toInt() == m) {
    if (output.substring(output.indexOf('/') + 1, output.lastIndexOf('/')).toInt() == d) {
      amHour = output.substring(output.indexOf('\t') + 1, output.indexOf(':')).toInt();
      pmHour = output.substring(output.lastIndexOf('\t') + 1, output.lastIndexOf(':')).toInt();
      amMin = output.substring(output.indexOf(':') + 1, output.lastIndexOf('\t')).toInt();
      pmMin = output.substring(output.lastIndexOf(':') + 1).toInt();
      if (DST) {
        //amHour stays the same
        pmHour -= 2;
      } else {
        amHour += 1;
        pmHour -= 1;
      }
      timesFound = true; //stops the loop reading through the file
    }
  }
}

boolean isItDST() {

  // ********************* Calculate offset for Sunday *********************
  int y = tmYearToCalendar(tm.Year) - 2000;                          // DS3231 uses two digit year (required here)
  int x = (y + y / 4 + 2) % 7;    // remainder will identify which day of month
  // is Sunday by subtracting x from the one
  // or two week window.  First two weeks for March
  // and first week for November
  // *********** Test DST: BEGINS on 2nd Sunday of March @ 2:00 AM *********
  if (tm.Month == 3 && tm.Day >= (14 - x))
  {
    return true;                           // Daylight Savings Time is TRUE (add one hour)
  }
  if (tm.Month > 4 && tm.Month < 11)
  {
    return true;
  }
  // ************* Test DST: ENDS on 1st Sunday of Nov @ 2:00 AM ************
  if (tm.Month == 11 && tm.Day <= (7 - x))
  {
    return true;                            // daylight savings time is TRUE
  }
  return false;  //it is not DST

}//end of isItDST


void takePic() {
  //take the pic
  digitalWrite(power, HIGH);
  delay(10000);
  digitalWrite(shutter, HIGH);
  delay(500);
  digitalWrite(shutter, LOW);
  delay(10000);
  digitalWrite(power, LOW);

  //log the pic
  myFile = SD.open("data.txt", FILE_WRITE);
  if (myFile) {
    myFile.print(F("Pic: "));
    myFile.println(picNumber);
    picNumber++;
    myFile.print(m);
    myFile.print(F("/"));
    myFile.println(d);
    myFile.print(F("Photo Resistor Value: "));
    myFile.println(analogRead(pResistor));
    myFile.println("\n\n");
    // close the file:
    myFile.close();
    //Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening data.txt");
  }
}// end of takePic

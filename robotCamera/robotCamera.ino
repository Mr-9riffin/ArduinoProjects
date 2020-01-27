/*
  SD card read/write
 The circuit:
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4
 */

#include <SPI.h>
#include <SD.h>
#include  <virtuabotixRTC.h>

File myFile;
String photoLog = "photoLog.txt";
String dataLog = "dataLog.txt";
const int SDCS = 10; //SD card selelct

virtuabotixRTC myRTC(6, 7, 8);
const int morningPic = 10;
const int eveningPic = 4;
int morningTimeStamp = myRTC.dayofweek;
int eveningTimeStamp = myRTC.dayofweek;

const int pResistor = A0;
const int pRUpperThreshold = 500;
const int pRLowerThreshold = 400;
int pRvalue;
int pRTimeStamp = 0;
int pRInterval = 6;
//change for longer term test
int pRDataCollected = myRTC.minutes; //used to collect preliminary data for photoresistor
int dataInterval = 10;
int photoNumber = 0; //track how many myFile are taken


void setup() {
  Serial.begin(9600);
  pinMode(pResistor, INPUT);
  // 10 must be output or the SD library functions will not work. 
  //pinMode(10, OUTPUT);

  if (!SD.begin(SDCS)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
  myFile = SD.open(photoLog, FILE_WRITE);
  myFile.close();
  myFile = SD.open(dataLog, FILE_WRITE);
  myFile.close();

  // Set the current date, and time in the following format:
  //                  seconds, minutes, hours, day of the week, day of the month, month, year
  myRTC.setDS1302Time(00,      43,       14,     5,              3,                1,     2020);
  

}

void loop() {
  pRvalue = analogRead(pResistor);

  //Take a picture if the light level and time conditions are met
  if(pRvalue > pRLowerThreshold && pRvalue < pRUpperThreshold && myRTC.hours > (pRTimeStamp + pRInterval)%24)
  {
    pRTimeStamp = myRTC.hours;
    takePhoto(photoLog, "Photo resistor");
  }

  //prints the photoresistor value  to the SD on a fixed interval for calibration
  if(myRTC.minutes % 10 == 0 && myRTC.minutes != pRDataCollected)
  {
    pRDataCollected = myRTC.minutes;
    myFile = SD.open(dataLog);
    myFile.print(String("Time - ") +   
          myRTC.hours + ":" + myRTC.minutes + ":" + myRTC.seconds);
    myFile.println("Photo Resistor Value: " + pRvalue);
    myFile.close();
  }

//take morning picture at a set time each day
  if(myRTC.hours == morningPic && myRTC.dayofweek == morningTimeStamp) 
  {
    takePhoto(photoLog, "Morning pic, day: " + morningTimeStamp);
    
    morningTimeStamp++; //timeStamp is day of week from 0-6 (sunday-saturday)
    if(morningTimeStamp == 7) {
      morningTimeStamp = 0;
    }
  }

//take evening picture at a set time each day
  if(myRTC.hours == eveningPic && myRTC.dayofweek == eveningTimeStamp) 
  {
    takePhoto(photoLog, "evening pic, day: " + eveningTimeStamp);
    
    eveningTimeStamp++;
    if(eveningTimeStamp == 7) {
      eveningTimeStamp = 0;
    }
  }

} // end of loop



void takePhoto (String dataFile, String trigger) {
  myFile = SD.open(dataFile);
    if (myFile) {
      Serial.print("Writing to " + dataFile + "...");
      myFile.println("Photo " + photoNumber);
      photoNumber++;
      myFile.println(trigger + " activated at " +  
          myRTC.dayofmonth + "/" + myRTC.month + "/" + myRTC.year + " " + 
          myRTC.hours + ":" + myRTC.minutes + ":" + myRTC.seconds);
      if(trigger == "Photo resistor") {
        myFile.println("Photo Resistor Value: " + pRvalue); 
      }
      // close the file:
      myFile.close();
      Serial.println("done.");
    } else {
      // if the file didn't open, print an error:
        Serial.println("error opening" + dataFile);
    }
}// end of takePhoto

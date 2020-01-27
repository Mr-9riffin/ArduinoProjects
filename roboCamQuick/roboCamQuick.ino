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
String photoLog = "photoLogQuick.txt";
String dataLog = "dataLogQuick.txt";
const int SDCS = 10; //SD card selelct

virtuabotixRTC myRTC(6, 7, 8);
const int morningPic = 4;
const int eveningPic = 12;
int picsPerMinute = 4;
int picCounter = 0;
int morningTimeStamp = 0;
int eveningTimeStamp = 0;
int minuteCounter = myRTC.minutes;

const int pResistor = A0;
const int pRUpperThreshold = 500;
const int pRLowerThreshold = 400;
int pRvalue;
int pRTimeStamp = 0;
int pRInterval = 6;
//change for longer term test
int pRDataCollected = myRTC.seconds; //used to collect preliminary data for photoresistor
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
  // seconds, minutes, hours, day of the week, day of the month, month, year
  myRTC.setDS1302Time(00, 43, 14, 5, 26, 12, 2019);
  

}

void loop() {

  // This allows for the update of variables for time or accessing the individual elements.
  myRTC.updateTime();

  //Update the photo resistor
  pRvalue = analogRead(pResistor);

  //Take a picture if the light level and time conditions are met
  if(pRvalue > pRLowerThreshold && pRvalue < pRUpperThreshold && myRTC.hours > (pRTimeStamp + pRInterval)%60) 
  {
    pRTimeStamp = myRTC.seconds;
    takePhoto(photoLog, "Photo resistor");
  }

  //prints the photoresistor value  to the SD on a fixed interval for calibration
  if(myRTC.seconds % 10 == 0 && myRTC.seconds != pRDataCollected)
  {
    pRDataCollected = myRTC.seconds;
    myFile = SD.open(dataLog);
    myFile.println(String("Time") +   
          myRTC.hours + ":" + myRTC.minutes + ":" + myRTC.seconds);
    myFile.println("Photo Resistor Value: " + pRvalue);
    myFile.close();
  }

//take morning picture at a set time each day
  if(myRTC.seconds % 60.0/picsPerMinute > morningPic &&  picCounter == morningTimeStamp) 
  {
    takePhoto(photoLog, "Morning pic, day: " + morningTimeStamp);
    
    morningTimeStamp++; //timeStamp is day of week from 0-6 (sunday-saturday)
    if(morningTimeStamp == picsPerMinute) {
      morningTimeStamp = 0;
    }
  }

//take evening picture at a set time each day
  if(myRTC.seconds % 60.0/picsPerMinute > eveningPic && picCounter == eveningTimeStamp) 
  {
    takePhoto(photoLog, "evening pic, day: " + eveningTimeStamp);
    
    eveningTimeStamp++;
    if(eveningTimeStamp == picsPerMinute) {
      eveningTimeStamp = 0;
    }
  }

  if(myRTC.seconds > 60.0/picsPerMinute * picCounter + 1){
    picCounter++;
  }

  //
  if(myRTC.minutes > minuteCounter){
    minuteCounter = myRTC.minutes;
    picCounter = 0;
  }

} // end of loop



void takePhoto (String dataFile, String trigger) {
  myFile = SD.open(dataFile);
    if (myFile) {
      Serial.print(String("Photo ") + photoNumber + ": Writing " + trigger + " to " + dataFile + "...");
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

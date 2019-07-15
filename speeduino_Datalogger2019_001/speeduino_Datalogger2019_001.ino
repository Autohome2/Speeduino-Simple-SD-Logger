/*
Simple SD Logger - Simple SD card  Logger for use with the Speeduino open source ECU 
Copyright (C) Darren Siepka

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,la
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

Thanks and credit goes to any other contributors to this software.
**************************************************************************************************


 The circuit:
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4 

 This example code is in the public domain.

 */
#include <avr/pgmspace.h>
#include <SPI.h>
#include <SD.h>

const int chipSelect = 4;

#include <SoftwareSerial.h>

SoftwareSerial mySerial1(3, 2); // RX, TX
SoftwareSerial mySerial2(6, 5); // RX, TX

int k;    // counter variable
String myChar;
 byte Sreply ;
 byte Areply[40] ;
  String dataString = "";
 byte cmdAdata[40] ; 
 byte addata;
 byte packetlength;

const char header1[] PROGMEM  = {"Time SecL  Squirt  Engine  Dwell Map IATraw  CLTraw  tpsADC  BatteryV  afr egoCorrection airCorrection warmupEnrich  rpm  accelEnrich  baro gammaEnrich  veCurrent  afrTarget pulseWidth  TPSdot  advance tps  loopsPerSecond freeRAM batCorrection spark afr2 rpmDOT flex  flexFuelCor flexIgnCor  errors"};
const char header2[] PROGMEM  = {"sec bits  bits  ms  kpa V O2  % % % rpm % % % $ O2 ms  %/s deg % loops bytes % bits  O2  rpm/s % % deg bits"};

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  
  }
    // set the data rate for the SoftwareSerial port
  mySerial1.begin(115200);
//  mySerial1.println("Hello, world?");
  mySerial2.begin(115200);
//  mySerial2.println("Hello, world2?");
  
  mySerial1.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    mySerial1.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  mySerial1.println("card initialized.");


}

void loop() {
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("datalog.txt", FILE_WRITE);
    
 mySerial2.print("S");
  delay(100);
    dataString += char(34);
        while (mySerial2.available() == 0) { }
              for (unsigned int sig = 0; sig < 20 ; sig++)
                {
                Sreply = mySerial2.read();
                dataString += char((Sreply)); 
                }
        dataString += char(34);
        dataString += char(13);   // carriage return
        dataString += char(10);   // new line 
 
   // read back a char
//  int len = strlen_P(header1);
//  for (k = 0; k < len; k++)
//  {
//    myChar =  pgm_read_byte_near(header1);
//    dataFile.println(myChar);
//  }
//    myChar =  pgm_read_byte_near(header2);
//    dataFile.println(myChar);
        
    mySerial2.print("A");
    delay(100);
        while (mySerial2.available() == 0) { }
        cmdAdata[1] = mySerial2.read();    // read respnse from speeduino
        if (cmdAdata[1] == 65) //dec 65 == "A"
         {
          while (mySerial2.available() == 0) { }
          cmdAdata[2] = mySerial2.read();  // next byte from speeduino is the packet length
          packetlength = cmdAdata[2];
             while (mySerial2.available() == 0) { }
              for (uint8_t readA = 3; readA < (packetlength +3) ; readA++)
              {
              Areply[readA] = mySerial2.read();
              }
         }
// now build the string for the sd file
for (unsigned int readAback = 3; readAback < (packetlength +3) ; readAback++)
 {
 dataString += cmdAdata[readAback] ;
 }

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();

  }
  // if the file isn't open, pop up an error:
//  else {
//    Serial.println("error opening datalog.txt");
//  
    // print to the serial port too:
    mySerial1.println(dataString);
while( true ){
  //An empty loop that never ends.
}
}
//void printString(const prog_char str[]) {
//  char c;
//  if(!str) return;
//  while((c = pgm_read_byte(str++)))
//    dataFile.write(c);
//}









/***************************************************************************
This software is free provided that this notice is not removed and proper attribution is accorded to Layad
Circuits and its Author(s).
Layad Circuits invests resources in producing free software.
By purchasing Layad Circuits'products or utilizing its services, you support the continuing development of
free software for all.
Author(s): C.D.Malecdan for Layad Circuits Electronics Engineering
Revision: 1.0 - 2020/10/27 - initial creation
Layad Circuits Electronics Engineering Supplies and ServicesB314 Lopez Bldg., Session Rd. cor. Assumption
Rd., Baguio City, Philippines
www.layadcircuits.com
general: info@layadcircuits.com
sales: sales@layadcircuits.com
+63-916-442-8565
***************************************************************************/
#include <SoftwareSerial.h>
SoftwareSerial sethgun (10,11); // using pins 10 (To SethGun TX) and 11 (To SethGun RX) as software serial pins

String rawdata;  // This is the raw serial data. Expected format is as follows:
                 // @,xx.x,y,#\r\n where xx.x is the temperature in degrees Celsius while y is the type either 'B' for body or 'S' for surface
float temp;      // tempearture reading in Celsius

void setup() {
  Serial.begin(9600);
  sethgun.begin(9600);
  sethgun.setTimeout(100);
  pinMode(7,INPUT_PULLUP); // trigger button
}

void loop() {
  if(sethgun.available()) // pass through here as frequent as possible
  {
      rawdata = sethgun.readStringUntil('\n');  
      rawdata.remove(rawdata.lastIndexOf("@,"),2);
      temp = rawdata.toFloat();
      Serial.print("float = ");
      Serial.println(temp);
  }

  // Connect a normally open button at pin 7 and the other pin to ground.
  // When button is pressed, a reading is taken
  if(digitalRead(7) == LOW) 
  {
    delay(10);
    while(digitalRead(7) == LOW) {};
    sethgun.print("@,R,#\r\n"); // trigger the SethGun
  }
  
  //place your other code here
}

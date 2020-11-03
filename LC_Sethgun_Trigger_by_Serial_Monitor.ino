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
}

void loop() {
  if(sethgun.available()) // pass through here as frequent as possible
  {
      rawdata = sethgun.readStringUntil('\n');  
      rawdata.remove(rawdata.lastIndexOf("@,"),2);
      temp = rawdata.toFloat();
      Serial.print("Temperature = ");
      Serial.println(temp);
  }

  // When you type @,R,# into the Serial monitor with the "Both NL & CR" option enabled and click send, this triggers the SethGun to take a reading
  // A reading can also be triggered manually using the read button of the SethGun.
  if(Serial.available()) sethgun.write(Serial.read());
  
  //place your other code here
}

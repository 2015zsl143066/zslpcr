/*
 *  openpcr.pde - OpenPCR control software.
 *  Copyright (C) 2010-2012 Josh Perfetto. All Rights Reserved.
 *
 *  OpenPCR control software is free software: you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License as published
 *  by the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  OpenPCR control software is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along with
 *  the OpenPCR control software.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <LiquidCrystal.h>
#include <EEPROM.h>
#include <SoftwareSerial.h>
#include "pcr_includes.h"
#include "thermocycler.h"

SoftwareSerial mySerial(5, 6); // RX, TX

Thermocycler* gpThermocycler = NULL;

boolean InitialStart() {
  for (int i = 0; i < 50; i++) {
    if (EEPROM.read(i) != 0xFF)
      return false;
  }
  
  return true;
}

void setup() {
  //init factory settings
   // Open serial communications and wait for port to open:
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }



  // set the data rate for the SoftwareSerial port
  mySerial.begin(4800);
   //pinMode(7, OUTPUT);
  // digitalWrite(7, HIGH); 
  if (InitialStart()) {
    EEPROM.write(0, 100); // set contrast to 100
  }
  
  //restart detection
  boolean restarted = !(MCUSR & 1);
  MCUSR &= 0xFE;
    
  gpThermocycler = new Thermocycler(restarted);
}

void loop() {
    Serial.write("hello zsl! ");
     delay(500);
  //digitalWrite(7, HIGH); 
  //digitalWrite(8, HIGH);   // turn the LED on (HIGH is the voltage level)
  gpThermocycler->Loop();
  
}


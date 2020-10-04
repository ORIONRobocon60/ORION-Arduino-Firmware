/***************************************************************************
  This is a library for the CCS811 air

  This sketch reads the sensor

  Designed specifically to work with the Adafruit CCS811 breakout
  ----> http://www.adafruit.com/products/3566

  These sensors use I2C to communicate. The device's I2C address is 0x5A

  Adafruit invests time and resources providing this open source code,
  please support Adafruit andopen-source hardware by purchasing products
  from Adafruit!

  Written by Dean Miller for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ***************************************************************************/

#include "Adafruit_CCS811.h"
#if defined(__AVR_ATmega328P__)
#include <SoftwareSerial.h>

SoftwareSerial Serial1(0,1); //(RX, TX)
#endif

#define COMMS_PIN 5

Adafruit_CCS811 ccs;
int temperature = 0;

void setup() {

 
  
 pinMode(COMMS_PIN,OUTPUT);
 digitalWrite(COMMS_PIN,LOW);
  
 Serial.begin(9600);

 while(!Serial);
 Serial.println("READY");

 Serial.println("CCS811 test");

 if(!ccs.begin()){
 Serial.println("Failed to start sensor! Please check your wiring.");
 while(1);
 }
 //calibrate temperature sensor
 while(!ccs.available());
 float temp = ccs.calculateTemperature();
 ccs.setTempOffset(temp - 25.0);
}


void loop() 
{
  while(Serial.available()){
    uint8_t t = Serial.read();
    //Serial1.write('\n');
    Serial1.write(t);
  }

  while(Serial1.available()){
    uint8_t r = Serial1.read();
    //Serial1.write('\n');
    Serial.write(r);
    
  }
  
 if(ccs.available()){
 float temp = ccs.calculateTemperature();
 if(!ccs.readData()){
 //Serial.print("CO2: ");
 Serial.print(ccs.geteCO2());
 //Serial.print("ppm, TVOC: ");
 Serial.print(",");
 Serial.print(ccs.getTVOC());
 //Serial.print("ppb Temp:");
 Serial.print(",");
 Serial.println(temp);
 }
 else{
 Serial.println("ERROR!");
 while(1);
 }
 }
 delay(500);
}

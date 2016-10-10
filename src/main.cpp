#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <FooLib.h>
#include <RGBLED.h>
#include <SensorTest.h>


#define S_CONF 0
#define S_WORK 1

//pull up to enter conf state
#define confStatePin 3

int state;

unsigned long ts;  // To store the "current" time in for delays.

void setup() {
  Serial.begin(9600);

  ts = millis();

  //init conf state pin
  pinMode(confStatePin,INPUT);


  if(digitalRead(confStatePin) == LOW){//enter conf mode
    (RGBLED()).lightOn(0,0,255);
    state = S_CONF;
  }else{
    state = S_WORK;
  }

}

void loop() {
  switch(state)
  {
    case S_CONF:
      //enter config mode
      (RGBLED()).lightOn(0,0,255);
      break;
    case S_WORK:
      (RGBLED()).lightOn(255,0,0);
      //normal working state
      break;
    default:
      state = S_WORK;
      break;
  }
}

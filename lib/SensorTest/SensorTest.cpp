#include <Arduino.h>
#include "SensorTest.h"
#include "RGBLED.h"

#define infraredSensorPin 9

void SensorTest::test(){
  pinMode(infraredSensorPin, INPUT);

  int triggered = digitalRead(infraredSensorPin);
  // Serial.println(triggered);
  // delay(100);

  if(triggered == 1){
    (RGBLED()).lightOn(0,255,255);
  }else{
    (RGBLED()).lightOff();
  }
}

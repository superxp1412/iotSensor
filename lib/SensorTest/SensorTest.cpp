#include <Arduino.h>
#include "SensorTest.h"
#include "RGBLED.h"

#define infraredSensorPin 9

String SensorTest::test(){
  pinMode(infraredSensorPin, INPUT);

  int triggered = digitalRead(infraredSensorPin);
  // Serial.println(triggered);

  if(triggered == 1){
    // (RGBLED()).lightOn(0,255,255);
    return SENSOR_STATUS_BUSY;
  }else{
    // (RGBLED()).lightOff();
    return SENSOR_STATUS_FREE;
  }
}

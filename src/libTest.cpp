#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <FooLib.h>
#include <RGBLED.h>
#include <SensorTest.h>

#define S_IDLE 0
#define S_LED_ON 1
#define S_LED_OFF 2
#define S_END 3

int state;
unsigned long initTime;
unsigned long ts;  // To store the "current" time in for delays.

void setup() {
  Serial.begin(9600);
  state = S_LED_OFF;
  initTime = millis();//initial time

  // delay(3000);
  Serial.println(millis());
  // delay(1000);
  Serial.println(millis());
  ts = millis();
}

void loop() {
  
}

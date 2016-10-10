#include <Arduino.h>
#include "RGBLED.h"

#define redPin 5
#define greenPin 4
#define bluePin 0
#define powerPin 2

//light on the LED & set a color
void RGBLED::lightOn(int red, int green, int blue)
{
  pinMode(powerPin, OUTPUT);
  digitalWrite(powerPin, HIGH);

  analogWrite(redPin,constrain(red,0,255));
  analogWrite(greenPin,constrain(green,0,255));
  analogWrite(bluePin,constrain(blue,0,255));
}

void RGBLED::lightOff(){
  pinMode(powerPin, OUTPUT);
  digitalWrite(powerPin, LOW);
}

//should invoke this function before switch to another color
void RGBLED::reset(){
  pinMode(redPin, INPUT);
  pinMode(greenPin, INPUT);
  pinMode(bluePin, INPUT);
}

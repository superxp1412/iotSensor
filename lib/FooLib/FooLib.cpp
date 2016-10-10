#include "FooLib.h"
#include <Arduino.h>

int FooLib::showNum()
{
    Serial.println("inside");
		return 123;
}

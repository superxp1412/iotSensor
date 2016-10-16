#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FooLib.h>
#include <RGBLED.h>
#include <SensorTest.h>
#include <EEPROM.h>

#include <WifiConfig.h>


#define S_CONF 0
#define S_WORK 1

//pull up to enter conf state
#define confStatePin 3

int state;

unsigned long ts;  // To store the "current" time in for delays.

WifiConfig wifiConfig;

void setup()
{
	Serial.begin(9600);

	WiFi.mode(WIFI_STA);
	// uncomment the following if you set a static IP in the begining
	//WiFi.config(nkip, nkgateway, nksubnet);

	// WifiConfig wifiConfig;

	// call espWiFi2eeprom to connect to saved to eeprom AP or
	// to create an AP to store new values for SSID and password
	wifiConfig.espNKWiFiconnect();
	//--
  delay(1000);
	Serial.print("IP address: ");
	Serial.println(WiFi.localIP());

  wifiConfig.init();
}

int stateNum = 0;

void loop()
{
  wifiConfig.server.handleClient();
  (RGBLED()).lightOn(0,255,0);
}

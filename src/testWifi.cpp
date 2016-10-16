#include <Arduino.h>
#include <WiFiClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FooLib.h>
#include <RGBLED.h>
#include <SensorTest.h>
#include <EEPROM.h>

#include <WifiConfig.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

#include <WString.h>


#define S_CONF 0
#define S_WORK 1

//pull up to enter conf state
#define confStatePin 3

int state;

unsigned long ts;  // To store the "current" time in for delays.

WifiConfig wifiConfig;

int stateNum = 0;

ESP8266WiFiMulti WiFiMulti;
HTTPClient http;

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

	//test
	if (WiFi.status() == WL_CONNECTED) {
		Serial.println("test wifi:");
		Serial.println(wifiConfig.printConnectionType(WiFi.status()));
	}
}

void loop()
{
	wifiConfig.server.handleClient();
	(RGBLED()).lightOn(0, 255, 0);

  //http request
	http.begin("http://192.168.99.130:8080/api");
	//http.begin("192.168.1.12", 80, "/test.html");

	int httpCode = http.POST("WiFi.localIP:" + WiFi.localIP().toString());
	if (httpCode > 0) {
		Serial.printf("[HTTP] GET... code: %d\n", httpCode);
    Serial.println();

		// file found at server
		if (httpCode == HTTP_CODE_OK)
			http.writeToStream(&Serial);
      Serial.println();
	} else {
		Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
	}

	http.end();

  delay(1000);
}

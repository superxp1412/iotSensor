#include <Arduino.h>
#include <WiFiClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
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
	// init serial port
	Serial.begin(9600);

	// uncomment the following if you set a static IP in the begining
	// WiFi.config(nkip, nkgateway, nksubnet);

	// call espWiFi2eeprom to connect to saved to eeprom AP or to create an AP to store new values for SSID and password
	wifiConfig.espNKWiFiconnect();

	// show IP address
	Serial.print("IP address: ");
	Serial.println(WiFi.localIP());

	// init basic web server for basic functions: info, restart, cleareeprom
	wifiConfig.initBasicHttpServer();
}

void loop()
{
	wifiConfig.server.handleClient();
	delay(1000);
}

void sendRequest(){
	//http request
	http.begin("http://192.168.99.130:8080/api");
	//http.begin("192.168.1.12", 80, "/test.html");

	int httpCode = http.POST("WiFi.localIP:" + WiFi.localIP().toString());
	if (httpCode > 0) {
		Serial.printf("[HTTP] GET... code: %d\n", httpCode);
		Serial.println();

		if (httpCode == HTTP_CODE_OK)
			http.writeToStream(&Serial);
		Serial.println();
	} else {
		Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
	}

	http.end();
}

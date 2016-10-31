#include <Arduino.h>
#include <WiFiClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <WString.h>
#include <EEPROM.h>
#include <WifiConfig.h>
#include <RGBLED.h>
#include <SensorTest.h>

#define S_CONFIG 0
#define S_CONNECTED 1
#define REQUEST_INTERVAL 2000

WifiConfig wifiConfig;
HTTPClient http;

int state;
unsigned long ts;  // To store the "current" time in for delays.

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

	if (WIFI_STA == WiFi.getMode()) {
		state = S_CONNECTED;    //in normal working mode
	} else {
		state = S_CONFIG;       // in config mode
		WiFi.config(IPAddress(192, 168, 1, 1), IPAddress(192, 168, 1, 1), IPAddress(255, 255, 255, 0));
	}

	if (state == S_CONFIG){
		(RGBLED()).lightOn(255, 0, 0);
	} else if (state == S_CONNECTED){
		(RGBLED()).lightOn(0, 255, 0);
	}

	delay(3000);

	(RGBLED()).lightOff();
}

void sendRequest(String sensorStatus, String roomName, String reportUrl)
{
	//http request
	http.begin(reportUrl + "/sensor?roomName=" + roomName +"&status=" + sensorStatus);
	// http.begin("http://192.168.99.130:8080/hello-world");
	//http.begin("192.168.1.12", 80, "/test.html");

	// int httpCode = http.POST("WiFi.localIP:" + WiFi.localIP().toString());
	int httpCode = http.POST("");

	if (httpCode > 0) {
		Serial.printf("[HTTP] POST... code: %d\n", httpCode);
		Serial.println();

		if (httpCode == HTTP_CODE_OK)
			http.writeToStream(&Serial);
		Serial.println();
	} else {
		Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
	}

	http.end();
}

void loop()
{
	wifiConfig.server.handleClient();

	if((state == S_CONNECTED) && (millis() > ts + REQUEST_INTERVAL)) {

		String sensorStatus = (SensorTest()).test();
		if(sensorStatus == SENSOR_STATUS_BUSY){
	    (RGBLED()).lightOn(0,255,255);
			Serial.println("sensor shows Busy####");
	  }else{
	    (RGBLED()).lightOff();
			Serial.println("sensor shows free~~~~~");
	  }
		Serial.println(wifiConfig.reportUrl);
		Serial.println(wifiConfig.roomName);
		sendRequest(sensorStatus,wifiConfig.roomName,wifiConfig.reportUrl);

		ts = millis();//reset timer
	}
}

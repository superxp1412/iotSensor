#ifndef WifiConfig_H
#define WifiConfig_H

#include <ESP8266WebServer.h>
#include <WString.h>
#define AP_RESTART "esprestart"
#define AP_CLEAREEPROM "cleareeprom"
#define AP_WIFICFGPORT 80
#define ESPWIFI2EEPROM_VERSION "0.4"
// password for the esp8266 softAP creates when it doesn't find info in the
// eeprom
// or when something else goes wrong and can't connect
const char AP_password[] = "esp8266control";

// void handle_root();

class WifiConfig {
public:
	WifiConfig();
	void init();

	ESP8266WebServer server;
	ESP8266WebServer APserver;

	void espNKWiFiconnect();

	bool testWiFi();
	String printConnectionType(int thisType);

	void setupWiFiAP();
	void getAPlist();
	String printEncryptionType(int thisType);

	void handle_root();
	
	//AP web server handlers
	void handle_AProot();
	void handle_APsubmit();
	void handle_APrestart();
	void handle_clearAPeeprom();
};
#endif

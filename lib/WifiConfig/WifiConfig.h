#ifndef WifiConfig_H
#define WifiConfig_H

#include <WString.h>
#define AP_RESTART "esprestart"
#define AP_CLEAREEPROM "cleareeprom"
#define AP_WIFICFGPORT 8266
#define ESPWIFI2EEPROM_VERSION "0.4"
// password for the esp8266 softAP creates when it doesn't find info in the
// eeprom
// or when something else goes wrong and can't connect
const char AP_password[] = "esp8266control";

void handle_root();

class WifiConfig {
public:
	WifiConfig();
	void espNKWiFiconnect();

private:
	String printConnectionType(int thisType);
	bool testWiFi();
	void setupWiFiAP();
	// void handle_clearAPeeprom();

	// void getAPlist();

	// String printEncryptionType(int thisType);
};
#endif

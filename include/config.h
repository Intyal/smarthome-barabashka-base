// Библиотека для работы с JSON
#include <ArduinoJson.h>

#include <avr/pgmspace.h>

struct config_wifi_t
{
	char ssid[32];
	char password[64];
};

class Config {
	StaticJsonDocument<8192> _cfg;
public:
	bool loadConfig ();
	bool saveConfig();
	void defaultConfig();
	void printConfig();
	String param(String key);

	static const char FILE_NAME[] PROGMEM;
protected:
	//const char *_file_name = "/config.json";
	config_wifi_t _wifi;
};

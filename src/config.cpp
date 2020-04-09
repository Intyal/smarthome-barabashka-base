#include "config.h"
#include <avr/pgmspace.h>
// Библиотека для работы с файловой системой
#include <FS.h>
// Библиотека для работы с JSON
#include <ArduinoJson.h>
// Библиотека для работы с SPIFFS по FTP
//#include <ESP8266FtpServer.h>

const char Config::FILE_NAME[] PROGMEM = "/config.json";

// Загрузка настроек устройства из файла 
bool Config::loadConfig () {
	char fileName[sizeof(FILE_NAME)];
	strcpy_P(fileName, FILE_NAME);
	// Открываем файл для чтения
	Serial.println(fileName);
	SPIFFS.begin();
	File file = SPIFFS.open("/config.json", "r");
	if (!file) {
		Serial.println("Failed to open file");
		return false;
	} 
	// Разбор JSON файла

	//StaticJsonDocument<512> doc; // Используйте arduinojson.org/v6/assistant для расчета объема.
	DeserializationError error = deserializeJson(_cfg, file);
	if (error) {
		Serial.println("Failed to deserializeJson file");
		file.close();
		return false;
	}

	// Копирование значений из JSON в Config
	//_wifi.ssid = doc["wifi"]["ssid"];
	//_wifi.password = doc["wifi"]["password"];
	strcpy_P(_wifi.ssid, _cfg["wifi"]["ssid"] | "");
	strcpy_P(_wifi.password, _cfg["wifi"]["password"] | "");
	//strlcpy(_wifi.ssid, doc["wifi"]["ssid"] | "barabashka_1", sizeof(_wifi.ssid));
	//strlcpy(_wifi.password, doc["wifi"]["password"] | "password", sizeof(_wifi.password));

	// Закрываем фаил
	file.close();
	return true;
};

bool Config::saveConfig() {
	char fileName[sizeof(FILE_NAME)];
	strcpy_P(fileName, FILE_NAME);
	// Открытие файла для записи
	File file = SPIFFS.open(fileName, "w");
	if (!file) {
		Serial.println("Failed to create file");
		Serial.println(fileName);
		return false;
	}

	//StaticJsonDocument<512> doc; // Используйте arduinojson.org/v6/assistant для расчета объема.

	// Передаем значение в переменные
	_cfg["wifi"]["ssid"] = _wifi.ssid;
	_cfg["wifi"]["password"] = _wifi.password;

	// Собираем JSON фаил
	if (serializeJsonPretty(_cfg, file) == 0) {
		Serial.println("Failed to write to file");
		file.close();
		return false;
	}

	// Закрываем фаил
	file.close();
	return true;
};

void Config::defaultConfig() {
	//_wifi.ssid = "default";
	//_wifi.password = "default";
};

void Config::printConfig() {
	Serial.print("SSID: ");
	Serial.println(_wifi.ssid);
	Serial.print("PASS: ");
	Serial.println(_wifi.password);
};

String Config::param(String key) 
{ 
	String value = _cfg[key];
	return value;
} 
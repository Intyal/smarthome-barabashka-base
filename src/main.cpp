#include <Arduino.h>
#include <config.h>

#include <ESP8266WiFi.h>

Config config;

void setup() {
	Serial.begin(115200);
	Serial.println();

	//config.defaultConfig();
	//config.saveConfig();
	//config.loadConfig();
	config.printConfig();

	Serial.printf("Wi-Fi mode set to WIFI_STA %s\n", WiFi.mode(WIFI_STA) ? "" : "Failed!");
	Serial.print("Begin WPS (press WPS button on your router) ... ");
	Serial.println(WiFi.beginWPSConfig() ? "Success" : "Failed");

	while (WiFi.status() != WL_CONNECTED)
	{
		delay(500);
		Serial.print(".");
	}
	Serial.println();
	Serial.print("Connected, IP address: ");
	Serial.println(WiFi.localIP());
	Serial.println(WiFi.SSID());
	Serial.println(WiFi.macAddress());
	Serial.println(WiFi.psk());

	config.saveConfig();

}

void loop() {

}
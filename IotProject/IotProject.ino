/*
 Name:		IotProject.ino
 Created:	2/28/2020 3:44:53 PM
 Author:	O.Ketabchi
*/

#include <ESP8266WiFi.h>
#include <Esp8266WebServer.h>
#include <WS2812FX.h>
#include "LedStrip.h"


#define LED_BUILT_IN 2

ESP8266WebServer server(80);
//Adafruit_NeoPixel pixels = Adafruit_NeoPixel(180, D1, NEO_GRB + NEO_KHZ800);
LedStrip ledStrip(60, D1);

// the setup function runs once when you press reset or power the board
void setup() {
	char ssid[32 + 1] = "Target1";
	char password[64 + 1] = "14125518588";

	pinMode(LED_BUILT_IN, OUTPUT);



	//pixels.begin();
	Serial.begin(115200);

	WiFi.disconnect();
	WiFi.begin(ssid, password);

	while (WiFi.status() != WL_CONNECTED)
	{
		Serial.print(".");

		digitalWrite(LED_BUILT_IN, LOW);
		delay(100);
		digitalWrite(LED_BUILT_IN, HIGH);
		delay(100);
	}

	Serial.println();
	Serial.println("connected");
	Serial.printf("Local IP:%s\n", WiFi.localIP().toString().c_str());
	Serial.printf("Gateway IP:%s\n", WiFi.gatewayIP().toString().c_str());
	Serial.printf("SubnetMask IP:%s\n", WiFi.subnetMask().toString().c_str());
	Serial.printf("PSK:%s\n", WiFi.psk().c_str());
	Serial.printf("macAddress:%s\n", WiFi.macAddress().c_str());

	server.begin();
	server.on("/lightBubble", manageLightBulb);
	server.on("/ledStrip", manageLedStrip);
}

// the loop function runs over and over again until power down or reset
void loop() {

	server.handleClient();

	ledStrip.startEffectMode();
} 

void manageLightBulb()
{
	//Serial.println(server.args());

	if (server.hasArg("status"))
	{
		//Serial.println("hasArg");
		int count = server.args();

		if (count != 1)
		{
			//Serial.println("count != 1");
			server.send(400, "text/plain", "inavalid parameter bulb");
		}
		else
		{
			//Serial.println("else");
			for (uint8 i = 0; i < count; i++)
			{
				server.argName(i);
				server.arg(i);

				if (server.argName(i) == "status")
				{
					//Serial.println("==");
					digitalWrite(LED_BUILT_IN, (server.arg(i).toInt() == 0) ? HIGH : LOW);
					server.send(200, "text/plain", "valid parameter bulb");
				}
			}
		}
	}
} 

void manageLedStrip()
{
	uint8 red = 0;
	uint8 green = 0;
	uint8 blue = 0;
	uint8 effect = 0;
	uint8 brightness;
	uint8 speed;
	uint8 effectMode;
	char buffer[100] = { 0 };
	bool moreEffect = false;

	//http://192.168.43.203/ledStrip?red=216&green=24&blue=36&effect=6&speed=197&brightness=59
	Serial.println("manageLedStrip");

	//ledStrip.stopEffectMode();

	if (server.hasArg("red") &&
		server.hasArg("green") &&
		server.hasArg("blue") &&
		server.hasArg("effect") &&
		server.hasArg("speed") &&
		server.hasArg("brightness"))
	{
		red = server.arg("red").toInt();
		green = server.arg("green").toInt();
		blue = server.arg("blue").toInt();
		brightness = server.arg("brightness").toInt();
		speed = server.arg("speed").toInt();
		effectMode = server.arg("effect").toInt();

		uint8 count = server.args();

		if (count != 6)
		{
			Serial.println("count != 6");
			server.send(400, "text/plain", "inavalid parameter led");
		}
		else
		{
			Serial.println("manageLedStrip else");

			sprintf(buffer, "%d,%d,%d-%d,%d", red, green, blue, speed, brightness);
			server.send(200, "text/plain", buffer);

			ledStrip.manageLeds(red, green, blue); 
			ledStrip.manageLedEffecs(red, green, blue, brightness, speed, effectMode);
		}
		 
	}
	delay(100);
}


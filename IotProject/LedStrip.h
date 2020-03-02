#ifndef LED_STRIP_H
#define LED_STRIP_H

#include <Adafruit_NeoPixel.h>
#include <WS2812FX.h>

class LedStrip {

public:
	LedStrip(uint8 numberOfLed, uint8 pin);
	void manageLeds(uint8 red, uint8 green, uint8 blue);
	void setLedAndpin(uint8 numberOfLed, uint8 pin);
	void manageLedEffecs(uint8 red, uint8 green, uint8 blue, uint8 brightness, uint8 speed, uint8 mode);
	void stopEffectMode();
	void startEffectMode();
private:
	//uint8 red;
	//uint8 green;
	//uint8 blue;
	//uint8 brightness;
	//uint8 speed;
	uint8 numberOfLed;
	uint8 pin;
	Adafruit_NeoPixel pixels;
	WS2812FX ws2812fx;


	void intiLed();
};






#endif //LED_STRIP_H
#pragma once

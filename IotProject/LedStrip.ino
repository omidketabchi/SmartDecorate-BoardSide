#include <Adafruit_NeoPixel.h>
#include "LedStrip.h"

LedStrip::LedStrip(uint8 numberOfLed, uint8 pin) :ws2812fx(numberOfLed, pin, NEO_GRB + NEO_KHZ800)
{
	setLedAndpin(numberOfLed, pin);

	intiLed();
}

void LedStrip::intiLed()
{
	pixels = Adafruit_NeoPixel(numberOfLed, pin, NEO_GRB + NEO_KHZ800);

	pixels.begin();
}

void LedStrip::manageLeds(uint8 red, uint8 green, uint8 blue)
{
	for (uint8 i = 0; i < numberOfLed; i++)
	{
		pixels.setPixelColor(i, pixels.Color(red, green, blue));

		pixels.show();

		delay(50);
	}
}

void LedStrip::setLedAndpin(uint8 numberOfLed, uint8 pin)
{
	this->pin = pin;
	this->numberOfLed = numberOfLed;
}

void LedStrip::manageLedEffecs(uint8 red, uint8 green, uint8 blue, uint8 brightness, uint8 speed, uint8 mode)
{
	ws2812fx.setBrightness(brightness);
	ws2812fx.setSpeed(speed);
	ws2812fx.setColor(red, green, blue);
	ws2812fx.setMode(mode);
	ws2812fx.start();
}

void LedStrip::stopEffectMode()
{
	ws2812fx.stop();
}

void LedStrip::startEffectMode()
{
	ws2812fx.service();
}
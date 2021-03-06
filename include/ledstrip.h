#pragma once
#include <FastLED.h>

#define NUM_LEDS    50
#define BRIGHTNESS  64
#define LEDS_PIN     5
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define UPDATES_PER_SECOND 100
#define KRUTILKA A0

const TProgmemRGBPalette16 Black_p FL_PROGMEM =
{
    CRGB::Black,
    CRGB::Black,
    CRGB::Black,
    CRGB::Black,

    CRGB::Black,
    CRGB::Black,
    CRGB::Black,

    CRGB::Black,
    CRGB::Black,
    CRGB::Black,
    CRGB::Black,

    CRGB::Black,
    CRGB::Black,
    CRGB::Black,
    CRGB::Black
};

extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;

class LedStrip
{
    public:
    LedStrip();
    
    void FillLEDsFromPaletteColors(uint8_t colorIndex);
    void SetupTotallyRandomPalette();
    void SetupBlackAndWhiteStripedPalette();
    void SetupPurpleAndGreenPalette();
    void ChangePaletteRandom();
    void ChangePaletteOneByOne();
    void run();
    CRGBPalette16 currentPalette;

    private:
    CRGB strip_leds[NUM_LEDS];
    TBlendType    currentBlending;
    int brightness, prev_brightness = BRIGHTNESS;
};
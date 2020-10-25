#include <FastLED.h>

#define NUM_LEDS    50
#define BRIGHTNESS  64
#define LEDS_PIN     5
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define UPDATES_PER_SECOND 100
#define KRUTILKA A0



extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;

class LedStrip
{
    public:
    LedStrip()
    {
        FastLED.addLeds<LED_TYPE, LEDS_PIN, COLOR_ORDER>(strip_leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
        FastLED.setBrightness(BRIGHTNESS);
        
        currentPalette = RainbowColors_p;
        currentBlending = LINEARBLEND;
        
        ChangePaletteRandom();
    }
    void FillLEDsFromPaletteColors(uint8_t colorIndex);
    void SetupTotallyRandomPalette();
    void SetupBlackAndWhiteStripedPalette();
    void SetupPurpleAndGreenPalette();
    void ChangePaletteRandom();
    void ChangePaletteOneByOne();
    void run();

    private:
    CRGB strip_leds[NUM_LEDS];
    CRGBPalette16 currentPalette;
    TBlendType    currentBlending;
    int actual_brightness = BRIGHTNESS;
    int saved_brightness = 0;
};
#include "ledstrip.h"
#include "toilet.h"

extern Toilet toilet;

LedStrip::LedStrip()
{
    FastLED.addLeds<LED_TYPE, LEDS_PIN, COLOR_ORDER>(strip_leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(BRIGHTNESS);
    
    ChangePaletteRandom();
}

void LedStrip::FillLEDsFromPaletteColors(uint8_t colorIndex)
{
    uint8_t brightness = 255;
    
    for( int i = 0; i < NUM_LEDS; i++) {
        strip_leds[i] = ColorFromPalette(currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
}

void LedStrip::SetupTotallyRandomPalette()
{
    for( int i = 0; i < 16; i++) {
        currentPalette[i] = CHSV( random8(), 255, random8());
    }
}

void LedStrip::SetupBlackAndWhiteStripedPalette()
{
    // 'black out' all 16 palette entries...
    fill_solid(currentPalette, 16, CRGB::Black);
    // and set every fourth one to white.
    strip_leds[0] = CRGB::White;
    strip_leds[4] = CRGB::White;
    strip_leds[8] = CRGB::White;
    strip_leds[12] = CRGB::White; 
}

// This function sets up a palette of purple and green stripes.
void LedStrip::SetupPurpleAndGreenPalette()
{
    CRGB purple = CHSV( HUE_PURPLE, 255, 255);
    CRGB green  = CHSV( HUE_GREEN, 255, 255);
    CRGB black  = CRGB::Black;
    
    currentPalette = CRGBPalette16(
                                   green,  green,  black,  black,
                                   purple, purple, black,  black,
                                   green,  green,  black,  black,
                                   purple, purple, black,  black );
}


// This example shows how to set up a static color palette
// which is stored in PROGMEM (flash), which is almost always more
// plentiful than RAM.  A static PROGMEM palette like this
// takes up 64 bytes of flash.
const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM =
{
    CRGB::Red,
    CRGB::Gray, // 'white' is too bright compared to red and blue
    CRGB::Blue,
    CRGB::Black,
    
    CRGB::Red,
    CRGB::Gray,
    CRGB::Blue,
    CRGB::Black,
    
    CRGB::Red,
    CRGB::Red,
    CRGB::Gray,
    CRGB::Gray,
    CRGB::Blue,
    CRGB::Blue,
    CRGB::Black,
    CRGB::Black
};

void LedStrip::ChangePaletteRandom()
{
uint8_t random_palette = random(11);
    
        if( random_palette == 0)  { currentPalette = myRedWhiteBluePalette_p; currentBlending = LINEARBLEND;  }
        if( random_palette == 1)  { currentPalette = RainbowColors_p;         currentBlending = LINEARBLEND; }
        if( random_palette == 2)  { currentPalette = RainbowStripeColors_p;   currentBlending = NOBLEND;  }
        if( random_palette == 3)  { currentPalette = RainbowStripeColors_p;   currentBlending = LINEARBLEND; }
        if( random_palette == 4)  { SetupPurpleAndGreenPalette();             currentBlending = LINEARBLEND; }
        if( random_palette == 5)  { SetupTotallyRandomPalette();              currentBlending = LINEARBLEND; }
        if( random_palette == 6)  { SetupBlackAndWhiteStripedPalette();       currentBlending = NOBLEND; }
        if( random_palette == 7)  { SetupBlackAndWhiteStripedPalette();       currentBlending = LINEARBLEND; }
        if( random_palette == 8)  { currentPalette = CloudColors_p;           currentBlending = LINEARBLEND; }
        if( random_palette == 9)  { currentPalette = PartyColors_p;           currentBlending = LINEARBLEND; }
        if( random_palette == 10)  { currentPalette = myRedWhiteBluePalette_p; currentBlending = NOBLEND;  }
        if( random_palette == 11)  { currentPalette = myRedWhiteBluePalette_p; currentBlending = LINEARBLEND; }
        Serial.print(F("Random palette number "));
        Serial.println(random_palette);
}

void LedStrip::ChangePaletteOneByOne()
{
        static uint8_t secondHand = 0;
        if (secondHand == 0) {currentPalette = RainbowColors_p;         currentBlending = LINEARBLEND;}
        if (secondHand == 1) {currentPalette = myRedWhiteBluePalette_p; currentBlending = LINEARBLEND;}
        if (secondHand == 2) {currentPalette = RainbowStripeColors_p;   currentBlending = NOBLEND;}
        if (secondHand == 3) {currentPalette = RainbowStripeColors_p;   currentBlending = LINEARBLEND;}
        if (secondHand == 4) {SetupPurpleAndGreenPalette();             currentBlending = LINEARBLEND;}
        if (secondHand == 5) {SetupTotallyRandomPalette();              currentBlending = LINEARBLEND;}
        if (secondHand == 6) {SetupBlackAndWhiteStripedPalette();       currentBlending = NOBLEND;}
        if (secondHand == 7) {SetupBlackAndWhiteStripedPalette();       currentBlending = LINEARBLEND;}
        if (secondHand == 8) {currentPalette = CloudColors_p;           currentBlending = LINEARBLEND;}
        if (secondHand == 9) {currentPalette = PartyColors_p;           currentBlending = LINEARBLEND;}
        if (secondHand == 10) {currentPalette = myRedWhiteBluePalette_p; currentBlending = NOBLEND;}
        if (secondHand == 11) {currentPalette = LavaColors_p; currentBlending = LINEARBLEND;}
        if (secondHand == 12) {currentPalette = OceanColors_p; currentBlending = LINEARBLEND;}
        if (secondHand == 13) {currentPalette = ForestColors_p; currentBlending = LINEARBLEND;}
        if (secondHand == 14) {currentPalette = HeatColors_p; currentBlending = LINEARBLEND;}
        if (secondHand == 15) {currentPalette = LavaColors_p; currentBlending = NOBLEND;}
        if (secondHand == 16) {currentPalette = ForestColors_p; currentBlending = NOBLEND;}
        if (secondHand == 17) {currentPalette = Black_p; currentBlending = LINEARBLEND;}
        Serial.print(F("Set palette number "));
        Serial.println(secondHand);
        secondHand++;
        if (secondHand == 18) {secondHand = 0;}
}

void LedStrip::run()
{
    static uint8_t startIndex = 0;
    startIndex = startIndex + 1; /* motion speed */
    FillLEDsFromPaletteColors(startIndex);
    brightness = map(analogRead(KRUTILKA), 0, 1023, 0, 255);
    if (abs(brightness - prev_brightness) > 20)
    {
        toilet.set_sleep(false);
        toilet.update_enter_led();
        prev_brightness = brightness;
        toilet.somebody_inside_toilet = true;
    }
    FastLED.setBrightness(brightness);
    FastLED.show();
    FastLED.delay(1000/UPDATES_PER_SECOND);
}
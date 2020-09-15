
// ARC REACTOR
// Ryan Appel

#include <FastLED.h>


// SETTINGS
const float MIN_BRIGHTNESS = 0.5f;      // % of min. brightness -- 0 always off, 1.0 full bright
const float MAX_BRIGHTNESS = 0.75f; 
const float BRIGHTNESS_RATE = 60.0f;   // Speed of brightness pulsing (bigger = slower)
const float COLORCHANGE_RATE = 500.0f; // Speed of color transition 
// END SETTINGS


const uint8_t NUM_LEDS = 10;
CRGB leds[NUM_LEDS];
uint32_t frames = 0;

void setup()
{
  FastLED.addLeds<WS2812B, 2, GRB>(leds, NUM_LEDS);
}

// linear interpolation
float lerp(float begin, float end, float t)
{
  return (t * end + (1 - t) * begin);
}

// color interpolation
CRGB clerp(CRGB begin, CRGB end, float t)
{
  float r = lerp(begin.r, end.r, t);
  float g = lerp(begin.g, end.g, t);
  float b = lerp(begin.b, end.b, t);
  return CRGB(r, g, b);
}

void loop()
{
  frames++;

  float brightness = (sin(frames / BRIGHTNESS_RATE) + 1) * 0.5f;    // results in a value from 0 to 1
  float interpolate = (sin(frames / COLORCHANGE_RATE) + 1) * 0.5f;  // same (at a different timing rate)
  
  CRGB color = clerp(CRGB::White, CRGB::Blue, interpolate);

  // update the color and brightness
  for (uint8_t i = 0; i < NUM_LEDS; i++) leds[i] = color;
  FastLED.setBrightness(lerp(MIN_BRIGHTNESS, MAX_BRIGHTNESS, brightness) * 255);
  FastLED.show();
}

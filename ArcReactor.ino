
// ARC REACTOR
// Ryan Appel


// NOTE: If you want to change "slots," hold a pin from D3 (slot 1)
// through D12 (slot 10) and press the reset button.


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
uint8_t mode = 0;

void setup()
{
  FastLED.addLeds<WS2812B, 2, GRB>(leds, NUM_LEDS);

  // setup pins to handle additional modes
  for (uint8_t i = 3; i < 13; i++) pinMode(i, INPUT_PULLUP);
  delay (200);
  for (uint8_t i = 3; i < 13; i++) if (!digitalRead(i)) mode = i - 2;
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

  // calculate pulsing
  float brightValue = (sin(frames / BRIGHTNESS_RATE) + 1) * 0.5f;    // results in a value from 0 to 1
  float colorValue = (sin(frames / COLORCHANGE_RATE) + 1) * 0.5f;  // same (at a different timing rate)

  // update color and brightness
  CRGB color = clerp(CRGB::White, CRGB::Blue, colorValue);
  float brightness = lerp(MIN_BRIGHTNESS, MAX_BRIGHTNESS, brightValue);


  // "SLOTS"
  // override default color and/or brightness for each mode here
  switch (mode)
  {
    case 1:
      color = CRGB::Red;
      brightness = MIN_BRIGHTNESS;
      break;
      
    case 2:
      color = CRGB::Green;
      break;
      
    case 3:
      color = CRGB::Blue;
      break;
      
    case 4:
      break;
      
    case 5:
      break;
      
    case 6:
      break;
      
    case 7:
      break;
      
    case 8:
      break;
      
    case 9:
      break;
      
    case 10:
      break;
  }
  

  // update the color and brightness
  for (uint8_t i = 0; i < NUM_LEDS; i++) leds[i] = color;
  FastLED.setBrightness(brightness * 255);
  FastLED.show();
}

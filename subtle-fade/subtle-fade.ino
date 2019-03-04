/**
 * Adapted from the FastLED examples. Thank you so much to that team for the
 * excellent example files.
 *
 * @author Jacob Fischer <jacob.t.fischer@gmail.com>
 *
 * This is a small script that given some configuration about your LEDs uses
 * the FastLED library to slowly scroll through RGB colors of all hues. Unlike
 * most similar code that does this online, this script has configurable
 * segments so the color doesn't drastically change. Instead you get slow
 * colors fading through the strip, but never the same color across the entire
 * strip.
 */

#include <FastLED.h>

#define LED_PIN         5
#define COLOR_ORDER     GRB
#define CHIPSET         WS2812B
#define NUM_LEDS        240

#define BRIGHTNESS      200 // All LED's brightness
#define LOOP_DELAY      35  // loop delay, longer means slower animations
#define SEGMENT_LENGTH  3   // How many LEDs long each segment should be

CRGB leds[NUM_LEDS];

void setup() {
  delay(3000); // sanity delay
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness( BRIGHTNESS );
}

void fadeall() { for(int i = 0; i < NUM_LEDS; i++) { leds[i].nscale8(250); } } // not used

static byte hue = 0;

void loop() {
  hue += 1; // static instance for future loops
  byte currentHue = hue; // copy to manipulate without affecting static instance
  byte currentSegment = hue % SEGMENT_LENGTH;

  // iterate through all LEDS in strip by index and set colors
  for(int i = 0; i < NUM_LEDS; i++) {
    if (++currentSegment >= SEGMENT_LENGTH - 1) { // new hue segment, next hue for it
      currentSegment = 0;
      currentHue++;
    }

    leds[i] = CHSV(currentHue, 255, 255);
  }

  FastLED.show();
  delay(LOOP_DELAY);
}

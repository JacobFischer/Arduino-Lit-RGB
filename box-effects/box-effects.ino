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
#define NUM_LEDS        (26*2 + 28*2)

#define BRIGHTNESS      255 // All LEDs' brightness
#define LOOP_DELAY      75  // loop delay, longer means slower animations

CRGB leds[NUM_LEDS];

void setup() {
  delay(3000); // sanity delay
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness( BRIGHTNESS );
}

void fadeall() { for(int i = 0; i < NUM_LEDS; i++) { leds[i].nscale8(250); } } // not used

static byte offset = 0; // change to short or something if >255 leds

void loop() {
  offset += 1;
  offset = offset % NUM_LEDS; // cap so when a fade loop occurs it resets

  // for each leds, set it to some number between [0, 255] by an offset so it scrolls around the box
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV((int)((float)(i + offset) / (float)NUM_LEDS * 255.0) % 255, 255, 255);
  }

  FastLED.show();
  delay(LOOP_DELAY);
}

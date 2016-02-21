#include <Adafruit_NeoPixel.h>

#define PIN 0

Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, PIN);

uint32_t loops = 0; // the number of times we have looped.
uint32_t multiplier = 1; // multiplier for pixel/color offset calculation.
uint32_t direction = 1; // up or down

// How often should we consider changing the multiplier?
#define MULTIPLIER_FREQUENCY 2000
// How do we decide the new multiplier? ZERO IS BAD.
#define MULTIPLIER_CHOICE (random(16) + 1)
// How often should we consider changing direction?
#define DIRECTION_FREQUENCY 10000
// How do we decide if we are walking forwards or backwards?
#define DIRECTION_CHOICE (random(1))

void setup() {
  strip.begin();
  strip.setBrightness(30);
  loops = 0;
  multiplier = 1;
  direction = 1;
}

// Space the entire 256-color line across some fraction of the strip; dup
// across the whole strip; then rotate it.
void loop() {
  if (loops % MULTIPLIER_FREQUENCY == 0) {
    multiplier = MULTIPLIER_CHOICE;
  }
  if (loops % DIRECTION_FREQUENCY == 0) {
    direction = DIRECTION_CHOICE ? 1 : -1;
  }

  uint8_t i;
  uint32_t factor = direction * multiplier * 256 / strip.numPixels();
  for (i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, Wheel((i * factor + loops) & 255));
  }

  strip.show();
  loops++;
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

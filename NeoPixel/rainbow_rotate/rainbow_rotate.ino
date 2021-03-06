#include <Adafruit_NeoPixel.h>

#define PIN 0

Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, PIN);

uint32_t loops = 0; // the number of times we have looped.

void setup() {
  strip.begin();
  strip.setBrightness(30);
  loops = 0;
}

// Space the entire 256-color line across the strip then rotate it.
void loop() {
  uint8_t i;
  for (i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, Wheel((i * 256 / strip.numPixels() + loops) & 255));
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

#include <Adafruit_NeoPixel.h>

#define PIN 0

Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, PIN);

void setup() {
  strip.begin();
  strip.setBrightness(30);
}

// Randomly give the same color to all pixels.
//
// An experiment that does not use the Wheel helper function.
//
// This tends toward white colors, as it is likely that all three rgb will get
// real values.
//
// Try different default brightness settings and different MAX_RGB.
#define MAX_RGB 256
void loop() {
  uint8_t r = random(MAX_RGB);
  uint8_t g = random(MAX_RGB);
  uint8_t b = random(MAX_RGB);
  uint8_t i;
  for (i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, r, g, b);
  }
  strip.show();
  delay(500);
}

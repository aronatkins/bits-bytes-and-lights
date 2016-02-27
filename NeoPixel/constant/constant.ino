// This sketch applys a single color to every pixel. That color doesn't ever
// change.

#include <Adafruit_NeoPixel.h>

#define PIN 0

Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, PIN);

// This is our color; use any value from 0 to 255.
uint8_t color = 128;

void setup() {
  strip.begin();
  strip.setBrightness(30);
}

// Apply a color to each pixel.
void loop() {
  uint8_t i;
  for (i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, Wheel(color));
  }
  strip.show();

  delay(500);
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

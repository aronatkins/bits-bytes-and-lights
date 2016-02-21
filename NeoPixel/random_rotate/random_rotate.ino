#include <Adafruit_NeoPixel.h>

#define PIN 0

Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, PIN);

// We store color values outside the strip because we set a default
// brightness. As a result, calling getPixelColor to then call setPixelColor
// is lossy and changes colors.
uint32_t values[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

void setup() {
  strip.begin();
  strip.setBrightness(30);
}

// Randomly choose colors for all pixels, then rotate a full cycle in either
// direction.
void loop() {
  uint16_t i,j;
  for (i=0; i<16; i++) {
    // We do this with one call to random and bit-masking. See random_some for
    // similar ideas.
    uint16_t r = random(1024);
    switch(r & 3) {
    case 0:
      // 25% of the time, turn the pixel off.
      values[i] = strip.Color(0,0,0);
      break;
    case 1:
      // 25% of the time, give it a new color.
      values[i] = Wheel((r >> 2) & 255);
      break;
      // 50% of the time, leave it alone.
    }
  }

  // If direction is positive, we walk forwards along the strip. When
  // negative, we walk backwards.
  uint32_t direction = random(2)?1:-1;

  // The outer loop means that we perform a full rotation.
  for (j=0; j<16; j++) {
    // The inner loop causes every pixel to get the next value on a single
    // step of our rotation.
    for (i=0; i<16; i++) {
      // Treat values as a circular buffer - as we walk off its end, we
      // continue to its start.
      strip.setPixelColor(i, values[(i+j*direction) % 16]);
    }
    strip.show();
    delay(100);
  }
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

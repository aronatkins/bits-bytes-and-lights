#include <Adafruit_NeoPixel.h>

#define PIN 0

Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, PIN);

// We store color values outside the strip because we set a default
// brightness. As a result, calling getPixelColor to then call setPixelColor
// is lossy and changes colors.
uint32_t values[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

uint32_t loops;     // count the number of loops
uint32_t direction; // stores our direction

// How often should we consider changing direction?
#define DIRECTION_FREQUENCY 64
// How do we decide if we are walking forwards/backwards?
#define DIRECTION_CHOICE (random(2)==1)

void setup() {
  strip.begin();
  strip.setBrightness(30);

  loops = 0;
  direction = 1;
}

// Randomly make a color appear in the 0th pixel and walk it across the strip.
// Sometimes we walk forwards, sometimes we walk backwards.
void loop() {
  // We always manipulate "values" with forward walks and then take
  // "direction" and "loops" into account when assigning those colors to the
  // actual pixels.

  uint32_t i;

  // walk all the current colors forward one step, dropping whatever is last.
  for (i=15; i>0; i--) {
    values[i] = values[i-1];
  }

  // now randomly choose if the 0th gets a color.
  switch(random(4)) {
  case 0:
    // 25% of the time, give a new color
    values[0] = Wheel(random(256));
    break;
  default:
    // 75% of the time, make it black.
    values[0] = strip.Color(0,0,0);
    break;
  }

  // Every so often decide if we should change direction.
  //
  // If direction is positive, we walk forwards along the strip. When
  // negative, we walk backwards.
  if (loops%DIRECTION_FREQUENCY==0) {
    direction = DIRECTION_CHOICE?1:-1;
  }

  for (i=0; i<16; i++) {
    strip.setPixelColor((i*direction)%16, values[i]);
  }
  ++loops;

  strip.show();
  delay(100);
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

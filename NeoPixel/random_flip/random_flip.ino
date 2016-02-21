#include <Adafruit_NeoPixel.h>

#define PIN 0

Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, PIN);

void setup() {
  strip.begin();
  strip.setBrightness(30);
}

// Randomly choose a color and give some pixels that color and some pixels the
// inverse of that color.
void loop() {
  uint8_t i;
  uint8_t c = random(256);
  uint32_t main = Wheel(c);
  uint32_t different;

  // Try different ways of coming up with your second color! Some ideas:
  //
  // Also random:
  // different = Wheel(256);
  //
  // Invert the computed color:
  // different = ~main;
  //
  // Invert the chosen color:
  // different = Wheel(~c);
  //
  // Rotate some amount around the 256-color line.
  different = Wheel( (c+64) % 256 );
 
  for (i=0; i<strip.numPixels(); i++) {
    if (random(2)) {
      strip.setPixelColor(i, main);
    } else {
      strip.setPixelColor(i, different);
    }
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

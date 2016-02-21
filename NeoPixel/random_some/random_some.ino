#include <Adafruit_NeoPixel.h>

#define PIN 0

Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, PIN);

void setup() {
  strip.begin();
  strip.setBrightness(30);
}

// Randomly choose what pixels to change and randomly choose its color.
void loop() {
  uint8_t i;
  for (i=0; i<strip.numPixels(); i++) {
    // Lowest bit is on/off. Remaining bits are color choice.
    /*
    uint16_t r = random(512);
    if (r & 1) {
      strip.setPixelColor(i, Wheel((r >> 1) & 255));
    }
    */
    // Implementation using two separate calls to random:
    /*
    if (random(2)) {
      strip.setPixelColor(i, Wheel(random(256)));
    }
    */
    // Implementation that uses two bits of randomness when deciding if a
    // pixel should be set.
    /*
    uint16_t r = random(1024);
    if ((r & 3) > 2) { // >0=75%, >1=50%, >2=25% chance
      strip.setPixelColor(i, Wheel((r >> 2) & 255));
    }
    */
    // Implementation that uses two bits of randomness and sometimes turns a
    // pixel off.
    uint16_t r = random(1024);
    switch(r & 3) {
    case 0:
      // 25% of the time, turn the pixel off.
      strip.setPixelColor(i, strip.Color(0,0,0));
      break;
    case 1:
      // 25% of the time, give it a new color.
      strip.setPixelColor(i, Wheel((r >> 2) & 255));
      break;
      // 50% of the time, leave it alone.
    }
  }
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

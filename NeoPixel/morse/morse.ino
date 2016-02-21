#include <Adafruit_NeoPixel.h>

#define PIN 0

Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, PIN);

void setup() {
  strip.begin();
  strip.setBrightness(30);
}

// https://en.wikipedia.org/wiki/Morse_code
#define ON pushColor(255)
#define OFF pushColor(0)
#define DIT dit()
#define DAH dah()
#define CH ch()
#define LT lt()
#define WD wd()
#define A letter_A()
#define B letter_B()
#define C letter_C()
#define D letter_D()
#define E letter_E()
#define F letter_F()
#define G letter_G()
#define H letter_H()
#define I letter_I()
#define J letter_J()
#define K letter_K()
#define L letter_L()
#define M letter_M()
#define N letter_N()
#define O letter_O()
#define P letter_P()
#define Q letter_Q()
#define R letter_R()
#define S letter_S()
#define T letter_T()
#define U letter_U()
#define V letter_V()
#define W letter_W()
#define X letter_X()
#define Y letter_Y()
#define Z letter_Z()

void loop() {
  H;LT;E;LT;L;LT;L;LT;O;
  WD;
  A;LT;R;LT;O;LT;N;
}

// Having these as functions instead of define blocks saves program space.
void dit() { ON; }
void dah() { ON;ON;ON; }
void ch() { OFF; }
void lt() { OFF;OFF;OFF; }
void wd() {
  for(uint8_t i=0; i<7; i++) { OFF; }
}
void letter_A() { DIT;CH;DAH; }
void letter_B() { DAH;CH;DIT;CH;DIT;CH;DIT; }
void letter_C() { DAH;CH;DIT;CH;DAH;CH;DIT; }
void letter_D() { DAH;CH;DIT;CH;DIT; }
void letter_E() { DIT; }
void letter_F() { DIT;CH;DIT;CH;DAH;CH;DIT; }
void letter_G() { DAH;CH;DAH;CH;DIT; }
void letter_H() { DIT;CH;DIT;CH;DIT;CH;DIT; }
void letter_I() { DIT;CH;DIT; }
void letter_J() { DIT;CH;DAH;CH;DAH;CH;DAH; }
void letter_K() { DAH;CH;DIT;CH;DAH; }
void letter_L() { DIT;CH;DAH;CH;DIT;CH;DIT; }
void letter_M() { DAH;CH;DAH; }
void letter_N() { DAH;CH;DIT; }
void letter_O() { DAH;CH;DAH;CH;DAH; }
void letter_P() { DIT;CH;DAH;CH;DAH;CH;DIT; }
void letter_Q() { DAH;CH;DAH;CH;DIT;CH;DAH; }
void letter_R() { DIT;CH;DAH;CH;DIT; }
void letter_S() { DIT;CH;DIT;CH;DIT; }
void letter_T() { DAH; }
void letter_U() { DIT;CH;DIT;CH;DAH; }
void letter_V() { DIT;CH;DIT;CH;DIT;CH;DAH; }
void letter_W() { DIT;CH;DAH;CH;DAH; }
void letter_X() { DAH;CH;DIT;CH;DIT;CH;DAH; }
void letter_Y() { DAH;CH;DIT;CH;DAH;CH;DAH; }
void letter_Z() { DAH;CH;DAH;CH;DIT;CH;DIT; }


// We store color values outside the strip because we set a default
// brightness. As a result, calling getPixelColor to then call setPixelColor
// is lossy and changes colors.
uint32_t values[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

void pushColor(uint32_t c) {
  uint8_t i;
  
  // walk all the current colors forward one step, dropping whatever is last.
  for (i=15; i>0; i--) {
    values[i] = values[i-1];
  }
  // our new value goes to zero.
  values[0] = c;
  // set all the colors.
  for (i=0; i<16; i++) {
    strip.setPixelColor(i, values[i]);
  }
  strip.show();
  delay(200);
}

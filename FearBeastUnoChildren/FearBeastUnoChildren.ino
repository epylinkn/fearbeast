// NeoPixel test program showing use of the WHITE channel for RGBW
// pixels only (won't look correct on regular RGB NeoPixel strips).

#include <Adafruit_NeoPixel.h>
#define BRIGHTNESS 255 // Set BRIGHTNESS to about 1/5 (max = 255)

// Declare our NeoPixel strip object:
Adafruit_NeoPixel outerStrip(15, 6, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel innerStrip(150, 11, NEO_GRBW + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)

enum ARTSTATES {
  BEASTING,
  TO_CHILD,
  CHILDING,
  TO_BEAST
};
ARTSTATES currentState = BEASTING;

unsigned long fadeInAt = 0;
unsigned long fadeOutAt = 0;
long pulseCounter = 0;
int led = 13;

int saucePins[4] = { 2, 3, 4, 5 };
int sauce[4] = { 0, 0, 0, 0 };

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);

  outerStrip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  outerStrip.show();            // Turn OFF all pixels ASAP
  outerStrip.setBrightness(BRIGHTNESS);
  
  innerStrip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  innerStrip.show();            // Turn OFF all pixels ASAP
  innerStrip.setBrightness(BRIGHTNESS);
  Serial.println("@leafcruncher");
}

void loop() {
  unsigned long currentTime = millis();

  int value = 0;
  for (int i = 0; i < 4; i++) {
    sauce[i] = digitalRead(saucePins[i]);
//    Serial.print(sauce[i]);
//    Serial.print("\t");
  }
  int math = sauce[0] + sauce[1] * 2 + sauce[2] * 4 + sauce[3] * 8;
//  Serial.println();

  // Update state from Teensy   
  if (math == 1) {
    currentState = TO_CHILD;
    Serial.println("TO_CHILD");
    fadeInAt = currentTime + 3 * 1000;
  }

  if (math == 2) {
    currentState = TO_BEAST;
    Serial.println("TO_BEAST");
    fadeOutAt = currentTime + 3 * 1000;
  }

  if (math == 4) {
    currentState = CHILDING;
    Serial.println("CHILDING");
    pulseCounter = 0;
  }

  if (math == 8) {
    currentState = BEASTING;
    Serial.println("BEASTING");
  }

  if (currentState == BEASTING) {
    allInnerOff();
    allOuterGlow();
  }

  if (currentState == TO_CHILD && fadeInAt >= currentTime) {
    float remaining = (fadeInAt - currentTime) / (3000.) * 100;
    int brightness = map(remaining, 0, 100, 150, 255);
    innerStrip.fill(innerStrip.Color(0, 0, 0, innerStrip.gamma8(brightness)));
    innerStrip.show();
    outerStrip.fill(outerStrip.Color(0, 0, 0, outerStrip.gamma8(brightness)));
    outerStrip.show();
  }

  if (currentState == CHILDING) {
    bool isFadingOut = (pulseCounter / 255 % 2 == 0); // isEven
    int distance = pulseCounter % 255;

    if (isFadingOut) {
      int fadeOutBrightness = map(distance, 0, 255, 255, 150);
      innerStrip.fill(innerStrip.Color(0, 0, 0, innerStrip.gamma8(fadeOutBrightness)));
      innerStrip.show();
      outerStrip.fill(outerStrip.Color(0, 0, 0, outerStrip.gamma8(fadeOutBrightness)));
      outerStrip.show();
// Serial.print("fadeOutBrightness: ");
// Serial.println(fadeOutBrightness);
    } else { // isFadingIn
      int fadeInBrightness = map(distance, 0, 255, 150, 255);
      innerStrip.fill(innerStrip.Color(0, 0, 0, innerStrip.gamma8(fadeInBrightness)));
      innerStrip.show();
      outerStrip.fill(outerStrip.Color(0, 0, 0, outerStrip.gamma8(fadeInBrightness)));
      outerStrip.show();
// Serial.print("fadeInBrightness: ");
// Serial.println(fadeInBrightness);
    }

    pulseCounter++;
  }

  if (currentState == TO_BEAST && fadeOutAt > millis()) {
    float remaining = (fadeOutAt - millis()) / 3000. * 100;
    int brightness = map(remaining, 0, 100, 2, 255);
    innerStrip.fill(innerStrip.Color(0, 0, 0, innerStrip.gamma8(brightness)));
    innerStrip.show();
    outerStrip.fill(outerStrip.Color(0, 0, 0, outerStrip.gamma8(brightness)));
    outerStrip.show();
//Serial.print("brightness: ");
//Serial.println(brightness);
  }

  delay(10);
}

void allInnerOff() {
  innerStrip.clear();
  innerStrip.show();
}

void allOuterGlow() {
  outerStrip.clear();
  outerStrip.fill(outerStrip.Color(0, 0, 0, outerStrip.gamma8(25)));
  outerStrip.show();
}

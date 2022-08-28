// FearBeast State Manager for Teensy 4.1
// - reads several pressure mats to manage state
// - controls cross-fading between two wav files
// - controls strip LEDs
// - sends state to DMX sender (raspberry pi)
//
// by @leafcruncher


///////////////////////////////////
// copy the Design Tool code here
// https://www.pjrc.com/teensy/gui
///////////////////////////////////
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Bounce.h>

// GUItool: begin automatically generated code
AudioPlaySdWav           playSdWav1;     //xy=2777.14276776995,1469.9999901907784
AudioPlaySdWav           playSdWav2;     //xy=2844.2856249128067,1579.9999901907784
AudioAmplifier           amp1;           //xy=3021.428482055664,1472.8571330479213
AudioAmplifier           amp2;           //xy=3051.428482055664,1618.571418762207
AudioEffectFade          fade1;          //xy=3391.428571428571,1501.4285714285713
AudioEffectFade          fade2;          //xy=3441.428571428571,1599.9999999999998
AudioMixer4              mixer1;         //xy=3609.9999999999995,1574.2857142857142
AudioOutputI2S           i2s1;           //xy=3784.9999999999973,1609.9999999999989
AudioConnection          patchCord1(playSdWav1, 0, amp1, 0);
AudioConnection          patchCord2(playSdWav2, 0, amp2, 0);
AudioConnection          patchCord3(amp1, fade1);
AudioConnection          patchCord4(amp2, fade2);
AudioConnection          patchCord5(fade1, 0, mixer1, 0);
AudioConnection          patchCord6(fade2, 0, mixer1, 1);
AudioConnection          patchCord7(mixer1, 0, i2s1, 0);
// GUItool: end automatically generated code
AudioControlSGTL5000     sgtl5000_1;

#define SDCARD_CS_PIN    BUILTIN_SDCARD
#define SDCARD_MOSI_PIN  11  // not actually used
#define SDCARD_SCK_PIN   13  // not actually used

#define arduino Serial8

enum ARTSTATES {
  BEASTING,
  TO_CHILD,
  CHILDING,
  TO_BEAST
};
ARTSTATES currentState = BEASTING;

// a boolean and timestamp to schedule future state change
bool nextState = false;
unsigned long nextStateAt = 0;

const int matPins[8] = { A0, A1, A2, A3, A14, A15, A16, A17 };
int matReadings[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
int matThreshold = 300;
int stripPin = 37;
unsigned long autoplayAt = 0;

void setup() {
  Serial.begin(9600);
  arduino.begin(9600);

//  override_setup();
  
  AudioMemory(300);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.6);
  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  if (!(SD.begin(SDCARD_CS_PIN))) {
    while (1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }
  
  mixer1.gain(0, 0.5);
  mixer1.gain(1, 0.5);
  
  delay(1000);

  Serial.println("BEASTING");
}

void loop() {
  override_loop();
  arduino.println("ping");
  unsigned long currentTime = millis();

  //= Read Pressure Mats
//  bool pressed = false;
//  for (int i = 0; i < 8; i++) {
//    int reading = analogRead(matPins[i]);
//    if (reading > matThreshold) {
//      pressed = true;
//    }
//    Serial.print(reading);
//    Serial.print("\t");
//  }
//  Serial.println();
    
//  if (currentState == BEASTING && pressed) {
  if (currentState == BEASTING && autoplayAt < millis()) {
    currentState = TO_CHILD;
    Serial.println("TO_CHILD");
    arduino.println("TO_CHILD");
    long transitionMs = 3 * 1000;
    nextStateAt = currentTime + transitionMs;
    fade1.fadeOut(transitionMs);
    fade2.fadeIn(transitionMs);
    autoplayAt = millis() + 60 * 1000;
  }

//  if (currentState == CHILDING && !pressed) {
  if (currentState == CHILDING && autoplayAt < millis()) {
    currentState = TO_BEAST;
    Serial.println("TO_BEAST");
    arduino.println("TO_BEAST");
    long transitionMs = 15 * 1000;
    nextStateAt = currentTime + transitionMs;
    fade1.fadeIn(transitionMs);
    fade2.fadeOut(transitionMs);
    autoplayAt = millis() + 60 * 1000;
  }

  //= Handle queued state changes
  if (currentState == TO_CHILD && currentTime > nextStateAt) {
    currentState = CHILDING;
    Serial.println("CHILDING");
    arduino.println("CHILDING");
  }

  if (currentState == TO_BEAST && currentTime > nextStateAt) {
    currentState = BEASTING;
    Serial.println("BEASTING");
    arduino.println("BEASTING");
  }

  //= Keep the audio ALWAYS looping...
  if (playSdWav1.isPlaying() == false) {
//    Serial.println("Re-start Beasting");
    playSdWav1.play("fearbeast-beasting.wav");
    delay(10); // wait for library to parse WAV info
  }
  
  if (playSdWav2.isPlaying() == false) {
//    Serial.println("Re-start Childing");
    playSdWav2.play("fearbeast-childing.wav");
    delay(10); // wait for library to parse WAV info
  }
}

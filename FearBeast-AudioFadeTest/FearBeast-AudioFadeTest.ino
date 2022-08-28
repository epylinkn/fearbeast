// Advanced Microcontroller-based Audio Workshop
//
// http://www.pjrc.com/store/audio_tutorial_kit.html
// https://hackaday.io/project/8292-microcontroller-audio-workshop-had-supercon-2015
// 
// Part 2-2: Mixers & Playing Multiple Sounds


///////////////////////////////////
// copy the Design Tool code here
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

bool isFearing = true;
// TODO: add a delay?
//unsigned long reFearAt = 0;

int buttonPin = 35;
Bounce button0 = Bounce(buttonPin, 2000);

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);
  
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
//  pinMode(13, OUTPUT); // LED on pin 13
  
  mixer1.gain(0, 0.5);
  mixer1.gain(1, 0.5);
  delay(1000);
}

void loop() {
  // Check for state change
  button0.update();

  // switch to parting
  if (isFearing && button0.fallingEdge()) {
    Serial.println("Start Parting");
    isFearing = false;
    fade1.fadeOut(5000);
    fade2.fadeIn(5000);
  }

  // switch to fearing 
  if (!isFearing && button0.risingEdge()) {
    Serial.println("Start Fearing");
    isFearing = true;
    fade1.fadeIn(5000);
    fade2.fadeOut(5000);
  }

  // Keep the audio looping...
  if (isFearing && playSdWav1.isPlaying() == false) {
    Serial.println("Re-start Fearing");
    playSdWav1.play("the-frontier.wav");
    delay(10); // wait for library to parse WAV info
  }
  
  if (!isFearing && playSdWav2.isPlaying() == false) {
    Serial.println("Re-start Parting");
    playSdWav2.play("always-like-this.wav");
    delay(10); // wait for library to parse WAV info
  }
}

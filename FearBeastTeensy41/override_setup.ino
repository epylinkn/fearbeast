int buttonPin = 35;
Bounce button0 = Bounce(buttonPin, 2000);

void override_setup() {
  pinMode(buttonPin, INPUT_PULLUP);
}

void override_loop() {
   // Check for state change
  button0.update();

  // switch to childing
  if (currentState == BEASTING && button0.fallingEdge()) {
    currentState = TO_CHILD;
    Serial.println("TO_CHILD");
    long transitionMs = 3 * 1000;
    nextStateAt = millis() + transitionMs;
    fade1.fadeOut(transitionMs);
    fade2.fadeIn(transitionMs);
  }

  // switch to fearing 
  if (currentState == CHILDING && button0.fallingEdge()) {
    currentState = TO_BEAST;
    Serial.println("TO_BEAST");
    long transitionMs = 15 * 1000;
    nextStateAt = millis() + transitionMs;
    fade1.fadeIn(transitionMs);
    fade2.fadeOut(transitionMs);
  }
}

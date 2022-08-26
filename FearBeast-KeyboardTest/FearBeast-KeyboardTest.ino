/* Simple USB Keyboard Example
   Teensy becomes a USB keyboard and types characters

   You must select Keyboard from the "Tools > USB Type" menu

   This example code is in the public domain.
*/

bool pressed = false;

void setup() {
  Serial.begin(9600);

  pinMode(35, INPUT_PULLUP);
  delay(1000);
}

void loop() {
  // Your computer will receive these characters from a USB keyboard.

  if (!pressed && digitalRead(35) == LOW) {
    Keyboard.print("schmeckel"); 
    pressed = true;
  }

  delay(1000);
  pressed = false;
}

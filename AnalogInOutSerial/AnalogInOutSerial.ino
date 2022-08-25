const int numReadings = 10;

int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average

// These constants won't change. They're used to give names to the pins used:
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to

const int ledPin = 13;       // pin that the LED is attached to
int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)
const int threshold = 1000;   // an arbitrary threshold level that's in the range of the analog input
const int thresholdLow = 800;   // an arbitrary threshold level that's in the range of the analog input
int activated = 1; 


void setup() {
  // initialize serial communications at 9600 bps:
  pinMode(ledPin, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // read the analog in value:
  sensorValue = analogRead(analogInPin);
  // map it to the range of the analog out:
  Serial.print("sensorValue:");
  Serial.println(sensorValue);
  // subtract the last reading:
  total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = sensorValue;
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }

  // calculate the average:
  average = total / numReadings;
//  Serial.println(average);

  // if the analog value is high enough, turn on the LED:
  if (average > threshold) {
    if (activated == 0) {
      digitalWrite(ledPin, HIGH);
      Serial.println("ACTIVATED");
      activated = 1;
    }
  } 
  if (average < thresholdLow){
    if (activated == 1) {
      digitalWrite(ledPin, LOW);
      Serial.println("DEACTIVATED");
      activated = 0;
    }
  }
  // print the results to the Serial Monitor:
//  Serial.print("average = ");
//  Serial.println(average);


  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(100);
}

 const int numReadings = 10;
const int threshold = 1000;   // the threshold level that's will activate the trigger
const int thresholdLow = 800;   // an threshold level that will deactivate the trigger 
const int ledPin = 13;       // pin that the LED is attached to


int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)
int activated_array[6] = {0, 0, 0, 0, 0, 0}; 
int activated_sum = 0;                
int activated = 0;

const int analogInPin_0 = A0;  // Analog input pin that the potentiometer is attached to
const int analogInPin_1 = A1;  // Analog input pin that the potentiometer is attached to
const int analogInPin_2 = A2;  // Analog input pin that the potentiometer is attached to
const int analogInPin_3 = A3;  // Analog input pin that the potentiometer is attached to
const int analogInPin_4 = A4;  // Analog input pin that the potentiometer is attached to
const int analogInPin_5 = A5;  // Analog input pin that the potentiometer is attached to

void setup() {
  // initialize serial communications at 9600 bps:
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  activated_sum = 0;
  read_sensor(analogInPin_0, 0);
  read_sensor(analogInPin_1, 1);
  read_sensor(analogInPin_2, 2);
  read_sensor(analogInPin_3, 3);
  read_sensor(analogInPin_4, 4);
  read_sensor(analogInPin_5, 5);

  int i;
  for (i=0; i< 6; i++) {
      activated_sum += activated_array[i];
  }

  if (activated_sum > 0) { // the 0 and 1 will gate the trigger so it only sends its activation/deactivation once
    if (activated == 0) {
      digitalWrite(ledPin, HIGH);
      Serial.println("ACTIVATED"); // this string will trigger the raspberry pi
      activated = 1;
      }
    }

  else {
    if (activated == 1) { // the 0 and 1 will gate the trigger so it only sends its activation/deactivation once
      digitalWrite(ledPin, LOW);
      Serial.println("DEACTIVATED"); // this string will trigger the raspberry pi
      activated = 0;
    }
  }

  delay(100);
  }

void read_sensor(int analogInPin, int activated_array_num) {
    sensorValue = analogRead(analogInPin);
//    Serial.print("sensorValue ");
//    Serial.print(activated_array_num);
//    Serial.print(":");
//    Serial.println(sensorValue);
    
    if (sensorValue > threshold) {
      if (activated_array[activated_array_num] == 0) { // the 0 and 1 will gate the trigger so it only sends its activation/deactivation once
        Serial.print("PAD_ACTIVATED ");
        Serial.println(activated_array_num);
        (activated_array[activated_array_num]) = 1;
      }
    }

    if (sensorValue < thresholdLow){
      if (activated_array[activated_array_num] == 1) { // the 0 and 1 will gate the trigger so it only sends its activation/deactivation once
        Serial.print("PAD_DEACTIVATED ");
        Serial.println(activated_array_num);
        (activated_array[activated_array_num]) = 0;
      }
    }
  }

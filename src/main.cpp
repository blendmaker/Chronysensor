#include <Arduino.h>

const uint8_t outputPins[] = { 18, 19, 20, 21 };
const uint8_t input1 = 2;
const uint8_t input2 = 3;

const float distance = 100 * 0.001f; // in m

volatile unsigned long startTime = 0;
volatile double travelTime = 0;

void inputTriggered() {
  travelTime = 0;
  startTime = micros();
}

void outputTriggered() {
  if (startTime != 0)
  {
    travelTime = (micros()-startTime)*0.000001f;
    startTime = 0;
  }
}

void setup() {
  Serial.begin(115200);

  for (byte i = 0; i <  (sizeof(outputPins) / sizeof(outputPins[0])); i++) {
    pinMode( outputPins[i], OUTPUT );
    digitalWrite( outputPins[i], HIGH );
  }

  pinMode(input1, INPUT_PULLUP);
  pinMode(input2, INPUT_PULLUP);
  
  attachInterrupt( digitalPinToInterrupt(input1), inputTriggered,  FALLING);
  attachInterrupt( digitalPinToInterrupt(input2), outputTriggered,  FALLING);
}

void loop() {
  if (travelTime > 0) {
    double mps = distance / travelTime;
    Serial.print(String(mps));
    Serial.print(";");
    travelTime = 0;
  }
}

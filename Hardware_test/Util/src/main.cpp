#include <Arduino.h>

void setup() {
  Serial.begin(9600);
  #ifdef test
  Serial.print("Defined: ");
  Serial.println(binary_test,BIN);
  #endif
}

void loop() {
  // put your main code here, to run repeatedly:
}
#include <Arduino.h>
int sensorPin = A0;
char buffer[10];
void setup() {
  Serial.begin(115200);
}

void loop() {
  int sensorValue = analogRead(sensorPin);
  sprintf(buffer,"%d\n",sensorValue);
  Serial.print(buffer);
}

#include <cmodbus.h>

cmodbus cmodbus(Serial);

void setup() {
  Serial.begin(115200);
  cmodbus.begin();
}

void loop() {
  // Write a value to register 1 in the server (slave 1)
  uint8_t server = 1;
  uint16_t registerAddr = 1;
  uint16_t data = 128;

  if (cmodbus.writeSingleRegister(server, registerAddr, data)) {
    Serial.println("Write request sent successfully.");
  } else {
    Serial.println("Failed to send write request.");
  }

  delay(1000);
}

#include <Arduino.h>
#include "modbus_client.h"

ModbusClient modbus;

void setup()
{
    modbus.init(0x01, 9600);
}

void loop()
{
    uint16_t data = 0;
    modbus.read(0x0005, &data);
    delay(5000);
}

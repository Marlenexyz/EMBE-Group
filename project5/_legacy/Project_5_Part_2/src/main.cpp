#include <Arduino.h>
#include "modbus_server.h"

ModbusServer modbus;

void setup()
{
    modbus.init(0x01, 9600);
}

void loop()
{
    modbus.handleRequest();
}

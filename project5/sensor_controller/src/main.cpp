#include <Arduino.h>
#include "modbus_server.h"

ModbusServer modbus;
uint16_t registerNr = 0x0000;

// int sensorPin = A0;
const int opPin = 2;
const int stopPin = 3;
const int preOpPin = 4;
const int resetPin = 5;
const int comPin = 6;

// char buffer[10];

void setup()
{
    Serial.begin(9600);
    modbus.init(0x01, 9600); // Server Nr, Baudrate

    pinMode(opPin, INPUT_PULLUP);
    pinMode(stopPin, INPUT_PULLUP);
    pinMode(preOpPin, INPUT_PULLUP);
    pinMode(resetPin, INPUT_PULLUP);
    pinMode(comPin, INPUT_PULLUP);
}

void loop()
{
    // handle client requests
    modbus.handleRequest();

    // int sensorValue = analogRead(sensorPin);
    // sprintf(buffer,"%d\n",sensorValue);
    // Serial.print(buffer);

    if (!digitalRead(opPin))
    {
        modbus.setReg(registerNr, 0x0001);
    }
    else if (!digitalRead(stopPin))
    {
        modbus.setReg(registerNr, 0x0002);
    }
    else if (!digitalRead(preOpPin))
    {
        modbus.setReg(registerNr, 0x0080);
    }
    else if (!digitalRead(resetPin))
    {
        modbus.setReg(registerNr, 0x0081);
    }
    else if (!digitalRead(comPin))
    {
        modbus.setReg(registerNr, 0x0082);
    }
}

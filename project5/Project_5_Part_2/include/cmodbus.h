#ifndef MODBUS_CLIENT_H
#define MODBUS_CLIENT_H

#include "Arduino.h"
#include <Stream.h>

class cmodbus {
public:
    cmodbus(Stream& stream);
    void begin();
    bool writeSingleRegister(uint8_t server, uint16_t registerAddr, uint16_t data);

private:
    Stream& communicationStream;
};

#endif

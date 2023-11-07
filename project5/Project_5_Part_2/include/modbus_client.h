#ifndef MODBUSCLIENT_H
#define MODBUSCLIENT_H

#include <stdint.h>

class ModbusClient
{
public:

    ModbusClient(uint8_t serverNr);
    virtual ~ModbusClient();

    // ModbusClient function read
    void read(uint16_t reg, uint16_t* data);
    // ModbusClient function write
    void write(uint16_t reg, uint16_t data);

private:

    // receive UART data
    void receive(uint8_t* msg, uint8_t len);
    // send UART data
    void send(uint8_t* msg, uint8_t len);

    // calculate the CRC
    uint16_t ModRTU_CRC(uint8_t buf[], int len);

    // server number
    uint8_t mServerNr;
};

#endif // ModbusClient_H

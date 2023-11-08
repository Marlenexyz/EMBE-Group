#ifndef MODBUSCLIENT_H
#define MODBUSCLIENT_H

#include <stdint.h>

class ModbusClient
{
public:

    ModbusClient();
    virtual ~ModbusClient();

    // initialize client
    void init(uint8_t serverNr, uint32_t baudrate);

    // client function read
    void read(uint16_t reg, uint16_t* data);
    // client function write
    void write(uint16_t reg, uint16_t data);

private:

    // receive UART data
    int32_t receive(uint8_t* msg, uint8_t len);
    // send UART data
    void send(uint8_t* msg, uint8_t len);

    // calculate the CRC
    uint16_t ModRTU_CRC(uint8_t buf[], int len);
    // print message
    void printMsg(uint8_t* msg, uint8_t len);

    // server number
    uint8_t mServerNr = 0;
};

#endif // ModbusClient_H

#ifndef MODBUSERVER_H
#define MODBUSERVER_H

#include <stdint.h>

class ModbusServer
{
public:

    ModbusServer();
    virtual ~ModbusServer();

    // initialize client
    void init(uint8_t serverNr, uint32_t baudrate);

    // set a register value from outside
    void setReg(uint16_t reg, uint16_t data);
    // read a register value from outside
    void getReg(uint16_t reg, uint16_t* data);

    // handle requests from clients
    void handleRequest();

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
    uint16_t mServerRegister[64] = {0};
};

#endif // ModbusServer_H

#ifndef MODBUSCLIENT_H
#define MODBUSCLIENT_H

#include <stdint.h>

class ModbusClient
{
public:

    ModbusClient();
    virtual ~ModbusClient();

    // initialize client
    void init(uint32_t baudrate);

    // open UART
    void openUart();
    // close UART
    void closeUart();

    // client function read
    void readServer(uint8_t server, uint16_t reg, uint16_t* data);
    // client function write
    void writeServer(uint8_t server, uint16_t reg, uint16_t data);

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
    int32_t mFile = 0;
};

#endif // ModbusClient_H

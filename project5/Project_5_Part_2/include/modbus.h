#ifndef MODBUS_H
#define MODBUS_H
#include <Arduino.h>


class modbus {
public:
    // Constructor that takes an integer parameter to initialize the variable.
    modbus(int variable);

    // Function to read data.
    int read(char message[],int len);

    // Function to write data.
    void write(char message[],int len);

    uint16_t ModRTU_CRC(uint8_t buf[], int len);

    uint32_t parseHex(const char* str, size_t length);
private:
    int server;
    int serverregister[100];
    uint16_t server_;
    uint16_t function_;
    uint32_t regi_;
    uint32_t numreg_;
    uint32_t value_;
    uint16_t crc_;
};

#endif // MODBUS_H

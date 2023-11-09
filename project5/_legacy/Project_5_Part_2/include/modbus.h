#ifndef MODBUS_H
#define MODBUS_H
#include <Arduino.h>


class modbus {
public:
    // Constructor that takes an integer parameter to initialize the variable.
    modbus(int variable);

    // Function to read data.
    void recieve(char message[],int len);

    void read(uint32_t regi_,uint32_t numreg_);

    // Function to write data.
    void write(uint32_t regi_,uint32_t value_);

    void send(uint32_t value_);

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


#ifndef MODBUS_H
#define MODBUS_H
#include <Arduino.h>

class modbus {
public:
    // Constructor that takes an integer parameter to initialize the variable.
    modbus(int variable);

    // Function to read data.
    int read(uint8_t message[],int len);

    // Function to write data.
    void write(int data);

    uint16_t ModRTU_CRC(uint8_t buf[], int len);
private:
    int server;
    int serverregister[100];
};

#endif // MODBUS_H

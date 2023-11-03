#include "cmodbus.h"

cmodbus::cmodbus(Stream& stream) : communicationStream(stream) {}

void cmodbus::begin() {
    // Initialize any communication settings here, e.g., baud rate
}

bool cmodbus::writeSingleRegister(uint8_t server, uint16_t registerAddr, uint16_t data) {
    // Create and send the Modbus request here using your communicationStream
    // You need to implement the Modbus request format manually

    // Example: Serial communication
    communicationStream.write(server);
    communicationStream.write(0x06); // Function code for Write Single Register
    communicationStream.write(registerAddr >> 8); // High byte of register address
    communicationStream.write(registerAddr & 0xFF); // Low byte of register address
    communicationStream.write(data >> 8); // High byte of data
    communicationStream.write(data & 0xFF); // Low byte of data

    // You need to implement the actual request format and communication

    // Return true if the request was sent successfully
    return true;
}

#include "modbus.h"
#include <stdint.h>
modbus::modbus(int server) {
    this->server = server;
}

int modbus::read(uint8_t message[],int len) {

    uint16_t regist;
    uint16_t data;
    
    uint16_t crc = message[len-1]; //ÄNDERN

    
    //CRC Check
    if(crc =!ModRTU_CRC(message, len)){
        Serial.println("Message was wrong submitted");
    }
    
    
    
    if (&serverregister[regist]==nullptr){
        Serial.println("No Value in the register");
    }
    else {
        int value=serverregister[regist];
        
        Serial.print(value);
    

    }


    return 1; 
}

void modbus::write(int data) {
    // Implement your write logic here using the 'data' parameter.
    // You can use this->variable to access the variable value.
    // Example:
    // writeDataToModbus(this->variable, data);
    // Replace with actual write implementation
}

uint16_t ModRTU_CRC(uint8_t buf[], int len)
{
uint16_t crc = 0xFFFF;
for (int pos = 0; pos < len; pos++) {
crc ^= (uint16_t)buf[pos]; // XOR byte into least sig. byte of crc
for (int i = 8; i != 0; i--) { // Loop over each bit
if ((crc & 0x0001) != 0) { // If the LSB is set
crc >>= 1; // Shift right and XOR 0xA001
crc ^= 0xA001;
}
else // Else LSB is not set
crc >>= 1; // Just shift right
}
}
// Note, this number has low and high bytes swapped, so use it accordingly (or swap bytes)
return crc;
}
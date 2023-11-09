#include "modbus.h"
#include <stdint.h>
#include<string.h>
#include<Arduino.h>
#include <HardwareSerial.h>
modbus::modbus(int server) {
    this->server = server;

}

void modbus::recieve(char message[],int len) {

    server_ = parseHex(message, 2);
    function_ = parseHex(message + 2, 2);
    crc_ = parseHex(message + 12, 4);
    regi_ = parseHex(message + 4, 4);
    numreg_ = parseHex(message + 8, 4);
    // crc check
    uint8_t buffer[6]={server_,function_,regi_>>8,regi_,numreg_>>8,numreg_};


    if(ModRTU_CRC(buffer,6)==crc_){

        if (function_==3){
        regi_ = parseHex(message + 4, 4);
        numreg_ = parseHex(message + 8, 4);
        read(regi_,numreg_);
        }
        else if(function_==6){
        regi_ = parseHex(message + 4, 4);
        value_= parseHex(message + 8, 4);
        write(regi_,value_);
        }
    }
    else { 
        Serial.println("Das war wohl nichts du Hurensohn");
    }
}

void modbus::read(uint32_t regi_,uint32_t numreg_){
    for (uint32_t i = 0; i < numreg_; i++)
    {
        value_=serverregister[regi_+i];
        send(value_);
    }
    

}
void modbus::write(uint32_t regi_,uint32_t value_){
        serverregister[regi_]=value_;
        send(value_);
}

void modbus::send(uint32_t valuess){

    Serial.print(server_);
    Serial.print(function_);
    Serial.print(regi_);
    Serial.print(valuess);
    Serial.print(crc_);
}


uint16_t modbus::ModRTU_CRC(uint8_t buf[], int len)
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

    
    // Funktion zum Konvertieren von Hexadezimal-String in Ganzzahl
uint32_t modbus::parseHex(const char* str, size_t length) {
        uint32_t result = 0;
        for (size_t i = 0; i < length; i++) {
            result <<= 4;
            char c = str[i];
            if (c >= '0' && c <= '9') {
                result += c - '0';
            } else if (c >= 'A' && c <= 'F') {
                result += c - 'A' + 10;
            } else if (c >= 'a' && c <= 'f') {
                result += c - 'a' + 10;
            } else {
                // Unerwartetes Zeichen
                return 0;
            }
        }
        return result;
    }
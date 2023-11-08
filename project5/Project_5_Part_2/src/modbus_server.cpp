#include "modbus_server.h"
#include <Arduino.h>

ModbusServer::ModbusServer()
{

}

ModbusServer::~ModbusServer()
{

}

void ModbusServer::init(uint8_t serverNr, uint32_t baudrate)
{
    mServerNr = serverNr;
    Serial.begin(baudrate);
}

void ModbusServer::handleRequest()
{
    uint8_t receiveMsg[8] = {0};
    if(receive(receiveMsg, sizeof(receiveMsg)) < 0)
    {
        // Serial.print("No message received!\n");
        return;
    }

    // Serial.print("Received message: ");
    // printMsg(receiveMsg, sizeof(receiveMsg));
    
    uint16_t recCrc = (receiveMsg[6] << 8) | receiveMsg[7];
    uint16_t calcCrc = ModRTU_CRC(receiveMsg, sizeof(receiveMsg) - 2);
    if(recCrc != calcCrc)
    {
        // Serial.print("CRC check failure!\n");
        return;
    }
    if(receiveMsg[0] != mServerNr)
    {
        // Serial.print("Received message invalid!\n");
        return;
    }


    if(receiveMsg[1] == 0x03)
    {
        // handle read
        uint8_t sendMsg[7] = {0};
        
        uint16_t reg = (receiveMsg[2] << 8) | receiveMsg[3];
        uint16_t data = mServerRegister[reg];

        sendMsg[0] = receiveMsg[0];
        sendMsg[1] = receiveMsg[1];
        sendMsg[2] = 0x02;
        sendMsg[3] = (uint8_t)(data >> 8);
        sendMsg[4] = (uint8_t)data;

        uint16_t crc = ModRTU_CRC(sendMsg, sizeof(sendMsg) - 2);
        sendMsg[5] = (uint8_t)(crc >> 8);
        sendMsg[6] = (uint8_t)crc;

        send(sendMsg, sizeof(sendMsg));

        // // Serial.print("Sent message: ");
        // printMsg(sendMsg, sizeof(sendMsg));
    }
    else if(receiveMsg[1] == 0x06)
    {
        // handle write
        uint16_t reg = (receiveMsg[2] << 8) | receiveMsg[3];
        uint16_t data = (receiveMsg[4] << 8) | receiveMsg[5];
        mServerRegister[reg] = data;

        send(receiveMsg, sizeof(receiveMsg));

        // // Serial.print("Sent message: ");
        // printMsg(receiveMsg, sizeof(receiveMsg));
    }
}

int32_t ModbusServer::receive(uint8_t* msg, uint8_t len)
{
    // timeout after 1s of waiting
    for(uint8_t i = 0; i < 100; i++)
    {
        if(Serial.available() > 0)
        {
            Serial.readBytes(msg, len);
            return 0;
        }
        delay(10);
    }
    return -1;
}

void ModbusServer::send(uint8_t* msg, uint8_t len)
{
    for(uint8_t i = 0; i < len; i++)
    {
        Serial.write(msg[i]);
    }
}

uint16_t ModbusServer::ModRTU_CRC(uint8_t buf[], int len)
{
    uint16_t crc = 0xFFFF;
    for (int pos = 0; pos < len; pos++)
    {
        crc ^= (uint16_t)buf[pos]; // XOR byte into least sig. byte of crc
        for (int i = 8; i != 0; i--) // Loop over each bit
        {
            if ((crc & 0x0001) != 0) // If the LSB is set
            {
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

void ModbusServer::printMsg(uint8_t* msg, uint8_t len)
{
    char buffer[64] = {0};
    for(uint8_t i; i < len; i++)
    {
        sprintf(&buffer[i*2], "%02X", msg[i]);
    }
    // // Serial.println(buffer);
}

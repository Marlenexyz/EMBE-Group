#include "modbus_client.h"
#include <Arduino.h>

ModbusClient::ModbusClient()
{

}

ModbusClient::~ModbusClient()
{

}

void ModbusClient::init(uint8_t serverNr, uint32_t baudrate)
{
    mServerNr = serverNr;
    Serial.begin(baudrate);
}

void ModbusClient::read(uint16_t reg, uint16_t* data)
{
    uint8_t sendMsg[8] = {0};
    sendMsg[0] = mServerNr;
    sendMsg[1] = 0x03;
    sendMsg[2] = (uint8_t)(reg >> 8);
    sendMsg[3] = (uint8_t)reg;
    sendMsg[4] = 0x00;
    sendMsg[5] = 0x01;

    uint16_t crc = ModRTU_CRC(sendMsg, sizeof(sendMsg) - 2);
    sendMsg[6] = (uint8_t)(crc >> 8);
    sendMsg[7] = (uint8_t)crc;

    send(sendMsg, sizeof(sendMsg));

    uint8_t receiveMsg[7] = {0};
    if(receive(receiveMsg, sizeof(receiveMsg)) < 0)
    {
        Serial.println("No message received!");
        return;
    }
    Serial.print("Received message: ");
    printMsg(receiveMsg, sizeof(receiveMsg));

    uint16_t recCrc = (receiveMsg[5] << 8) | receiveMsg[6];
    Serial.println(recCrc);
    uint16_t calcCrc = ModRTU_CRC(receiveMsg, sizeof(receiveMsg) - 2);
    Serial.println(calcCrc);
    if(recCrc != calcCrc)
    {
        Serial.println("CRC check failure!");
        return;
    }
    if(receiveMsg[0] != sendMsg[0]
    || receiveMsg[1] != sendMsg[1]
    || receiveMsg[2] != 0x02)
    {
        Serial.println("Received message invalid!");
        return;
    }

    // read data
    *data = (receiveMsg[3] << 8) | receiveMsg[4];

    Serial.print("Received data: ");
    Serial.println(*data);
}

void ModbusClient::write(uint16_t reg, uint16_t data)
{
    uint8_t sendMsg[8] = {0};
    sendMsg[0] = mServerNr;
    sendMsg[1] = 0x06;
    sendMsg[2] = (uint8_t)(reg >> 8);
    sendMsg[3] = (uint8_t)reg;
    sendMsg[4] = (uint8_t)(data >> 8);
    sendMsg[5] = (uint8_t)data;

    uint16_t crc = ModRTU_CRC(sendMsg, sizeof(sendMsg) - 2);
    sendMsg[6] = (uint8_t)(crc >> 8);
    sendMsg[7] = (uint8_t)crc;

    send(sendMsg, sizeof(sendMsg));
    
    uint8_t receiveMsg[8] = {0};
    if(receive(receiveMsg, sizeof(receiveMsg)) < 0)
    {
        Serial.println("No message received!");
        return;
    }

    for(uint8_t i = 0; i < sizeof(receiveMsg); i++)
    {
        if(receiveMsg[i] != sendMsg[i])
        {
            Serial.println("Received message invalid!");
            return;
        }
    }
}

int32_t ModbusClient::receive(uint8_t* msg, uint8_t len)
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

void ModbusClient::send(uint8_t* msg, uint8_t len)
{
    for(uint8_t i = 0; i < len; i++)
    {
        Serial.write(msg[i]);
    }
}

uint16_t ModbusClient::ModRTU_CRC(uint8_t buf[], int len)
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

void ModbusClient::printMsg(uint8_t* msg, uint8_t len)
{
    char buffer[64] = {0};
    for(uint8_t i; i < len; i++)
    {
        sprintf(&buffer[i*2], "%02X", msg[i]);
    }
    Serial.println(buffer);
}

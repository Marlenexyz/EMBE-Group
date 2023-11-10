#include "modbus_client.h"
#include <cstdio>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

ModbusClient::ModbusClient()
{

}

ModbusClient::~ModbusClient()
{

}

void ModbusClient::init(uint32_t baudrate)
{
    openUart();

    struct termios options;
    tcgetattr(mFile, &options);
    cfmakeraw(&options);

    // set baudrate
    if(baudrate == 9600)
        options.c_cflag = B9600 | CS8 | CREAD | CLOCAL;
    else if(baudrate == 115200)
        options.c_cflag = B115200 | CS8 | CREAD | CLOCAL;
    // wait for 1ds on read
    options.c_cc[VTIME] = 5;
    // min number of bytes
    options.c_cc[VMIN] = 1;

    tcflush(mFile, TCIFLUSH);
    tcsetattr(mFile, TCSANOW, &options);
    
    closeUart();
}

void ModbusClient::openUart()
{
    if((mFile = open("/dev/ttyS0", O_RDWR | O_NOCTTY | O_NDELAY)) < 0) // maybe needs: O_NDELAY
    {
        perror("Failed to open the file!\n");
        return;
    }
}

void ModbusClient::closeUart()
{
    close(mFile);
}

void ModbusClient::readServer(uint8_t server, uint16_t reg, uint16_t* data)
{
    const uint8_t SEND_LEN = 8;
    uint8_t sendMsg[SEND_LEN] = {0};
    sendMsg[0] = server;
    sendMsg[1] = 0x03;
    sendMsg[2] = (uint8_t)(reg >> 8);
    sendMsg[3] = (uint8_t)reg;
    sendMsg[4] = 0x00;
    sendMsg[5] = 0x01;

    uint16_t crc = ModRTU_CRC(sendMsg, SEND_LEN - 2);
    sendMsg[6] = (uint8_t)(crc >> 8);
    sendMsg[7] = (uint8_t)crc;

    send(sendMsg, SEND_LEN);
   // printf("Sent request:  ");
    printMsg(sendMsg, SEND_LEN);
    usleep(100000);

    const uint8_t RECEIVE_LEN = 7;
    uint8_t receiveMsg[RECEIVE_LEN] = {0};
    if(receive(receiveMsg, RECEIVE_LEN) < 0)
    {
        perror("No message received!\n");
        return;
    }
   // printf("Received reply:");
    printMsg(receiveMsg, RECEIVE_LEN);

    uint16_t recCrc = (receiveMsg[5] << 8) | receiveMsg[6];
    uint16_t calcCrc = ModRTU_CRC(receiveMsg, RECEIVE_LEN - 2);
    if(recCrc != calcCrc)
    {
        perror("CRC check failure!\n");
        return;
    }
    if(receiveMsg[0] != sendMsg[0]
    || receiveMsg[1] != sendMsg[1]
    || receiveMsg[2] != 0x02)
    {
        perror("Received message invalid!\n");
        return;
    }

    // read data
    *data = (receiveMsg[3] << 8) | receiveMsg[4];
}

void ModbusClient::writeServer(uint8_t server, uint16_t reg, uint16_t data)
{
    const uint8_t SEND_LEN = 8;
    uint8_t sendMsg[SEND_LEN] = {0};
    sendMsg[0] = server;
    sendMsg[1] = 0x06;
    sendMsg[2] = (uint8_t)(reg >> 8);
    sendMsg[3] = (uint8_t)reg;
    sendMsg[4] = (uint8_t)(data >> 8);
    sendMsg[5] = (uint8_t)data;

    uint16_t crc = ModRTU_CRC(sendMsg, SEND_LEN - 2);
    sendMsg[6] = (uint8_t)(crc >> 8);
    sendMsg[7] = (uint8_t)crc;

    send(sendMsg, SEND_LEN);
   // printf("Sent request:  ");
    printMsg(sendMsg, SEND_LEN);
    usleep(100000);

    const uint8_t RECEIVE_LEN = 8;
    uint8_t receiveMsg[RECEIVE_LEN] = {0};
    if(receive(receiveMsg, RECEIVE_LEN) < 0)
    {
        perror("No message received!\n");
        return;
    }
   // printf("Received reply:");
    printMsg(receiveMsg, RECEIVE_LEN);

    for(uint8_t i = 0; i < RECEIVE_LEN; i++)
    {
        if(receiveMsg[i] != sendMsg[i])
        {
            perror("Received message invalid!\n");
            return;
        }
    }
}

int32_t ModbusClient::receive(uint8_t* msg, uint8_t len)
{
    if(read(mFile, msg, len) < 0)
    {
        perror("Failed to read from the input!\n");
        return -1;
    }
    return 0;
}

void ModbusClient::send(uint8_t* msg, uint8_t len)
{
    if (write(mFile, msg, len) < 0)
    {
        perror("Failed to write to the output!\n");
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
        sprintf(&buffer[i * 3], " %02X", msg[i]);
    }
   // printf("%s\n", buffer);
}

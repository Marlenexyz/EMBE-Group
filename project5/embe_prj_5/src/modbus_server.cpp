#include "modbus_server.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

ModbusServer::ModbusServer()
{

}

ModbusServer::~ModbusServer()
{

}

void ModbusServer::init(uint8_t serverNr, uint32_t baudrate)
{
    mServerNr = serverNr;

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
    options.c_cc[VTIME] = 1;
    // min number of bytes
    options.c_cc[VMIN] = 8;

    tcflush(mFile, TCIFLUSH);
    tcsetattr(mFile, TCSANOW, &options);
    
    closeUart();

    mServerRegister[5] = 0x000F;
}

void ModbusServer::openUart()
{
    if((mFile = open("/dev/ttyS0", O_RDWR | O_NOCTTY)) < 0) // maybe needs: O_NDELAY
    {
        perror("Failed to open the file!\n");
        return;
    }
}

void ModbusServer::closeUart()
{
    close(mFile);
}

void ModbusServer::handleRequest()
{
    uint8_t receiveMsg[8] = {0};
    if(receive(receiveMsg, sizeof(receiveMsg)) < 0)
    {
        perror("No message received!\n");
        return;
    }

    printf("Received message: ");
    printMsg(receiveMsg, sizeof(receiveMsg));
    printf("\n");
    
    uint16_t recCrc = (receiveMsg[6] << 8) | receiveMsg[7];
    uint16_t calcCrc = ModRTU_CRC(receiveMsg, sizeof(receiveMsg) - 2);
    if(recCrc != calcCrc)
    {
        perror("CRC check failure!\n");
        return;
    }
    if(receiveMsg[0] != mServerNr)
    {
        perror("Received message invalid!\n");
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
        sendMsg[3] = (uint8_t)(data << 8);
        sendMsg[4] = (uint8_t)data;

        uint16_t crc = ModRTU_CRC(sendMsg, sizeof(sendMsg) - 2);
        sendMsg[5] = (uint8_t)(crc << 8);
        sendMsg[6] = (uint8_t)crc;

        printf("reg: %d, data: %d\n", reg, data);
        send(sendMsg, sizeof(sendMsg));

        printf("Sent message: ");
        printMsg(sendMsg, sizeof(sendMsg));
        printf("\n");
    }
    else if(receiveMsg[1] == 0x06)
    {
        // handle write
        uint16_t reg = (receiveMsg[2] << 8) | receiveMsg[3];
        uint16_t data = (receiveMsg[4] << 8) | receiveMsg[5];
        mServerRegister[reg] = data;

        printf("reg: %d, data: %d\n", reg, data);
        send(receiveMsg, sizeof(receiveMsg));

        printf("Sent message: ");
        printMsg(receiveMsg, sizeof(receiveMsg));
        printf("\n");
    }
}


int32_t ModbusServer::receive(uint8_t* msg, uint8_t len)
{
    if(read(mFile, msg, len) < 0)
    {
        perror("Failed to read from the input!\n");
        return -1;
    }
    return 0;
}

void ModbusServer::send(uint8_t* msg, uint8_t len)
{
    if (write(mFile, msg, len) < 0)
    {
        perror("Failed to write to the output!\n");
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
    for(uint8_t i; i < len; i++)
    {
        printf("%02X", msg[i]);
    }
}

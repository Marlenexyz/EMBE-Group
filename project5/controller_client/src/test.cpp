#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include "modbus_client.h"

ModbusClient modbus;

int main(int argc, char** argv)
{
   if(argc != 5)
   {
       printf("Invalid number of arguments, exiting!\n");
       return -2;
   }

    modbus.init(9600);
    modbus.openUart();

    uint8_t server = atoi(argv[1]);
    uint8_t fnct = atoi(argv[2]);
    uint16_t reg = atoi(argv[3]);
    uint16_t data = 0;

    if(fnct == 0x03)
    {
        modbus.readServer(server, reg, &data);
    }
    else if(fnct == 0x06)
    {
        data = atoi(argv[4]);
        modbus.writeServer(server, reg, data);
    }
    else
    {
        perror("False function set, set 3 for read or 6 for write.\n");
    }
    
    modbus.closeUart();
    return 0;
}
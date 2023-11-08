#include <stdint.h>
#include <unistd.h>
#include "modbus_server.h"

ModbusServer modbus;

int main()
{
    modbus.init(0x01, 9600);

    while(1)
    {
        modbus.openUart();
        modbus.handleRequest();
        // modbus.closeUart();
        sleep(1);
    }
    return 0;
}
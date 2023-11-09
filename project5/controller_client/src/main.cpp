#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include "modbus_client.h"

ModbusClient modbus;

int main(int argc, char** argv)
{
    modbus.init(9600);
    modbus.openUart();

    while(1)
    {
        uint16_t = data = 0xFFFF;
        modbus.readServer(0x01, 0x0000, &data);
        printf("data read from server 0x01: %d\n", data);

        if(data == 0x0082)
        {
            // std::system("sudo reboot");
        }
        
        modbus.writeServer(0x02, 0x0000, data);
        sleep(5);
    }
    
    // modbus.closeUart();

    return 0;
}
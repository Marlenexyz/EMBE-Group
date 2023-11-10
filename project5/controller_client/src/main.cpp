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
        uint16_t data = 0;
        modbus.readServer(0x01, 0x0000, &data);
        if(data == 0x0082)
        {
            // std::system("sudo reboot");
        }
        usleep(1000);

        int16_t omegaRef = 0;
        modbus.readServer(0x01, 0x0001, reinterpret_cast<uint16_t*>(&omegaRef));
        usleep(1000);
        
        modbus.writeServer(0x02, 0x0000, data);
        usleep(1000);
        
        modbus.writeServer(0x02, 0x0001, omegaRef);
        usleep(1000);
        
        int16_t omega = 0;
        modbus.readServer(0x02, 0x0002, reinterpret_cast<uint16_t*>(&omega));
        usleep(1000);

        printf("w_ref: %.2f, w: %.2f\n", static_cast<float>(omegaRef) / 100.0f, static_cast<float>(omega) / 100.0f);
    }
    
    // modbus.closeUart();

    return 0;
}
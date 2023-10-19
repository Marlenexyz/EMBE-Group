#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string>

#include "controller.h"

// VERY IMPORTANT DEFINES

static const int UPDATE_RATE_US = 3000;
static const double REF_RPS = 1.0;


Controller controller(1.419, 0.796);

int main()
{
    //Enable gpio pin18 PWM
    int fd = open("/sys/class/pwm/pwmchip0/export", O_WRONLY);       //??
    write(fd,"0",1);
    close(fd);

    fd = open("/sys/class/pwm/pwmchip0/pwm0/period", O_WRONLY);
    write(fd,"1000000",7);
    close(fd);

    fd = open("/sys/class/pwm/pwmchip0/pwm0/duty_cycle", O_WRONLY);
    write(fd,"1000000",7);
    close(fd);

    fd = open("/sys/class/pwm/pwmchip0/pwm0/enable", O_WRONLY);
    write(fd,"1",1);
    close(fd);

    fd = open("/sys/class/pwm/pwmchip0/unexport", O_WRONLY);
    write(fd, "18", 2);
    close(fd);

     // Set gpio18 as output
    int fd_direction = open("/sys/class/gpio/gpio18/direction", O_WRONLY);
    write(fd_direction, "out", 3);
    close(fd_direction);

    // Enable gpio23
    int fd_out = open("/sys/class/gpio/export", O_WRONLY);
    write(fd_out, "23", 2);
    close(fd_out);

    // Enable gpio24
    fd_out = open("/sys/class/gpio/export", O_WRONLY);
    write(fd_out, "24", 2);
    close(fd_out);

    // Set gpio23 as output
    fd_out = open("/sys/class/gpio/gpio23/direction", O_WRONLY);
    write(fd_out, "out", 3);
    close(fd_out);

    // Set gpio24 as output
    fd_out = open("/sys/class/gpio/gpio24/direction", O_WRONLY);
    write(fd_out, "out", 3);
    close(fd_out);

    int lastCnt;
    int newCnt;

    while (1)
    {
        // update the control values with the set update rate
        usleep(UPDATE_RATE_US);

        fd = open("/sys/kernel/test/number_presses", O_RDONLY);
        if (fd < 0)
        {
            perror("Error opening sysfs file");
            return 1;
        }

        char buffer[32];
        ssize_t bytesRead = read(fd, buffer, sizeof(buffer));
        close(fd);

        if (bytesRead > 0)
        {
            buffer[bytesRead] = '\0';
            newCnt = std::stoi(buffer);

            // calculate the counter difference and the resulting RPS
            int diffCnt = lastCnt - newCnt;
            double actRps = diffCnt / (700 * UPDATE_RATE_US / 1000000);
            
            // update the control values
            double duty = controller.update(REF_RPS, actRps);
            int dutyPeriod = 1000000 * duty;

            if (dutyPeriod == 0)
            {
                fd_out = open("/sys/class/gpio/gpio23/value", O_WRONLY);
                write(fd_out, "0", 1);
                close(fd_out);

                fd_out = open("/sys/class/gpio/gpio24/value", O_WRONLY);
                write(fd_out, "0", 1);
                close(fd_out);
            }
            if (dutyPeriod > 0)
            {
                fd_out = open("/sys/class/gpio/gpio23/value", O_WRONLY);
                write(fd_out, "1", 1);
                close(fd_out);

                fd_out = open("/sys/class/gpio/gpio24/value", O_WRONLY);
                write(fd_out, "0", 1);
                close(fd_out);

                std::string dutyStr = std::to_string(dutyPeriod).c_str();
                fd = open("/sys/class/pwm/pwmchip0/pwm0/duty_cycle", O_WRONLY);
                write(fd, dutyStr.c_str(), dutyStr.length());
                close(fd);
            }
            else if (dutyPeriod < 0)
            {
                fd_out = open("/sys/class/gpio/gpio23/value", O_WRONLY);
                write(fd_out, "0", 1);
                close(fd_out);

                fd_out = open("/sys/class/gpio/gpio24/value", O_WRONLY);
                write(fd_out, "1", 1);
                close(fd_out);
                
                std::string dutyStr = std::to_string(-dutyPeriod).c_str();
                fd = open("/sys/class/pwm/pwmchip0/pwm0/duty_cycle", O_WRONLY);
                write(fd, dutyStr.c_str(), dutyStr.length());
                close(fd);
            }
            // printf("Number of Presses: %s\n", buffer);
        }
        else
        {
            perror("Error reading sysfs file");
        }
    }


    int fd_unexport = open("/sys/class/gpio/unexport", O_WRONLY);
    write(fd_unexport, "23", 2);
    close(fd_unexport);

    fd_unexport = open("/sys/class/gpio/unexport", O_WRONLY);
    write(fd_unexport, "24", 2);
    close(fd_unexport);

    fd_unexport = open("/sys/class/pwm/pwmchip0/unexport", O_WRONLY);
    write(fd_unexport, "18", 2);
    close(fd_unexport);

    return 0;
}

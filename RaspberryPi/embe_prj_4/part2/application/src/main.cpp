#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string>

#include "p_controller.h"
#include "pi_controller.h"

/********* VERY IMPORTANT DEFINES **********/
static const int UPDATE_RATE_US = 3000;
static const double REF_RPS = 1.0;

P_Controller controller(1.429, 0.784);
// PI_Controller controller(1.429, 0.784, 25, 2000);



/************** MAIN LOOP ***************/
int main()
{
    // export pwm on pin18
    int fd = open("/sys/class/pwm/pwmchip0/export", O_WRONLY);
    write(fd, "0", 1);
    close(fd);

    // set period of pwm to 1000000 ns
    fd = open("/sys/class/pwm/pwmchip0/pwm0/period", O_WRONLY);
    write(fd, "1000000", 7);
    close(fd);

    // set duty cycle of pwm to 100%
    fd = open("/sys/class/pwm/pwmchip0/pwm0/duty_cycle", O_WRONLY);
    write(fd, "1000000", 7);
    close(fd);

    // enable pwm
    fd = open("/sys/class/pwm/pwmchip0/pwm0/enable", O_WRONLY);
    write(fd, "1", 1);
    close(fd);
    
     // set pwm (pin18) as output
    fd = open("/sys/class/gpio/gpio18/direction", O_WRONLY);
    write(fd, "out", 3);
    close(fd);

    // export gpio on pin23
    fd = open("/sys/class/gpio/export", O_WRONLY);
    write(fd, "23", 2);
    close(fd);

    // export gpio on pin24
    fd = open("/sys/class/gpio/export", O_WRONLY);
    write(fd, "24", 2);
    close(fd);

    // set gpio (pin23) as output
    fd = open("/sys/class/gpio/gpio23/direction", O_WRONLY);
    write(fd, "out", 3);
    close(fd);

    // set gpio (pin24) as output
    fd = open("/sys/class/gpio/gpio24/direction", O_WRONLY);
    write(fd, "out", 3);
    close(fd);

    // define count variable before loop
    int lastCnt = 0;
    int newCnt = 0;
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
            lastCnt = newCnt;
            newCnt = std::atoi(buffer);

            // calculate the counter difference and the resulting RPS
            int diffCnt = newCnt - lastCnt;
            double actRps = static_cast<double>(diffCnt) / (700.0d * UPDATE_RATE_US / 1000000.0d);
            
            // update the control values
            double duty = controller.update(REF_RPS, actRps);

            printf("ref. rps: %f, act. rps: %f, duty: %f\n", REF_RPS, actRps, duty);

            int dutyPeriod = duty * 1000000;

            if (dutyPeriod == 0)
            {
                fd = open("/sys/class/gpio/gpio23/value", O_WRONLY);
                write(fd, "0", 1);
                close(fd);

                fd = open("/sys/class/gpio/gpio24/value", O_WRONLY);
                write(fd, "0", 1);
                close(fd);
            }
            if (dutyPeriod > 0)
            {
                fd = open("/sys/class/gpio/gpio23/value", O_WRONLY);
                write(fd, "1", 1);
                close(fd);

                fd = open("/sys/class/gpio/gpio24/value", O_WRONLY);
                write(fd, "0", 1);
                close(fd);

                std::string dutyStr = std::to_string(dutyPeriod).c_str();
                fd = open("/sys/class/pwm/pwmchip0/pwm0/duty_cycle", O_WRONLY);
                write(fd, dutyStr.c_str(), dutyStr.length());
                close(fd);
            }
            else if (dutyPeriod < 0)
            {
                fd = open("/sys/class/gpio/gpio23/value", O_WRONLY);
                write(fd, "0", 1);
                close(fd);

                fd = open("/sys/class/gpio/gpio24/value", O_WRONLY);
                write(fd, "1", 1);
                close(fd);
                
                std::string dutyStr = std::to_string(-dutyPeriod).c_str();
                fd = open("/sys/class/pwm/pwmchip0/pwm0/duty_cycle", O_WRONLY);
                write(fd, dutyStr.c_str(), dutyStr.length());
                close(fd);
            }
        }
        else
        {
            perror("Error reading sysfs file");
        }
    }

    // unexport gpio on pin23
    fd = open("/sys/class/gpio/unexport", O_WRONLY);
    write(fd, "23", 2);
    close(fd);

    // unexport gpio on pin24
    fd = open("/sys/class/gpio/unexport", O_WRONLY);
    write(fd, "24", 2);
    close(fd);

    // unexport pwm on pin18
    fd = open("/sys/class/pwm/pwmchip0/unexport", O_WRONLY);
    write(fd, "18", 2);
    close(fd);

    return 0;
}

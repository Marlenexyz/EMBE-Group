#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {

    //Enable gpio pin18 PWM
    int fd = open("/sys/class/pwm/pwmchip0/export", O_WRONLY);       //??
    write(fd,"0",1);
    close(fd);

    fd = open("/sys/class/pwm/pwmchip0/pwm0/period", O_WRONLY);
    write(fd,"100000",6);
    close(fd);

    fd = open("/sys/class/pwm/pwmchip0/pwm0/duty_cycle", O_WRONLY);
    write(fd,"20000",5);
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
    fd_out = open("/sys/class/gpio/export", O_WRONLY);
    write(fd_out, "23", 2);
    close(fd_out);

    // Enable gpio23
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




    while (1) {
        fd = open("/sys/kernel/test/number_presses", O_RDONLY);     //int fd
        if (fd < 0) {
            perror("Error opening sysfs file");
            return 1;  // Beenden Sie das Programm im Fehlerfall
        }

        char buffer[32];  // Ausreichend großer Puffer für die Zahl
        ssize_t bytesRead = read(fd, buffer, sizeof(buffer));
        close(fd);

        if (bytesRead > 0) {
            buffer[bytesRead] = '\0';  // Nullterminierung, um die Zeichenfolge zu beenden
            printf("Number of Presses: %s\n", buffer);
        } else {
            perror("Error reading sysfs file");
        }

        sleep(5);  // Warten Sie eine Weile, bevor Sie erneut lesen
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

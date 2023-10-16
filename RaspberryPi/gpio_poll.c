#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Enable gpio17
    int fd_in = open("/sys/class/gpio/export", O_WRONLY);
    write(fd_in, "17", 2);
    close(fd_in);

    // Enable gpio22
    int fd_out = open("/sys/class/gpio/export", O_WRONLY);
    write(fd_out, "22", 2);
    close(fd_out);

    // Set gpio17 as input
    int fd_direction = open("/sys/class/gpio/gpio17/direction", O_WRONLY);
    write(fd_direction, "in", 2);
    close(fd_direction);

    // Set gpio22 as output
    fd_out = open("/sys/class/gpio/gpio22/direction", O_WRONLY);
    write(fd_out, "out", 3);
    close(fd_out);

    // Set gpio17 edge to rising (you can choose 'falling' if needed)
    int fd_edge = open("/sys/class/gpio/gpio17/edge", O_WRONLY);
    write(fd_edge, "both", 4);
    close(fd_edge);

    struct pollfd pfd;
    fd_in = open("/sys/class/gpio/gpio17/value", O_RDONLY);

    pfd.fd = fd_in;
    pfd.events = POLLPRI;

    for (int i = 0; i < 10000; i++) {
        // Wait for event
        lseek(fd_in, 0, SEEK_SET);
        int ret = poll(&pfd, 1, 5000);

        if (ret < 0) {
            perror("poll");
            break;
        } else if (ret == 0) {
            printf("Timeout\n");
        } else {
            char c;
            lseek(fd_in, 0, SEEK_SET);
            read(fd_in, &c, 1);

            if (c == '1'){
                printf("Push\n");
                fd_out = open("/sys/class/gpio/gpio22/value", O_WRONLY);
                write(fd_out, &c, 1);
                close(fd_out);
            }
            else{
                printf("Release\n");
                fd_out = open("/sys/class/gpio/gpio22/value", O_WRONLY);
                write(fd_out, &c, 1);
                close(fd_out);
            }
        }
    }

    // Disable gpio17
    int fd_unexport = open("/sys/class/gpio/unexport", O_WRONLY);
    write(fd_unexport, "17", 2);
    close(fd_unexport);

    // Disable gpio22
    fd_unexport = open("/sys/class/gpio/unexport", O_WRONLY);
    write(fd_unexport, "22", 2);
    close(fd_unexport);

    close(fd_in);

    return 0;
}

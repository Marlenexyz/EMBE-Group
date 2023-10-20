#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include <stdio.h>

int main()
{
    //Enable gpio17
    int fd_in = open("/sys/class/gpio/export", O_WRONLY);
    write(fd_in, "17", 2);
    close(fd_in);

    //Enable gpio22
    int fd_out = open("/sys/class/gpio/export", O_WRONLY);
    write(fd_out, "22", 2);
    close(fd_out);

    //Set gpio17 as input
    fd_in = open("/sys/class/gpio/gpio17/direction", O_WRONLY);
    write(fd_in, "in", 2);
    close(fd_in);

    //Set gpio22 as output
    fd_out = open("/sys/class/gpio/gpio22/direction", O_WRONLY);
    write(fd_out, "out", 3);
    close(fd_out);

    // //Set gpio17 interrupt
    // fd_in = open("/sys/class/gpio/gpio17/edge", O_WRONLY);
    // //write(fd_in, "falling", 7);
    // write(fd_in, "both", 4);
    // close(fd_in);

    // struct pollfd_in pfd_in;
    // pfd_in.fd_in = fd_in;
    // pfd_in.events = POLLPRI;

    while (1)
    {
        sleep (0.0001);
        //Wait for event
        fd_in = open("/sys/class/gpio/gpio17/value", O_RDONLY);       
        // int ret = poll(&pfd_in, 1, 3000);
        char c;
        read(fd_in, &c, 1);
        close(fd_in);
        // if(ret == 0)
        //     printf("Timeout\n");
        // else
            
            fd_out = open("/sys/class/gpio/gpio22/value", O_WRONLY);
            write(fd_out, &c, 1);
            close(fd_out);
    }

    //Disable gpio17
    fd_in = open("/sys/class/gpio/unexport", O_WRONLY);
    write(fd_in, "17", 2);
    close(fd_in);
    fd_out = open("/sys/class/gpio/unexport", O_WRONLY);
    write(fd_out, "22", 2);
    close(fd_out);

    return(0);
}



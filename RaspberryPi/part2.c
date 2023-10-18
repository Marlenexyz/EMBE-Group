#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    while (1) {
        int fd = open("/sys/kernel/test/number_presses", O_RDONLY);
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
    return 0;
}

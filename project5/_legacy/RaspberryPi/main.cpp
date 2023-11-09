#include <iostream>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <cstring>

int main() {
    int serialPort = open("/dev/ttyS0", O_RDWR | O_NOCTTY);
    if (serialPort == -1) {
        std::cerr << "Fehler beim Öffnen der seriellen Schnittstelle." << std::endl;
        return 1;
    }

    struct termios tty;
    memset(&tty, 0, sizeof(tty));

    if (tcgetattr(serialPort, &tty) != 0) {
        std::cerr << "Fehler beim Lesen der seriellen Schnittstellenattribute." << std::endl;
        return 1;
    }

    tty.c_cflag = B9600 | CS8 | CREAD | CLOCAL;  // Baudrate und 8-Bit-Daten
    tty.c_iflag = 0;
    tty.c_oflag = 0;
    tty.c_lflag = 0;
    tty.c_cc[VMIN] = 1;
    tty.c_cc[VTIME] = 5;

    if (tcsetattr(serialPort, TCSANOW, &tty) != 0) {
        std::cerr << "Fehler beim Setzen der seriellen Schnittstellenattribute." << std::endl;
        return 1;
    }

    std::cout << "Serielle Schnittstelle geöffnet." << std::endl;

    while (true) {
        std::string data_to_send;
        std::cout << "Gib eine Nachricht ein: ";
        std::cin >> data_to_send;

        write(serialPort, data_to_send.c_str(), data_to_send.length());

        usleep(1000000); // Warte eine Sekunde

        char receivedChar;
        while (read(serialPort, &receivedChar, 1) > 0) {
            std::cout << receivedChar << std::endl;
        }
    }

    close(serialPort);
    return 0;
}




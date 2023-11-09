#include <Arduino.h>

class cmodbus {
public:
    cmodbus(HardwareSerial& serial) : serial_(serial) {}

    // Funktion zum Lesen von Daten
    bool read() {
        char buffer[14]; // 2 (Serveradresse) + 2 (Funktion) + 4 (Register) + 4 (Anzahl der Register) + 2 (CRC)
        if (readBytes(buffer, sizeof(buffer)) != sizeof(buffer)) {
            return false; // Nicht genügend Daten erhalten
        }

        server_ = parseHex(buffer, 2);
        function_ = parseHex(buffer + 2, 2);
        regi_ = parseHex(buffer + 4, 4);
        numreg_ = parseHex(buffer + 8, 4);
        crc_ = parseHex(buffer + 12, 2);

        // Weitere Verarbeitung, z.B. Antwort senden oder Daten verarbeiten

        Serial.println(server_);
        return true;
    }

    // Funktion zum Schreiben von Daten
    bool write() {
        char buffer[16]; // 2 (Serveradresse) + 2 (Funktion) + 4 (Register) + 4 (Wert) + 2 (CRC)
        if (readBytes(buffer, sizeof(buffer)) != sizeof(buffer)) {
            return false; // Nicht genügend Daten erhalten
        }

        server_ = parseHex(buffer, 2);
        function_ = parseHex(buffer + 2, 2);
        regi_ = parseHex(buffer + 4, 4);
        value_ = parseHex(buffer + 8, 4);
        crc_ = parseHex(buffer + 12, 2);

        // Weitere Verarbeitung, z.B. Register schreiben oder Bestätigung senden
        return true;
    }

private:
    HardwareSerial& serial_;
    uint16_t server_;
    uint16_t function_;
    uint32_t regi_;
    uint32_t numreg_;
    uint32_t value_;
    uint16_t crc_;

    // Funktion zum Lesen von Bytes aus dem Serial-Port
    size_t readBytes(char* buffer, size_t length) {
        size_t bytesRead = 0;
        while (bytesRead < length) {
            if (serial_.available()) {
                buffer[bytesRead] = serial_.read();
                bytesRead++;
            }
        }
        return bytesRead;
    }

    // Funktion zum Konvertieren von Hexadezimal-String in Ganzzahl
    uint32_t parseHex(const char* str, size_t length) {
        uint32_t result = 0;
        for (size_t i = 0; i < length; i++) {
            result <<= 4;
            char c = str[i];
            if (c >= '0' && c <= '9') {
                result += c - '0';
            } else if (c >= 'A' && c <= 'F') {
                result += c - 'A' + 10;
            } else if (c >= 'a' && c <= 'f') {
                result += c - 'a' + 10;
            } else {
                // Unerwartetes Zeichen
                return 0;
            }
        }
        return result;
    }
};

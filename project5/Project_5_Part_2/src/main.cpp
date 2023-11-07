#include<Arduino.h>
#include<modbus.h>



void setup() {
    Serial.begin(9600);
    
}
char message[100];
int count=0;
boolean shit=true;
modbus versuch(1);
// Nachricht ohne leerzeichen
void loop() {
  while(count<20){
    
    while (Serial.available() > 0) {
        char receivedChar = Serial.read(); //readbytes
        message[count] = receivedChar;
        count=count+1; 
        }

  if (Serial.available()==0){
    // if (count >= 1 && count <= 13&&shit)
    // {
    //   Serial.print("Transport error, message too short");
    //   shit=false;
      
    // }
    
    if(shit && count>=16){
        versuch.recieve(message,strlen(message));
        shit=false;                  
    }
    }
  }

}



 
// Funktion zum Konvertieren von Hexadezimal-String in Ganzzahl
uint32_t ModbusClient::parseHex(const char* str, size_t length) {
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

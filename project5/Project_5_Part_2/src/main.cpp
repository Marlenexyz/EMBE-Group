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





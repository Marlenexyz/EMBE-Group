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
        char receivedChar = Serial.read();
        message[count] = receivedChar;
        //Serial.print(message[count]);
        //Serial.print("Counter Value: ");
        //Serial.println(count);
        count=count+1; 
        }

  if (Serial.available()==0){
    if (shit&&count >= 1 && count <= 13)
    {
      Serial.print("Transport error, message too short");
      shit=false;
      
    }
    
    if(shit && count>=14){
        versuch.read(message,strlen(message));
        //int bla = versuch.read(message,strlen(message));
        //Serial.print("in read kam raus: "+bla);
        shit=false;                  
    
      if (message[3]==3)
        {
          Serial.println("In der read if");
          int bla = versuch.read(message,strlen(message));
          Serial.print("in read kam raus: "+bla);

        }
        else if (message[2]=='0' && message[3]=='6')
        {
          versuch.write(message,strlen(message));
        }

    }
    }
  }

}





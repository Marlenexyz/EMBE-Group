#include <Arduino.h>
#include "modbus_server.h"

#define uint16_t registerNr= 0;    //RegisterNr anpassen

ModbusServer modbus;

int sensorPin = A0; 
const int opPin = 'D2';   //D2 - D7
const int stopPin = 'D3';
const int preOpPin = 'D4';
const int comPin = 'D5';

char buffer[10];



void setup() 
{
  Serial.begin(9600);
  modbus.init(0x01, 9600);    //Server Nr, Baudrate
  pinMode(opPin, INPUT);
  pinMode(stopPin, INPUT);
  pinMode(preOpPin, INPUT);
  pinMode(comPin, INPUT);
}

void loop() 
{
  // modbus.handleRequest();

  // command = Serial.read();
  int sensorValue = analogRead(sensorPin);

  sprintf(buffer,"%d\n",sensorValue);
  Serial.print(buffer);
  
  if (digitalRead(opPin))
  {
    modbus.setReg(registerNr,0x01)
  }
  else if (digitalRead(stopPin))
  {
    modbus.setReg(registerNr,0x02)
  }
  else if (digitalRead(preOpPin))
  {
    modbus.setReg(registerNr,0x80)
  }
  else if (digitalRead(comPin)){
    modbus.setReg(registerNr,0x82)
  }
  
}

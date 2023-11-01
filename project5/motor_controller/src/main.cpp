#include <Arduino.h>

const int m1 = 5;
const int m2 = 6;
char data[4] = {0};

void setup()
{
	Serial.begin(115200);

	pinMode(m1, OUTPUT);
	pinMode(m2, OUTPUT);
}

void loop()
{
	if (Serial.available() > 0)
	{
		Serial.readBytes(data, 4);
		Serial.println((int)*data);

		analogWrite(m1, atoi(data));
		digitalWrite(m2, false);
	}
}


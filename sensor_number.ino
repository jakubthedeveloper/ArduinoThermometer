// Sensor serial number reader for DS18B20

#include <OneWire.h>

// Digital sensor pin number where the DS18B20 sensor is connected
const byte ONEWIRE_PIN = 2;

OneWire onewire(ONEWIRE_PIN);

void setup()
{
  while(!Serial);
  Serial.begin(9600);
}

void loop()
{
  byte address[8];

  onewire.reset_search();
  while(onewire.search(address))
  {
    if (address[0] != 0x28)
      continue;

    if (OneWire::crc8(address, 7) != address[7])
    {
      Serial.println(F("Incorrect address, check connections."));
      break;
    }

    for (byte i=0; i<8; i++)
    {
      Serial.print(F("0x"));
      Serial.print(address[i], HEX);

      if (i < 7)
        Serial.print(F(", "));
    }
    Serial.println();
  }

  while(1);
}

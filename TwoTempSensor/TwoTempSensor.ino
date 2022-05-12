#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 4

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

int deviceCount = 0;
float Celcius = 0;
float Fahrenheit = 0;

void setup()
{
  pinMode(5, OUTPUT);
  digitalWrite(5, HIGH);
  sensors.begin();
  Serial.begin(9600);
  Serial.print("Locating devices...");
  Serial.print("Found ");
  deviceCount = sensors.getDeviceCount();
  Serial.print(deviceCount, DEC);
  Serial.println(" devices.");
  Serial.println("");
}

void loop()
{

  sensors.requestTemperatures();
  delay(1000);

  for (int i = 0; i < deviceCount; i++)
  {
    Celcius = sensors.getTempCByIndex(i);
    Fahrenheit = sensors.toFahrenheit(Celcius);
    Serial.print(Fahrenheit);
    Serial.print(" ");
  }
  Serial.println("");
  delay(5000);
}

#include <LowPower.h>
#include <SPI.h>
#include "RF24.h"
#include <OneWire.h>
#include <DallasTemperature.h>

#define PWR_CONTROLLER_DONE 3
#define ONE_WIRE_BUS 4
#define SENSOR_POWER 5
#define RADIO_POWER 6

// Init for Temp Sensors
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
int deviceCount = 0;
float Celcius = 0;
float Fahrenheit = 0;
float tempList[5] = {};

// Init for transmitter
bool radioNumber = 0;
RF24 radio(9, 10); // radio(CE_pin, CSN_pin)
byte addresses[][6] = {"1Node", "2Node"};

void setup()
{
  Serial.begin(9600);
  Serial.println(F("RF24/examples/GettingStarted"));
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(3, OUTPUT);
  digitalWrite(6, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(3, LOW);

  // Setup of radio
  radio.begin();
  radio.setPALevel(RF24_PA_MIN); // RF24_PA_MAX is default. _MIN for testing
                                 //  radio.setDataRate(RF24_250KBPS);
  radio.setRetries(15, 15);
  radio.openWritingPipe(addresses[0]);
  radio.openReadingPipe(1, addresses[1]);
  radio.startListening();

  // Setup for Temp Sensors
  sensors.begin();
  Serial.print("Locating devices...");
  Serial.print("Found ");
  deviceCount = sensors.getDeviceCount();
  Serial.print(deviceCount, DEC);
  Serial.println(" devices.");
  Serial.println("");
}

void updateTemp()
{
  //  sensors.begin();
  delay(100);
  sensors.requestTemperatures();
  delay(100);

  for (int i = 0; i < deviceCount; i++)
  {
    Celcius = sensors.getTempCByIndex(i);
    Fahrenheit = sensors.toFahrenheit(Celcius);
    tempList[i] = Fahrenheit;
  }
  //  digitalWrite(5, LOW);
}

void loop()
{

  unsigned long start_time = micros();
  updateTemp();
  Serial.print(F("Now sending: "));
  for (int i = 0; i < deviceCount; i++)
  {
    Serial.print(tempList[i]);
    Serial.print(" ");
  }
  Serial.println("");

  radio.stopListening(); // First, stop listening so we can talk.
  delay(2000);

  if (!radio.write(&tempList, sizeof(tempList)))
  {
    Serial.println(F("Write failed."));
  }

  delay(2000);

  radio.startListening();  // Now, continue listening
  boolean timeout = false; // Set up a variable to indicate if a response was received or not

  while (!radio.available())
  { // While nothing is received
    if (micros() - start_time > 5000000)
    { // If waited longer than 200ms, indicate timeout and exit while loop
      timeout = true;
      break;
    }
  }

  if (timeout)
  { // Describe the results
    Serial.println(F("Failed, response timed out."));
  }
  else
  {
    unsigned long got_time; // Grab the response, compare, and send to debugging spew
    radio.read(&tempList, sizeof(tempList));
    unsigned long end_time = micros();

    // Spew it
    Serial.print(F("Got response "));
    for (int i = 0; i < deviceCount; i++)
    {
      Serial.print(tempList[i]);
      Serial.print(" ");
    }
    Serial.println("");
    Serial.print(F("Round-trip delay "));
    Serial.print(end_time - start_time);
    Serial.println(F(" microseconds"));
  }
  delay(1000);
  delay(10000);
  digitalWrite(3, HIGH);
  //    digitalWrite(6, LOW); //For testing comment these two lines out
  //    digitalWrite(5, LOW); //

} // Loop

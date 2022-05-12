#include <LowPower.h>
#include <SPI.h>
#include "RF24.h"
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 4

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
  digitalWrite(6, HIGH);
  digitalWrite(5, HIGH);

  // Setup of radio
  radio.begin();
  radio.setPALevel(RF24_PA_LOW); // RF24_PA_MAX is default.
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

void radioOn()
{
  radio.begin();
  radio.setPALevel(RF24_PA_LOW); // RF24_PA_MAX is default.
  radio.setRetries(15, 15);
  radio.openWritingPipe(addresses[0]);
  radio.openReadingPipe(1, addresses[1]);
  radio.startListening();
  delay(1000);
}

void updateTemp()
{
  sensors.begin();
  delay(100);
  sensors.requestTemperatures();
  delay(100);

  for (int i = 0; i < deviceCount; i++)
  {
    Celcius = sensors.getTempCByIndex(i);
    Fahrenheit = sensors.toFahrenheit(Celcius);
    tempList[i] = Fahrenheit;
  }
  // float r = random(1000) / 100;
  // tempList[2] = r;
  /*Receiver will not take messages that are the exact same back to back. Could send
    a random number with each message to get every message sent. But can probably
    just interpret that where ever this data will be used.
  */
}

void loop()
{

  digitalWrite(6, HIGH);
  digitalWrite(5, HIGH);
  delay(1000);
  radioOn();
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

  if (!radio.write(&tempList, sizeof(tempList)))
  {
    Serial.println(F("Write failed."));
  }

  radio.startListening();  // Now, continue listening
  boolean timeout = false; // Set up a variable to indicate if a response was received or not

  while (!radio.available())
  { // While nothing is received
    if (micros() - start_time > 2000000)
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
  digitalWrite(6, LOW);
  digitalWrite(5, LOW);

  //    delay(10000); //Testing
  for (int i = 0; i < 111; i++)
  { // 111
    LowPower.idle(SLEEP_8S, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF,
                  SPI_OFF, USART0_OFF, TWI_OFF);
  }

} // Loop

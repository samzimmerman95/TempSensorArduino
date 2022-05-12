#include <SPI.h>
#include "RF24.h"

bool radioNumber = 0;

// radio(CE_pin, CSN_pin)
RF24 radio(9, 10);

byte addresses[][6] = {"1Node", "2Node"};

// Used to control whether this node is sending or receiving
bool role = 1;

struct dataStruct
{
  unsigned long m1;
  unsigned long m2;
} myData;

void setup()
{
  Serial.begin(9600);
  Serial.println(F("RF24/examples/GettingStarted"));

  radio.begin();

  // likelihood of close proximity of the devices. RF24_PA_MAX is default.
  radio.setPALevel(RF24_PA_LOW);
  radio.setRetries(15, 15);

  radio.openWritingPipe(addresses[0]);
  radio.openReadingPipe(1, addresses[1]);

  radio.startListening();
}

void loop()
{

  unsigned long start_time = micros();
  myData.m1 = micros();
  myData.m2 = micros();
  Serial.print(F("Now sending: "));
  Serial.print(myData.m1);
  Serial.print(" ");
  Serial.println(myData.m2);

  radio.stopListening(); // First, stop listening so we can talk.

  if (!radio.write(&myData, sizeof(myData)))
  {
    Serial.println(F("Write failed."));
  }

  radio.startListening();  // Now, continue listening
  boolean timeout = false; // Set up a variable to indicate if a response was received or not

  while (!radio.available())
  { // While nothing is received
    if (micros() - start_time > 200000)
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
    radio.read(&myData, sizeof(myData));
    unsigned long end_time = micros();

    // Spew it
    //          Serial.print(F("Sent "));
    //          Serial.print(start_time);
    Serial.print(F("Got response "));
    Serial.print(myData.m1);
    Serial.print(" ");
    Serial.println(myData.m2);
    Serial.print(F("Round-trip delay "));
    Serial.print(end_time - start_time);
    Serial.println(F(" microseconds"));
  }

  delay(8000);

} // Loop

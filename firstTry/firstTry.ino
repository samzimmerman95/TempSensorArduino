#include <SPI.h>
#include "RF24.h"

RF24 radio(9, 10); // CE, CSN

byte addresses[][6] = {"1Node","2Node"};

int sendingNum = 0;

struct dataStruct{
  unsigned long _micros;
  float value;
}myData;

void setup() {
  Serial.begin(9600);
  Serial.println(F("firstTry"));
  
  radio.begin();
  radio.setPALevel(RF24_PA_LOW);
  radio.openWritingPipe(addresses[1]);
  // radio.stopListening();  
  myData.value = 4.5;   
}

void loop() {                    
    sendingNum++;
    myData._micros = micros();
    if (radio.write( &myData, sizeof(dataStruct) )) {
      Serial.print(F("Sent "));
    }

    
    //Serial.print(F("Sent "));
    Serial.print(myData.value );
    Serial.print(" ");
    Serial.println( myData._micros);   
    myData.value++;                            
    delay(2000);
} 

#include <ArduinoCC2500.h>
#include <CC2500.h>



 ArduinoCC2500 ar;
 
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;

// the setup routine runs once when you press reset:
void setup() {                
  ar.init();
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);     
}

// the loop routine runs over and over again forever:
void loop() {
  unsigned char dataTX[] = "HELLO";
  ar.sendData(dataTX,sizeof(dataTX));
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);    // wait for a second
  
  unsigned char *dataRX;
  ar.ReceiveData(dataRX,5);
  
  
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);               // wait for a second
}


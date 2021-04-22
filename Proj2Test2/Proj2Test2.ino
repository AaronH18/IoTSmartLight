#include <SPI.h>
#include <Ethernet.h>

char lightOn[] ="https://maker.ifttt.com/trigger/trigger/with/key/jvU6Y1ffMzHca4opHsEAXdhGXYP2KUdLenWUo2Qs025"

EthernetClient client;

void setup() {
  Bridge.begin();  // Initialize the Bridge
  Serial.begin(9600);  // Initialize the Serial

}

void loop() {
  client.connect(lightOn,80);
  delay(5000);  // wait 5 seconds before you do it again
}

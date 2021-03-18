/*
/* Grove - Light Sensor demo v1.0
*
* signal wire to A0.
* By: http://www.seeedstudio.com
* Modified: 18/03/2021 5:09pm
*/
#include <math.h>
const int ledPin=12;                 //Connect the LED Grove module to Pin12, Digital 12
const int ledPin2=11;


const int ThresValue=10; //The threshold for which the LED should turn on.
const int ThresValue1= 20; 
const int ThresValue2= 30; 


float Rsensor; //Resistance of sensor in K
void setup() {
  Serial.begin(9600);                //Start the Serial connection
  pinMode(ledPin,OUTPUT);            //Set the LED on Digital 12 as an OUTPUT
  pinMode(ledPin2,OUTPUT);
}
void loop() {
  int sensorValue = analogRead(0);
  Rsensor=(float)(1023-sensorValue)*10/sensorValue;
  if(Rsensor>ThresValue1)
  {
    digitalWrite(ledPin,HIGH);
    digitalWrite(ledPin2,LOW);
  }
  else if(Rsensor>ThresValue2)
  {
    digitalWrite(ledPin,HIGH);
    digitalWrite(ledPin2,HIGH);
  }
  else
  {
  digitalWrite(ledPin,LOW);
  digitalWrite(ledPin2,LOW);
  }
  Serial.println("the analog read data is ");
  Serial.println(sensorValue);
  Serial.println("the sensor resistance is ");
  Serial.println(Rsensor,DEC);//show the light intensity on the serial monitor;
  delay(1000);
}

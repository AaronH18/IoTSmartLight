#include <math.h>
#include <Wire.h>
#include "rgb_lcd.h"

float Rsensor;

rgb_lcd lcd;
const int colorR = 220;
const int colorG = 20;
const int colorB = 255;

#include <Process.h>

Process date;                 // process used to get the date
int hours, minutes, seconds;  // for the results
int lastSecond = -1;          // need an impossible value for comparison

const int ledPin=2;                 //Connect the LED Grove module to Pin12, Digital 12
const int thresholdvalue=10;         //The threshold for which the LED should turn on.

void setup() {

  pinMode(ledPin,OUTPUT);

  lcd.begin(16, 2);

    lcd.setRGB(colorR, colorG, colorB);

  Bridge.begin();        // initialize Bridge

  SerialUSB.begin(9600);    // initialize serial
  
  // run an initial date process. Should return:
  // hh:mm:ss :

  if (!date.running()) {
    date.begin("date");
    date.addParameter("+%T");
    date.run();
  }
}

void loop() {
  
  
  lcd.setCursor(0,0);

  if (lastSecond != seconds) { // if a second has passed

    // print the time:

    if (hours <= 9) {

      SerialUSB.print("0");  // adjust for 0-9
      lcd.print("0");
    }

    SerialUSB.print(hours);
    lcd.print(hours);
    
    SerialUSB.print(":");
    lcd.print(":");

    if (minutes <= 9) {

      SerialUSB.print("0");  // adjust for 0-9
      lcd.print("0");
    }

    SerialUSB.print(minutes);
    lcd.print(minutes);

    SerialUSB.print(":");
    lcd.print(":");
    if (seconds <= 9) {

      SerialUSB.print("0");  // adjust for 0-9
      lcd.print("0");
    }

    SerialUSB.println(seconds);
    lcd.println(seconds);
    // restart the date process:

    if (!date.running()) {

      date.begin("date");

      date.addParameter("+%T");

      date.run();

    }
    
    int sensorValue = analogRead(A0);
    lcd.setCursor(0,1);
    lcd.println(sensorValue); // lightsensor
    

    Rsensor=(float)(1023-sensorValue)*10/sensorValue;
  if(Rsensor>thresholdvalue)
  {
    digitalWrite(ledPin,HIGH);
  }
  else
  {
  digitalWrite(ledPin,LOW);
  }

  }

  //if there's a result from the date process, parse it:

  while (date.available() > 0) {

    // get the result of the date process (should be hh:mm:ss):

    String timeString = date.readString();

    // find the colons:

    int firstColon = timeString.indexOf(":");

    int secondColon = timeString.lastIndexOf(":");

    // get the substrings for hour, minute second:

    String hourString = timeString.substring(0, firstColon);

    String minString = timeString.substring(firstColon + 1, secondColon);

    String secString = timeString.substring(secondColon + 1);

    // convert to ints,saving the previous second:

    hours = hourString.toInt();

    minutes = minString.toInt();

    lastSecond = seconds;          // save to do a time comparison

    seconds = secString.toInt();

  }

}

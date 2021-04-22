#include <Arduino.h>
#include <math.h>
#include <Wire.h>
#include "rgb_lcd.h"
#include <Process.h>
#include <Bridge.h>

rgb_lcd lcd;

bool lightOn = false;

const int colorR = 255; // The color of the ldc
const int colorG = 0;
const int colorB = 0;

const int ledPin = 6; //Connect the LED Grove module to Pin12, Digital 12
const int ledPin2 = 5;

const int ThresValue = 200; //The threshold for which the LED should turn on.
const int ThresValue1 = 150;

Process date;                // process used to get the date
int hours, minutes, seconds; // for the results
int lastSecond = -1;         // need an impossible value for comparison

float Rsensor; //Resistance of sensor in K
  void setup()
  {
    Bridge.begin();
    Serial.begin(9600);      //Start the Serial connection
    pinMode(ledPin, OUTPUT); //Set the LED on Digital 12 as an OUTPUT
    pinMode(ledPin2, OUTPUT);

    lcd.begin(16, 2);
    lcd.setRGB(colorR, colorG, colorB);

    Bridge.begin(); // initialize Bridge
    SerialUSB.begin(9600); // initialize serial

    SerialUSB.println("Time Check"); // Title of sketch

if (!date.running())
    {

      date.begin("date");

      date.addParameter("+%T");

      date.run();
    } 
  }

  void loop()
  {


    lcd.setCursor(0, 0);

    if (lastSecond != seconds)
    { // if a second has passed

      // print the time:

      if (hours <= 9)
      {

        SerialUSB.print("0"); // adjust for 0-9
        lcd.print("0");
      }

      SerialUSB.print(hours);
      lcd.print(hours);

      SerialUSB.print(":");
      lcd.print(":");

      if (minutes <= 9)
      {

        SerialUSB.print("0"); // adjust for 0-9
        lcd.print("0");
      }

      SerialUSB.print(minutes);
      lcd.print(minutes);

      SerialUSB.print(":");
      lcd.print(":");
      if (seconds <= 9)
      {

        SerialUSB.print("0"); // adjust for 0-9
        lcd.print("0");
      }

      SerialUSB.println(seconds);
      lcd.println(seconds);
      // restart the date process:

      if (!date.running())
      {

        date.begin("date");

        date.addParameter("+%T");

        date.run();
      }
    }

    //if there's a result from the date process, parse it:

    while (date.available() > 0)
    {

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

      lastSecond = seconds; // save to do a time comparison

      seconds = secString.toInt();
    }

    Process p;
    
    int sensorValue = analogRead(0);
    
    if (sensorValue < 500)
    {
      if(seconds >= 0 && seconds <= 4)
        {
          p.runShellCommand("curl https://maker.ifttt.com/trigger/trigger/with/key/jvU6Y1ffMzHca4opHsEAXdhGXYP2KUdLenWUo2Qs025");
        }
      else if(seconds >= 5 && seconds <= 9)
        {
          p.runShellCommand("curl https://maker.ifttt.com/trigger/dim/with/key/jvU6Y1ffMzHca4opHsEAXdhGXYP2KUdLenWUo2Qs025");
        }
      lightOn = true;
    }
    else if ( sensorValue && lightOn = true)
    {
      p.runShellCommand("curl https://maker.ifttt.com/trigger/trigger/with/key/jvU6Y1ffMzHca4opHsEAXdhGXYP2KUdLenWUo2Qs025");
      lightOn = false;
    }
    else
    { lightOn = false;
    }

    Serial.println("the analog read data is ");
    Serial.println(sensorValue);
    Serial.println(lightOn);
    delay(1000);
  }

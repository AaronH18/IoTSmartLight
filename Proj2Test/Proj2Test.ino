void setup() {
  Bridge.begin();  // Initialize the Bridge
  Serial.begin(9600);  // Initialize the Serial

  // Wait until a Serial Monitor is connected.
  //while (!Serial);
}

void loop() {
  Process p;
  // This command line runs the WifiStatus script, (/usr/bin/pretty-wifi-info.lua), then
  // sends the result to the grep command to look for a line containing the word
  // "Signal:"  the result is passed to this sketch:
  p.runShellCommand("https://maker.ifttt.com/trigger/trigger/with/key/jvU6Y1ffMzHca4opHsEAXdhGXYP2KUdLenWUo2Qs025");
  delay(5000);  // wait 5 seconds before you do it again
  p.runShellCommand("https://maker.ifttt.com/trigger/trigger/with/key/jvU6Y1ffMzHca4opHsEAXdhGXYP2KUdLenWUo2Qs025");
  delay(5000);  // wait 5 seconds before you do it again
  
}

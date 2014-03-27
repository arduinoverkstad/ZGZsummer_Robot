#include <IRremote.h>
#include <IRremoteTools.h>

int RECV_PIN = 14;
long counter=0;
void setup()
{
  Serial.begin(9600);
  beginIRremote(14); // Start the receiver
}

void loop() {
 if (IRrecived()) {
    Serial.print("Result: ");
    Serial.println(getIRresult(), HEX);
    resumeIRremote(); // Receive the next value
  }
}

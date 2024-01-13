 /**********************************************************************************
 *  TITLE: Get the Hex code from any IR remote.
 *  Board TYPE : ESP32 DEV MODULE 
 *  PARTITION SCHEME : HUGE APP (3 MB NO OTA/ 1 MB SPIFFS)
 *  IRremote Library (3.6.1): https://github.com/Arduino-IRremote/Arduino-IRremote
 **********************************************************************************/

#include <IRremote.h>
 
int IR_RECV_PIN = 35;  //Update the pin as per circuit
 
IRrecv irrecv(IR_RECV_PIN);
decode_results results;
 
void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}
 
void loop()
{
  if (irrecv.decode(&results))
  {
  Serial.print("0x");
  Serial.println(results.value, HEX); //print the HEX code
  irrecv.resume();
  }
  delay(200);
}

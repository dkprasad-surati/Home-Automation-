#define BLYNK_TEMPLATE_ID "TMPL3Ar9VyFjV"
#define BLYNK_TEMPLATE_NAME "Sweet Home"
#define BLYNK_AUTH_TOKEN "mjjvV54QQXFR4SB7JK1RVddVPe5l5-JB"

char ssid[] = "Airtel Hub Dk2";
char pass[] = "xxxxxxxx";

//Update the HEX code of IR Remote buttons 0x<HEX CODE>
#define IR_Button_1   0xFF42BD
#define IR_Button_2   0xFF827D
#define IR_Button_3   0xFF02FD
#define IR_Button_4   0xFF629D
#define IR_Button_5   0xFFA25D
#define IR_Button_6   0xFF22DD
#define IR_All_On     0xFFA857
#define IR_All_Off    0xFFB24D


#include <BlynkSimpleEsp32.h>
#include "BluetoothSerial.h" 
#include <IRremote.h>
#include <Preferences.h>
#include <AceButton.h>
using namespace ace_button;

Preferences pref;

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run
`make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

char auth[] = BLYNK_AUTH_TOKEN;

BlynkTimer timer;

// define the GPIO connected with Relays and switches
#define RelayPin1 23  //D23
#define RelayPin2 22  //D22
#define RelayPin3 21  //D21
#define RelayPin4 19  //D19
#define RelayPin5 18 
#define RelayPin6 5  


#define SwitchPin1 13  //D13
#define SwitchPin2 12  //D12
#define SwitchPin3 14  //D14
#define SwitchPin4 27  //D27
#define SwitchPin5 4
#define SwitchPin6 15


#define IR_RECV_PIN   34 // D35 (IR receiver pin)

#define wifiLed    2   //D2

#define VPIN_BUTTON_1    V1 
#define VPIN_BUTTON_2    V2
#define VPIN_BUTTON_3    V3 
#define VPIN_BUTTON_4    V4
#define VPIN_BUTTON_5    V5 
#define VPIN_BUTTON_6    V6



int toggleState_1 = 0; //Define integer to remember the toggle state for relay 1
int toggleState_2 = 0; //Define integer to remember the toggle state for relay 2
int toggleState_3 = 0; //Define integer to remember the toggle state for relay 3
int toggleState_4 = 0; //Define integer to remember the toggle state for relay 4
int toggleState_5 = 0; //Define integer to remember the toggle state for relay 5
int toggleState_6 = 0; //Define integer to remember the toggle state for relay 6

int wifiFlag = 0;
char bt_data ; // variable for storing bluetooth data


IRrecv irrecv(IR_RECV_PIN);
decode_results results;

ButtonConfig config1;
AceButton button1(&config1);
ButtonConfig config2;
AceButton button2(&config2);
ButtonConfig config3;
AceButton button3(&config3);
ButtonConfig config4;
AceButton button4(&config4);
ButtonConfig config5;
AceButton button5(&config5);
ButtonConfig config6;
AceButton button6(&config6);


void handleEvent1(AceButton*, uint8_t, uint8_t);
void handleEvent2(AceButton*, uint8_t, uint8_t);
void handleEvent3(AceButton*, uint8_t, uint8_t);
void handleEvent4(AceButton*, uint8_t, uint8_t);
void handleEvent5(AceButton*, uint8_t, uint8_t);
void handleEvent6(AceButton*, uint8_t, uint8_t);


// When App button is pushed - switch the state

BLYNK_WRITE(VPIN_BUTTON_1) {
  toggleState_1 = param.asInt();
  digitalWrite(RelayPin1, !toggleState_1);
  pref.putBool("Relay1", toggleState_1);
}

BLYNK_WRITE(VPIN_BUTTON_2) {
  toggleState_2 = param.asInt();
  digitalWrite(RelayPin2, !toggleState_2);
  pref.putBool("Relay2", toggleState_2);
}

BLYNK_WRITE(VPIN_BUTTON_3) {
  toggleState_3 = param.asInt();
  digitalWrite(RelayPin3, !toggleState_3);
  pref.putBool("Relay3", toggleState_3);
}

BLYNK_WRITE(VPIN_BUTTON_4) {
  toggleState_4 = param.asInt();
  digitalWrite(RelayPin4, !toggleState_4);
  pref.putBool("Relay4", toggleState_4);
}

BLYNK_WRITE(VPIN_BUTTON_5) {
  toggleState_5 = param.asInt();
  digitalWrite(RelayPin5, !toggleState_5);
   pref.putBool("Relay5", toggleState_5);
}

BLYNK_WRITE(VPIN_BUTTON_6) {
  toggleState_6 = param.asInt();
  digitalWrite(RelayPin6, !toggleState_6);
   pref.putBool("Relay6", toggleState_6);
}

BLYNK_CONNECTED() {
  // update the latest state to the server
  Blynk.virtualWrite(VPIN_BUTTON_1, toggleState_1);
  Blynk.virtualWrite(VPIN_BUTTON_2, toggleState_2);
  Blynk.virtualWrite(VPIN_BUTTON_3, toggleState_3);
  Blynk.virtualWrite(VPIN_BUTTON_4, toggleState_4);
  Blynk.virtualWrite(VPIN_BUTTON_5, toggleState_5);
  Blynk.virtualWrite(VPIN_BUTTON_6, toggleState_6);
  
}

void all_SwitchOn(){
  digitalWrite(RelayPin1, LOW); toggleState_1 = 1; Blynk.virtualWrite(VPIN_BUTTON_1, toggleState_1); pref.putBool("Relay1", toggleState_1); delay(100);
  digitalWrite(RelayPin2, LOW); toggleState_2 = 1; Blynk.virtualWrite(VPIN_BUTTON_2, toggleState_2); pref.putBool("Relay2", toggleState_2); delay(100);
  digitalWrite(RelayPin3, LOW); toggleState_3 = 1; Blynk.virtualWrite(VPIN_BUTTON_3, toggleState_3); pref.putBool("Relay3", toggleState_3); delay(100);
  digitalWrite(RelayPin4, LOW); toggleState_4 = 1; Blynk.virtualWrite(VPIN_BUTTON_4, toggleState_4); pref.putBool("Relay4", toggleState_4); delay(100);
  digitalWrite(RelayPin5, LOW); toggleState_5 = 1; Blynk.virtualWrite(VPIN_BUTTON_5, toggleState_5); pref.putBool("Relay5", toggleState_5); delay(100);
  digitalWrite(RelayPin6, LOW); toggleState_6 = 1; Blynk.virtualWrite(VPIN_BUTTON_6, toggleState_6); pref.putBool("Relay6", toggleState_6); delay(100);
 
}

void all_SwitchOff(){
  digitalWrite(RelayPin1, HIGH); toggleState_1 = 0; Blynk.virtualWrite(VPIN_BUTTON_1, toggleState_1); pref.putBool("Relay1", toggleState_1); delay(100);
  digitalWrite(RelayPin2, HIGH); toggleState_2 = 0; Blynk.virtualWrite(VPIN_BUTTON_2, toggleState_2); pref.putBool("Relay2", toggleState_2); delay(100);
  digitalWrite(RelayPin3, HIGH); toggleState_3 = 0; Blynk.virtualWrite(VPIN_BUTTON_3, toggleState_3); pref.putBool("Relay3", toggleState_3); delay(100);
  digitalWrite(RelayPin4, HIGH); toggleState_4 = 0; Blynk.virtualWrite(VPIN_BUTTON_4, toggleState_4); pref.putBool("Relay4", toggleState_4); delay(100);
  digitalWrite(RelayPin5, HIGH); toggleState_5 = 0; Blynk.virtualWrite(VPIN_BUTTON_5, toggleState_5); pref.putBool("Relay5", toggleState_5); delay(100);
  digitalWrite(RelayPin6, HIGH); toggleState_6 = 0; Blynk.virtualWrite(VPIN_BUTTON_6, toggleState_6); pref.putBool("Relay6", toggleState_6); delay(100);
   
}

void bluetooth_control()
{
  if (SerialBT.available()){
    bt_data = SerialBT.read();
    Serial.println(bt_data);
    delay(20);
    switch(bt_data)
      {
        case 'A': digitalWrite(RelayPin1, LOW);  toggleState_1 = 1; Blynk.virtualWrite(VPIN_BUTTON_1, toggleState_1); pref.putBool("Relay1", toggleState_1); break; // if 'A' received Turn on Relay1
        case 'a': digitalWrite(RelayPin1, HIGH); toggleState_1 = 0; Blynk.virtualWrite(VPIN_BUTTON_1, toggleState_1); pref.putBool("Relay1", toggleState_1); break; // if 'a' received Turn off Relay1
        case 'B': digitalWrite(RelayPin2, LOW);  toggleState_2 = 1; Blynk.virtualWrite(VPIN_BUTTON_2, toggleState_2); pref.putBool("Relay2", toggleState_2); break; // if 'B' received Turn on Relay2
        case 'b': digitalWrite(RelayPin2, HIGH); toggleState_2 = 0; Blynk.virtualWrite(VPIN_BUTTON_2, toggleState_2); pref.putBool("Relay2", toggleState_2); break; // if 'b' received Turn off Relay2
        case 'C': digitalWrite(RelayPin3, LOW);  toggleState_3 = 1; Blynk.virtualWrite(VPIN_BUTTON_3, toggleState_3); pref.putBool("Relay3", toggleState_3); break; // if 'C' received Turn on Relay3
        case 'c': digitalWrite(RelayPin3, HIGH); toggleState_3 = 0; Blynk.virtualWrite(VPIN_BUTTON_3, toggleState_3); pref.putBool("Relay3", toggleState_3); break; // if 'c' received Turn off Relay3
        case 'D': digitalWrite(RelayPin4, LOW);  toggleState_4 = 1; Blynk.virtualWrite(VPIN_BUTTON_4, toggleState_4); pref.putBool("Relay4", toggleState_4); break; // if 'D' received Turn on Relay4
        case 'd': digitalWrite(RelayPin4, HIGH); toggleState_4 = 0; Blynk.virtualWrite(VPIN_BUTTON_4, toggleState_4); pref.putBool("Relay4", toggleState_4); break; // if 'd' received Turn off Relay4
		    case 'E': digitalWrite(RelayPin5, LOW);  toggleState_5 = 1; Blynk.virtualWrite(VPIN_BUTTON_5, toggleState_5); pref.putBool("Relay5", toggleState_5); break; // if 'E' received Turn on Relay5
        case 'e': digitalWrite(RelayPin5, HIGH); toggleState_5 = 0; Blynk.virtualWrite(VPIN_BUTTON_5, toggleState_5); pref.putBool("Relay5", toggleState_5); break; // if 'e' received Turn off Relay5
		    case 'F': digitalWrite(RelayPin6, LOW);  toggleState_6 = 1; Blynk.virtualWrite(VPIN_BUTTON_6, toggleState_6); pref.putBool("Relay6", toggleState_6); break; // if 'F' received Turn on Relay6
        case 'f': digitalWrite(RelayPin6, HIGH); toggleState_6 = 0; Blynk.virtualWrite(VPIN_BUTTON_6, toggleState_6); pref.putBool("Relay6", toggleState_6); break; // if 'f' received Turn off Relay6
	    	case 'Z': all_SwitchOn(); break;  // if 'Z' received Turn on all Relays
        case 'z': all_SwitchOff(); break; // if 'z' received Turn off all Relays
        default : break;
      }
   }  
}

void ir_remote(){
  if (irrecv.decode(&results)) {
    switch(results.value){
        case IR_Button_1:  
          digitalWrite(RelayPin1, toggleState_1);
          toggleState_1 = !toggleState_1;
          pref.putBool("Relay1", toggleState_1);
          Blynk.virtualWrite(VPIN_BUTTON_1, toggleState_1);
          delay(100);            
          break;
        case IR_Button_2:  
          digitalWrite(RelayPin2, toggleState_2);
          toggleState_2 = !toggleState_2;
          pref.putBool("Relay2", toggleState_2);
          Blynk.virtualWrite(VPIN_BUTTON_2, toggleState_2);
          delay(100);            
          break;
        case IR_Button_3:  
          digitalWrite(RelayPin3, toggleState_3);
          toggleState_3 = !toggleState_3;
          pref.putBool("Relay3", toggleState_3);
          Blynk.virtualWrite(VPIN_BUTTON_3, toggleState_3);
          delay(100);            
          break;
        case IR_Button_4:  
          digitalWrite(RelayPin4, toggleState_4);
          toggleState_4 = !toggleState_4;
          pref.putBool("Relay4", toggleState_4);
          Blynk.virtualWrite(VPIN_BUTTON_4, toggleState_4);
          delay(100);            
          break;
		    case IR_Button_5:  
            digitalWrite(RelayPin5, toggleState_5);
            toggleState_5 = !toggleState_5;
            pref.putBool("Relay5", toggleState_5);
            Blynk.virtualWrite(VPIN_BUTTON_5, toggleState_5);
            delay(100);            
            break;
        case IR_Button_6:  
            digitalWrite(RelayPin6, toggleState_6);
            toggleState_6 = !toggleState_6;
            pref.putBool("Relay6", toggleState_6);
            Blynk.virtualWrite(VPIN_BUTTON_6, toggleState_6);
            delay(100);            
            break;
        case IR_All_Off:
          all_SwitchOff();  
          break;
        case IR_All_On:
          all_SwitchOn();  
          break;
        default : break;         
      }   
      //Serial.println(results.value, HEX);    
      irrecv.resume();   
  } 
}

void getRelayState()
{
  //Serial.println("reading data from NVS");
  toggleState_1 = pref.getBool("Relay1", 0);
  digitalWrite(RelayPin1, !toggleState_1); 
  Blynk.virtualWrite(VPIN_BUTTON_1, toggleState_1);
  delay(200);
  toggleState_2 = pref.getBool("Relay2", 0);
  digitalWrite(RelayPin2, !toggleState_2); 
  Blynk.virtualWrite(VPIN_BUTTON_2, toggleState_2);
  delay(200);
  toggleState_3 = pref.getBool("Relay3", 0);
  digitalWrite(RelayPin3, !toggleState_3); 
  Blynk.virtualWrite(VPIN_BUTTON_3, toggleState_3);
  delay(200);
  toggleState_4 = pref.getBool("Relay4", 0);
  digitalWrite(RelayPin4, !toggleState_4); 
  Blynk.virtualWrite(VPIN_BUTTON_4, toggleState_4);
  delay(200); 
  toggleState_5 = pref.getBool("Relay5", 0);
  digitalWrite(RelayPin5, !toggleState_5); 
  Blynk.virtualWrite(VPIN_BUTTON_5, toggleState_5);
  delay(200);
  toggleState_6 = pref.getBool("Relay6", 0);
  digitalWrite(RelayPin6, !toggleState_6); 
  Blynk.virtualWrite(VPIN_BUTTON_6, toggleState_6);
  delay(200);
  
}

void checkBlynkStatus() { // called every 3 seconds by SimpleTimer

  bool isconnected = Blynk.connected();
  if (isconnected == false) {
    wifiFlag = 1;
    digitalWrite(wifiLed, LOW);
    Serial.println("Blynk Not Connected");
  }
  if (isconnected == true) {
    wifiFlag = 0;
    digitalWrite(wifiLed, HIGH);
    //Serial.println("Blynk Connected");
  }
}

void setup()
{
  Serial.begin(9600);
  pref.begin("Relay_State", false);

  btStart();  //Serial.println("Bluetooth On");
  
  SerialBT.begin("ESP32_BT"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  delay(5000);

  pinMode(RelayPin1, OUTPUT);
  pinMode(RelayPin2, OUTPUT);
  pinMode(RelayPin3, OUTPUT);
  pinMode(RelayPin4, OUTPUT);
  pinMode(RelayPin5, OUTPUT);
  pinMode(RelayPin6, OUTPUT);

  pinMode(wifiLed, OUTPUT);

  pinMode(SwitchPin1, INPUT_PULLUP);
  pinMode(SwitchPin2, INPUT_PULLUP);
  pinMode(SwitchPin3, INPUT_PULLUP);
  pinMode(SwitchPin4, INPUT_PULLUP);
  pinMode(SwitchPin5, INPUT_PULLUP);
  pinMode(SwitchPin6, INPUT_PULLUP);
 

  irrecv.enableIRIn(); // Enabling IR sensor

  //During Starting all Relays should TURN OFF
  digitalWrite(RelayPin1, !toggleState_1);
  digitalWrite(RelayPin2, !toggleState_2);
  digitalWrite(RelayPin3, !toggleState_3);
  digitalWrite(RelayPin4, !toggleState_4);
  digitalWrite(RelayPin5, !toggleState_5);
  digitalWrite(RelayPin6, !toggleState_6);
  

  config1.setEventHandler(button1Handler);
  config2.setEventHandler(button2Handler);
  config3.setEventHandler(button3Handler);
  config4.setEventHandler(button4Handler);
  config5.setEventHandler(button5Handler);
  config6.setEventHandler(button6Handler);
 
  button1.init(SwitchPin1);
  button2.init(SwitchPin2);
  button3.init(SwitchPin3);
  button4.init(SwitchPin4);
  button5.init(SwitchPin5);
  button6.init(SwitchPin6);
 
  delay(200);

  WiFi.begin(ssid, pass);
  timer.setInterval(3000L, checkBlynkStatus); // check if Blynk server is connected every 3 seconds
  Blynk.config(auth);
  delay(1000);
  getRelayState(); //fetch data from NVS Flash Memory
}

void loop()
{  
  Blynk.run();
  timer.run(); // Initiates SimpleTimer

  //Control Switches Manualy
  button1.check();
  button2.check();
  button3.check();
  button4.check();
  button5.check();
  button6.check();
  
  
  bluetooth_control(); //Bluetooth Control
  ir_remote(); //IR remote Control
}

void button1Handler(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  Serial.println("EVENT1");
  switch (eventType) {
    case AceButton::kEventPressed:
      toggleState_1 = 1;
      digitalWrite(RelayPin1, LOW);
      Blynk.virtualWrite(VPIN_BUTTON_1, toggleState_1);
      pref.putBool("Relay1", toggleState_1);
      break;
    case AceButton::kEventReleased:
      toggleState_1 = 0;
      digitalWrite(RelayPin1, HIGH);
      Blynk.virtualWrite(VPIN_BUTTON_1, toggleState_1);
      pref.putBool("Relay1", toggleState_1);
      break;
  }
}

void button2Handler(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  Serial.println("EVENT2");
  switch (eventType) {
    case AceButton::kEventPressed:
      toggleState_2 = 1;
      digitalWrite(RelayPin2, LOW);
      Blynk.virtualWrite(VPIN_BUTTON_2, toggleState_2);
      pref.putBool("Relay2", toggleState_2);
      break;
    case AceButton::kEventReleased:
      toggleState_2 = 0;
      digitalWrite(RelayPin2, HIGH);
      Blynk.virtualWrite(VPIN_BUTTON_2, toggleState_2);
      pref.putBool("Relay2", toggleState_2);
      break;
  }
}

void button3Handler(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  Serial.println("EVENT3");
  switch (eventType) {
    case AceButton::kEventPressed:
      toggleState_3 = 1;
      digitalWrite(RelayPin3, LOW);
      Blynk.virtualWrite(VPIN_BUTTON_3, toggleState_3);
      pref.putBool("Relay3", toggleState_3); 
      break;
    case AceButton::kEventReleased:
      toggleState_3 = 0;
      digitalWrite(RelayPin3, HIGH);
      Blynk.virtualWrite(VPIN_BUTTON_3, toggleState_3);
      pref.putBool("Relay3", toggleState_3);
      break;
  }
}

void button4Handler(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  Serial.println("EVENT4");
  switch (eventType) {
    case AceButton::kEventPressed:
      toggleState_4 = 1;
      digitalWrite(RelayPin4, LOW);
      Blynk.virtualWrite(VPIN_BUTTON_4, toggleState_4);
      pref.putBool("Relay4", toggleState_4);
      break;
    case AceButton::kEventReleased:
      toggleState_4 = 0;
      digitalWrite(RelayPin4, HIGH);
      Blynk.virtualWrite(VPIN_BUTTON_4, toggleState_4);
      pref.putBool("Relay4", toggleState_4);
      break;
  }
}

void button5Handler(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  Serial.println("EVENT5");
  switch (eventType) {
    case AceButton::kEventPressed:
      toggleState_5 = 1;
      digitalWrite(RelayPin5, LOW);
      Blynk.virtualWrite(VPIN_BUTTON_5, toggleState_5);
      pref.putBool("Relay5", toggleState_4);
      break;
    case AceButton::kEventReleased:
      toggleState_5 = 0;
      digitalWrite(RelayPin5, HIGH);
      Blynk.virtualWrite(VPIN_BUTTON_5, toggleState_5);
      pref.putBool("Relay5", toggleState_5);
      break;
  }
}

void button6Handler(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  Serial.println("EVENT6");
  switch (eventType) {
    case AceButton::kEventPressed:
      toggleState_6 = 1;
      digitalWrite(RelayPin6, LOW);
      Blynk.virtualWrite(VPIN_BUTTON_6, toggleState_6);
      pref.putBool("Relay6", toggleState_6);
      break;
    case AceButton::kEventReleased:
      toggleState_6 = 0;
      digitalWrite(RelayPin6, HIGH);
      Blynk.virtualWrite(VPIN_BUTTON_6, toggleState_6);
      pref.putBool("Relay6", toggleState_6);
      break;
  }
}

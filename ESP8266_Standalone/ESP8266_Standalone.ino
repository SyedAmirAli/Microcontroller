#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "TMPL6eRguGIj_"
#define BLYNK_TEMPLATE_NAME "SHIHAB AUTOMATION"
#define BLYNK_AUTH_TOKEN "5LvsZf6g6xaLgcRzmF6NKW1JVnB_Nuzv"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char ssid[] = "SHIHAB";
char pass[] = "Nointernet";

// Digital pins on the ESP8266

// INPUT
const int D3 = 5;   
const int D4 = 4;

// OUTPUT
const int PC_RELAY_PIN = 0; // D1
const int OTHER_RELAY_PIN = 2; // D2

bool switchStatePC = LOW; 
bool switchStateOther = LOW; 

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Initialize digital pins as outputs
  pinMode(PC_RELAY_PIN, OUTPUT);
  pinMode(OTHER_RELAY_PIN, OUTPUT);
  pinMode(D3, INPUT_PULLUP);
  pinMode(D4, INPUT_PULLUP);

  // set the local state
  digitalWrite(PC_RELAY_PIN, HIGH);
  digitalWrite(OTHER_RELAY_PIN, HIGH);
}

BLYNK_WRITE(V1) {
  // Get the state of the virtual pin
  switchStatePC = param.asInt();

  // Set the corresponding digital pin state
  digitalWrite(PC_RELAY_PIN, switchStatePC);
}

BLYNK_WRITE(V2) {
  switchStateOther = param.asInt();
  digitalWrite(OTHER_RELAY_PIN, switchStateOther);
}

// function of local switch controlling
void localSwitchControlling(){
  const int pc_switch = digitalRead(D3);
  const int other_switch = digitalRead(D4);

  if(pc_switch == LOW){
    switchStatePC = !switchStatePC;
  }else{
    switchStatePC = !switchStatePC;
  }

  if(other_switch == LOW){
    switchStateOther = !switchStateOther;
  }else{
    switchStateOther = !switchStateOther;
  } 
}
 
void loop()
{
  Blynk.run();
  localSwitchControlling();
}


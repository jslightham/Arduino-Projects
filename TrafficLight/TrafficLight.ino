#include <Wire.h>
#include <NewPing.h>

#define TRIGGER_PIN 2 
#define ECHO_PIN 3 
const int relayPin = 7;
const int relayPing = 8;
const int relayPiny = 9;
const int relayPinr = 10;
int lightColor = 0;
int timer = 0;
bool on = false;
bool lightState = false;
#define MAX_DISTANCE 400
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup(){
  pinMode(relayPin, OUTPUT);
  pinMode(relayPing, OUTPUT);
  pinMode(relayPiny, OUTPUT);
  pinMode(relayPinr, OUTPUT);
  Serial.begin(9600);
}

void loop(){
  delay(250);
  timer++;
  
  if(timer >= 200){
    timer = 0;
    lightColor = 0;
  }else if(timer >=150){
    lightColor = 2;
  }else if(timer >= 140){
    lightColor = 1;
  }else{
    lightColor = 0;
  }
  
  unsigned int ultrasonic = sonar.ping();
  if(lightColor == 0){
    digitalWrite(relayPing, HIGH);
    digitalWrite(relayPiny, LOW);
    digitalWrite(relayPinr, LOW);
    if(ultrasonic / US_ROUNDTRIP_CM <= 50 && ultrasonic / US_ROUNDTRIP_CM != 0){
    if(!on){
      digitalWrite(relayPin, HIGH);
      on = true;
      lightState = !lightState;
    }else{
      digitalWrite(relayPin, LOW);
      on = false;
    }
  }else{
    if(lightState){
      digitalWrite(relayPin, HIGH);
      delay(100);
      digitalWrite(relayPin, LOW);
      lightState = false;
    }
  }
  }else if(lightColor == 1){
    digitalWrite(relayPing, LOW);
    digitalWrite(relayPiny, HIGH);
    digitalWrite(relayPinr, LOW);
  }else if(lightColor == 2){
    digitalWrite(relayPing, LOW);
    digitalWrite(relayPiny, LOW);
    digitalWrite(relayPinr, HIGH);
  }
  
}

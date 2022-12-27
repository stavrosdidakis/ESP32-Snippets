//Ping for Arduino, ESP8266, and ESP32

#include "NewPing.h"      // include NewPing library

// for Arduino microcontroller
int trigPin = D6;      // trigger pin
int echoPin = D7;      // echo pin

// for ESP8266 microcontroller
//int trigPin = D0;      // trigger pin
//int echoPin = D1;      // echo pin

// for ESP32 microcontroller
//int trigPin = 4;      // trigger pin
//int echoPin = 0;      // echo pin

NewPing sonar(trigPin, echoPin);

void setup(){
  Serial.begin(9600);
}

void loop(){
  float distance = sonar.ping_median(5);
  Serial.println(distance);
 
}

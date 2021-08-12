#include <WiFi.h>
#include <SinricPro.h>
#include "SinricProBlinds.h"
#include "credentials.h"
#include "pinout.h"

double blindsPosition        = 0;
double desiredBlindsPosition = 0;

// Encoder
double currStateA;
double prevStateA;
double currStateB;

void setup()
{
  // Set Pin Modes
  pinMode(MOTOR_SPEED, OUTPUT);   // Motor
  pinMode(MOTOR_IN1, OUTPUT);     // .
  pinMode(MOTOR_IN2, OUTPUT);     // .
  pinMode (OUTPUT_A,INPUT);       // Encoder
  pinMode (OUTPUT_B,INPUT);       // .

  // ISR Encoder
  prevStateA = digitalRead(OUTPUT_A);  //read initial state of OUTPUT_A
  attachInterrupt(digitalPinToInterrupt(OUTPUT_B), updatePosition, CHANGE);

  Serial.begin(BAUD_RATE);

  setupWifi();
  setupSinricPro();
}

void loop () {
  // Handle connection between SinricPro server and device
  SinricPro.handle();
}
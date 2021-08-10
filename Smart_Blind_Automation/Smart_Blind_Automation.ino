#include <WiFi.h>
#include <SinricPro.h>
#include "SinricProBlinds.h"
#include "credentials.h"
#include "pinout.h"

double blindsPosition        = 0;  // TODO: double? if we do adjustments for counter
double desiredBlindsPosition = 0;  // TODO: double?

// Encoder
double currStateA;
double prevStateA; // TODO: double?
double currStateB;

void setup()
{
  // Set pin modes
  pinMode(MOTOR_SPEED, OUTPUT);   //Motor
  pinMode(MOTOR_IN1, OUTPUT);     // .
  pinMode(MOTOR_IN2, OUTPUT);     // .
  pinMode (outputA,INPUT);        // Encoder
  pinMode (outputB,INPUT);        // .
  //pinMode(wifiLED, OUTPUT);     // LED

  // ISR Encoder
  prevStateA = digitalRead(outputA);  //read initial state of outputA
  attachInterrupt(digitalPinToInterrupt(outputB), updatePosition, CHANGE);

  Serial.begin(BAUDE_RATE);

  setupWifi();
  setupSinricPro();
}

void loop () {
  // Handle connection between SinricPro server and device
  SinricPro.handle();
}

// Potential Future Improvements:
// - Way to set open/closed location upon startup
// - External LED for status indication
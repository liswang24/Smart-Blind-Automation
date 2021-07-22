#include <WiFi.h>
#include <SinricPro.h>
#include "SinricProBlinds.h"
#include "credentials.h"
#include "pinout.h"

int blindsPosition = 0;
// bool powerState = false;

void setup()
{
  // Set pin modes
  //pinMode(wifiLED, OUTPUT);

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
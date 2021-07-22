#include <WiFi.h>
#include <SinricPro.h>
#include "SinricProBlinds.h"

#define BAUDE_RATE 9600

// Wifi Network Credentials
#define WIFI_SSID /* Hidden */
#define WIFI_PASSWORD /* Hidden */

// Sinric Pro Credentials
#define APP_KEY    /* Hidden */
#define APP_SECRET /* Hidden */
#define BLINDS_ID  /* Hidden */

int blindsPosition = 0;
// bool powerState = false;

// Wifi Status LED
//const byte wifiLED = 7;

void setupWifi() {
  // Attempt connection to wifi network   
  Serial.print("Attempting to connect to SSID: ");
  Serial.println(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.println("... Waiting for connection ...");
      //digitalWrite(wifiLED, HIGH);
  }

  // Successfully Connected to Wifi
  Serial.println("");
  Serial.println("Connected to WiFi");
}

void setupSinricPro() {
  // Get a blinds device from SinricPro
  SinricProBlinds &blinds = SinricPro[BLINDS_ID];
  // blinds.onPowerState(onPowerState);
  blinds.onRangeValue(setPosition);
  // blinds.onAdjustRangeValue(onAdjustRangeValue);

  // Connection to SinricPro
  SinricPro.onConnected([](){ Serial.printf("Connected to SinricPro\r\n"); }); 
  SinricPro.onDisconnected([](){ Serial.printf("Disconnected from SinricPro\r\n"); });
  SinricPro.begin(APP_KEY, APP_SECRET);
  // SinricPro.restoreDeviceStates(true); // what this for
}

// bool onPowerState(const String &deviceId, bool &state) {
//   Serial.printf("Device %s power turned %s \r\n", deviceId.c_str(), state?"on":"off");
//   powerState = state;
//   return true; // request handled properly
// }

bool setPosition(const String &deviceId, int &position) {
  Serial.printf("Device %s set position to %d\r\n", deviceId.c_str(), position);
  // TODO: Implement position reading and motor engagement
  return true; // request handled properly
}

// bool onAdjustRangeValue(const String &deviceId, int &positionDelta) {
//   blindsPosition += positionDelta;
//   Serial.printf("Device %s position changed about %i to %d\r\n", deviceId.c_str(), positionDelta, blindsPosition);
//   positionDelta = blindsPosition; // calculate and return absolute position
//   return true; // request handled properly
// }

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
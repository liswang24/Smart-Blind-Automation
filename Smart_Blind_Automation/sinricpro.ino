void setupSinricPro() {
  // Get a blinds device from SinricPro
  SinricProBlinds &blinds = SinricPro[BLINDS_ID];
  blinds.onRangeValue(setPosition);

  // Connection to SinricPro
  SinricPro.onConnected([](){ Serial.printf("Connected to SinricPro\r\n"); }); 
  SinricPro.onDisconnected([](){ Serial.printf("Disconnected from SinricPro\r\n"); });
  SinricPro.begin(APP_KEY, APP_SECRET);
}

bool setPosition(const String &deviceId, int &position) {
    // Calculate relative position
    desiredBlindsPosition = FULLY_OPEN * position / 100;
    moveBlindsToDesiredPosition(desiredBlindsPosition);
    
    stopBlinds();

    Serial.printf("Device %s set position to %d\r\n", deviceId.c_str(), position);
    return true; // request handled properly
}
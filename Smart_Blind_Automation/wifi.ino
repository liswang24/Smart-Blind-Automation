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
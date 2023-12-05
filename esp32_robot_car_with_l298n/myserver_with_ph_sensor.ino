#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

// Replace these with your Wi-Fi credentials
const char *ssid = "your-ssid";
const char *password = "your-password";

// Replace with your pH sensor configuration
const int analogPin = A0;

// Replace with your API endpoint
const char *apiEndpoint = "https://syedamirali.com/php/esp-api/message/store";

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  connectToWiFi();
}

void loop() {
  // Read pH sensor data
  float pHValue = readPHSensor();

  // Prepare JSON payload
  String jsonPayload = "{\"text\":\"pH value: " + String(pHValue, 2) + "\",\"username\":\"faysal\"}";

  // Send data to API
  sendDataToAPI(jsonPayload);

  // Wait for 10 seconds before taking the next reading
  delay(10000);
}

void connectToWiFi() {
  Serial.println();
  Serial.print("Connecting to WiFi");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

float readPHSensor() {
  // Read the analog voltage from the pH sensor
  int sensorValue = analogRead(analogPin);

  // Convert the analog value to pH value (replace the formula with the one provided by your sensor's datasheet)
  float pHValue = map(sensorValue, 0, 1023, 0, 14);  // Example mapping, adjust according to your sensor

  return pHValue;
}

void sendDataToAPI(String payload) {
  HTTPClient http;

  // Make a POST request to the API endpoint
  http.begin(apiEndpoint);
  http.addHeader("Content-Type", "application/json");

  // Send the JSON payload
  int httpResponseCode = http.POST(payload);

  // Check for errors
  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
  } else {
    Serial.print("HTTP Error: ");
    Serial.println(httpResponseCode);
  }

  // Close the connection
  http.end();
}

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

// Replace these with your Wi-Fi credentials
const char *ssid = "SYED AMIR ALI";
const char *password = "01817807594";

// Replace with your pH sensor configuration
const int trigPin = 14; // D5
const int echoPin = 12; // D6
const int pirMotionPin = 15; // D8
const int analogPin = A0;

// Replace with your API endpoint
const char *apiEndpoint = "http://syedamirali.com/php/esp-api/message/update?id=2";

// Create a WiFiClientSecure object for HTTPS
HTTPClient http;
WiFiClient wifiClient;

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  connectToWiFi();
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(pirMotionPin, INPUT);
}

void loop() {  
  sendDataToAPI(jsonDataForApi());

  // Wait for 10 seconds before taking the next reading value and sending request
  delay(20000);
}

String jsonDataForApi(){
  const size_t capacity = JSON_OBJECT_SIZE(2) + 4 * JSON_OBJECT_SIZE(4);
  DynamicJsonDocument doc(capacity);

  // create a instance of an JSON object and nested JSON object.
  JsonObject attributes = doc.createNestedObject("attributes");
  attributes["ph"] = ph();
  attributes["temperature"] = temperature();
  attributes["waterLevel"] = waterLevel();
  attributes["pirMotion"] = pirMotion();

  // set your username and description, username are valid on ("faysal", "adif", "amir", "chad", "esp")
  doc["username"] = "amir";
  doc["text"] = "Write Here Your Description";

  // make the JSON data into a string and serialize it.
  String JsonString;
  serializeJson(doc, JsonString);
  
  // Check the Created JSON data in our serial monitor and return the data from this function.  
  // Serial.println(JsonString);
  return JsonString;
}

void connectToWiFi() {
  Serial.println();
  Serial.print("Connecting to WiFi");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("\nWiFi connected");
  Serial.print("\nIP Address: ");
  Serial.println(WiFi.localIP());
}

// liquied PH Value from ph sensor
float ph() {
  int sensorValue = analogRead(analogPin); 
  float value = map(sensorValue, 0, 1023, 0, 14);
  return value;
}

// Temperature Value from temperature sensor
float temperature() {
  // int sensorValue = analogRead(analogPinTemperature);
  // float voltage = (sensorValue / 1024.0) * 5.0;
  // float temperatureC = (voltage - 0.5) * 100.0;
  // return temperatureC;
  return 0.00;
}

// Water Level from Water Level Indicator sensor
float waterLevel(){
  // Trigger the ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the duration of the echo pulse
  unsigned long duration = pulseIn(echoPin, HIGH);

  // Calculate the distance in centimeters
  // Speed of sound in air is approximately 343 meters per second (34300 cm/s)
  // Distance = (duration / 2) * speed of sound
  float distance = duration * 0.0343 / 2;

  return distance;
}

// PIR Motion Sensor Value from Ultrasonic sensor
float pirMotion(){
  int motionValue = digitalRead(pirMotionPin);

  if (motionValue == HIGH) {
    Serial.println("Motion detected!");
  } else {
    Serial.println("No motion");
  }

  delay(1000); 
  return motionValue;
}

void sendDataToAPI(String payload) {

  // Make a POST request to the API endpoint
  http.begin(wifiClient, apiEndpoint); 
  http.addHeader("Content-Type", "application/json");

  // Send the JSON payload
  int httpResponseCode = http.POST(payload);

  // Check for errors
  if (httpResponseCode > 0) {
    Serial.print("\nHTTP Response code: ");
    Serial.println(httpResponseCode);
    Serial.println(http.getString());
  } else {
    Serial.println("Connection failed");
    Serial.print("HTTP Error: ");
    Serial.println(http.errorToString(httpResponseCode).c_str());
    Serial.println("Details: " + http.getString());
  }

  // Close the connection
  http.end();
}
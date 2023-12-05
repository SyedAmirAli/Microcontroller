#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define WIFI_SSID "Everyday I'm buffering..."
#define WIFI_PASSWORD "asdfasdf"

#define FIREBASE_HOST "hydroponics-963c9-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "HqTp6Uh5HWsvP6HC3R0N2TrZSxk9hTNo7H9VIYR0"

void setup() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.begin(115200);

  // Connect to Firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  // Send data to Firebase
  sendHelloWorldToFirebase();

  // Delay before sending again (adjust as needed)
  delay(5000);
}

void sendHelloWorldToFirebase() {
  // Set the data you want to send
  String dataToSend = "Hello, World!";

  // Send the data to a specific path in Firebase
  Firebase.setString("message", dataToSend);

  // Check if the operation was successful
  if (Firebase.failed()) {
    Serial.print("Error sending data to Firebase: ");
    Serial.println(Firebase.error());
  } else {
    Serial.println("Data sent to Firebase successfully!");
  }
}
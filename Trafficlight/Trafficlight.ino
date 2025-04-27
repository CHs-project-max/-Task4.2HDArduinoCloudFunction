#include "Firebase_Arduino_WiFiNINA.h"
// Replace with your network credentials
#define ssid "Telstra1AA87A"
#define pass "rqp2vsnk44b7unk4"

// Firebase info
#define firebase_host "traffic-light-e5bd0-default-rtdb.asia-southeast1.firebasedatabase.app" // Your Firebase database URL
#define api_key "AIzaSyAgCmR2SNT9zsawYxJH5TwWnMxw46OrDX0" // Optional, if needed for authentication
#define path "/light"
// LED pins for simulating traffic lights
#define redPin  2
#define yellowPin  3
#define greenPin  4

FirebaseData Data;

void setup() {
  Serial.begin(9600);

  // Connect to Wi-Fi
  if (WiFi.begin(ssid, pass) == WL_CONNECTED) {
    Serial.println("Connected to WiFi");
  } else {
    Serial.println("Failed to connect to WiFi");
    while (true);  // Stop if Wi-Fi connection fails
  }
  Firebase.begin(firebase_host, api_key, ssid, pass);
  Firebase.reconnectWiFi(true);
  // Set LED pins as output
  pinMode(redPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
}

void loop() {
  // Make an HTTPS request to Firebase
  if(Firebase.getString(Data, path))
  {
    Serial.print("set ligh: ");
    Serial.println(Data.stringData());
    setTrafficLight(Data.stringData());
  }
  delay(50);
}

// Function to set the traffic light based on the response
void setTrafficLight(String color) {
  // Turn off all LEDs first
  digitalWrite(redPin, LOW);
  digitalWrite(yellowPin, LOW);
  digitalWrite(greenPin, LOW);

  // Set the correct LED
  if (color == "red") {
    digitalWrite(redPin, HIGH);
  } else if (color == "yellow") {
    digitalWrite(yellowPin, HIGH);
  } else if (color == "green") {
    digitalWrite(greenPin, HIGH);
  }
}

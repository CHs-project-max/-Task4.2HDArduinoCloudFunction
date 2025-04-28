#include <WiFiNINA.h>
#include "Secret.h"
#define host "traffic-light-e5bd0-default-rtdb.asia-southeast1.firebasedatabase.app"
#define auth "AIzaSyAgCmR2SNT9zsawYxJH5TwWnMxw46OrDX0"

#define redPin 2
#define yellowPin 3
#define greenPin 4
WiFiSSLClient client;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  while(WiFi.begin(SSID, pass) != WL_CONNECTED)
  {
    Serial.println(".");
    delay(10);
  }
  Serial.println("Connected to wifi");

  pinMode(redPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(greenPin, OUTPUT);

}

void loop() {

client.connect(host, 443);
String path = "/light.json?auth=";
client.println("GET " + path + auth + " HTTP/1.1");
client.println("Host: " + String(host));
client.println("Connection: close");
client.println("Accept: application/json");
client.println();

while (client.connected()) {
  String line = client.readStringUntil('\n');
  if (line == "\r" || line.length() == 0) {
    break;
  }
}

String content = "";
unsigned long timeout = millis();
while (client.connected() && millis() - timeout < 5000) {
  while (client.available()) {
    content = client.readString();
  }
}

content = content.substring(1, content.length() - 1);

Serial.println("Response Light:");
Serial.println(content);
setTrafficLight(content);
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

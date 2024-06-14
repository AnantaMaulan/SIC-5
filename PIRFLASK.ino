#include <WiFi.h>
#include <HTTPClient.h>

const char *ssid = "MAN1";
const char *password = "majesa1234";
const char *serverName = "http://192.168.252.254:5000/submit";

#define PIR_PIN 13

void setup(void) {
  Serial.begin(115200);
  
  // Setup WiFi connection
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Setup PIR sensor
  pinMode(PIR_PIN, INPUT);
}

void loop(void) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    int pirState = digitalRead(PIR_PIN);
    String pir = (pirState == HIGH) ? "true" : "false";

    http.begin(serverName);
    http.addHeader("Content-Type", "application/json");

    String jsonPayload = "{\"pir\":";
    jsonPayload += pir;
    jsonPayload += "}";

    int httpResponseCode = http.POST(jsonPayload);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(httpResponseCode);
      Serial.println(response);
    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
    }

    http.end();

    delay(1000); // Check PIR sensor every second
  } else {
    Serial.println("WiFi not connected");
    delay(1000);
  }
}

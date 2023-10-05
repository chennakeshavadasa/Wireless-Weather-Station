#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>
#include <DHT.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#define DHTPIN 2 // Pin where the DHT11 is connected
#define DHTTYPE DHT11 // Type of DHT sensor

DHT dht(DHTPIN, DHTTYPE);
Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);

const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";
const char* serverIP = "YOUR_SERVER_IP";
int port = 80;

void setup() {
  Serial.begin(9600);
  dht.begin();
  if (!bmp.begin()) {
    Serial.println(F("Could not find a valid BMP085 sensor, check wiring!"));
    while (1);
  }

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
}

void loop() {
  // Read temperature and humidity from DHT11
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Read pressure from BMP180
  sensors_event_t event;
  bmp.getEvent(&event);
  float pressure = event.pressure / 100.0F;

  // Read water drop sensor
  int waterDropValue = analogRead(A0);

  // Create JSON string
  String json = "{\"temperature\":" + String(temperature) + ","
                "\"humidity\":" + String(humidity) + ","
                "\"pressure\":" + String(pressure) + ","
                "\"water_drop\":" + String(waterDropValue) + "}";

  // Send data to server
  HTTPClient http;
  String url = "http://" + String(serverIP) + ":" + String(port) + "/update";
  
  http.begin(url);
  http.addHeader("Content-Type", "application/json");
  int httpCode = http.POST(json);
  
  if (httpCode > 0) {
    String payload = http.getString();
    Serial.println(payload);
  }
  else {
    Serial.println("Error on HTTP request");
  }
  
  http.end();

  delay(5000); // Delay for 5 seconds before sending the next reading
}

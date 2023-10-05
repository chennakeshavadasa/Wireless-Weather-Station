//version1
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>
#include <DHT.h>

#define DHTPIN 2 // DHT Pin Connection
#define DHTTYPE DHT11 // Type of DHT sensor

DHT dht(DHTPIN, DHTTYPE);
Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);

void setup() {
  Serial.begin(9600);
  dht.begin();
  if (!bmp.begin()) {
    Serial.println(F("Could not find a valid BMP085 sensor, check wiring!"));
    while (1);
  }
}

void loop() {
  // Get temperature and humidity from DHT11
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Get pressure from BMP180
  sensors_event_t event;
  bmp.getEvent(&event);
  float pressure = event.pressure / 100.0F;

  // Get water drop sensor
  int waterDropValue = analogRead(A0);

  // Print data to Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print("°C, Humidity: ");
  Serial.print(humidity);
  Serial.print("%, Pressure: ");
  Serial.print(pressure);
  Serial.print(" hPa, Water Drop Sensor Value: ");
  Serial.println(waterDropValue);
//version1


  // Add code here to send the data to your server or cloud service

  delay(5000); // Delay for 5 seconds before taking the next reading
}

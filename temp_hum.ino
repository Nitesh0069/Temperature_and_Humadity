#include <DHT.h>
#include <SoftwareSerial.h>

#define DHTPIN 2       // DHT sensor data pin connected to digital pin 2
#define DHTTYPE DHT11  // DHT 11 (change to DHT22 if using that sensor)

// Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE);

// Create a SoftwareSerial object for Bluetooth communication
SoftwareSerial BTSerial(10, 11); // RX, TX for HC-05

void setup() {
  // Start the serial communication for debugging
  Serial.begin(9600);
  BTSerial.begin(9600); // Start Bluetooth communication

  // Initialize the DHT sensor
  dht.begin();
}

void loop() {
  // Wait a few seconds between measurements
  delay(2000);
  
  // Read temperature as Celsius
  float temperature = dht.readTemperature();
  // Read humidity
  float humidity = dht.readHumidity();
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
  // Print the values to the Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C, Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  // Send the temperature and humidity data via Bluetooth
  BTSerial.print("Temperature: ");
  BTSerial.print(temperature);
  BTSerial.print(" °C, Humidity: ");
  BTSerial.print(humidity);
  BTSerial.println(" %");
}


#include "DHT.h"
#include <Wire.h>
#include "Adafruit_SGP40.h"
#include <WiFi.h>

Adafruit_SGP40 sgp;
#define DHTPIN 4      // what pin we're connected to
#define DHTTYPE DHT11 // DHT 11

// Initialize DHT sensor for normal 16mhz Arduino
DHT dht(DHTPIN, DHTTYPE);

void setup()
{
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.println("Connecting...");
    }
    Serial.println("Connected to Wifi");

    Serial.println("DHTxx test!");
    while (!Serial)
    {
        delay(10);
    } // Wait for serial console to open!
    Serial.println("SGP40 test");
    if (!sgp.begin())
    {
        Serial.println("Sensor not found :(");
        while (1)
            ;
    }
    Serial.print("Found SGP40 serial #");
    Serial.print(sgp.serialnumber[0], HEX);
    Serial.print(sgp.serialnumber[1], HEX);
    Serial.println(sgp.serialnumber[2], HEX);
    dht.begin();
}

int counter = 0;

void loop()
{
    // Wait a few seconds between measurements.
    delay(2000);
    uint16_t raw;

    raw = sgp.measureRaw();

    Serial.print("Measurement SPG40: ");
    Serial.println(raw);

    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    float h = dht.readHumidity();
    // Read temperature as Celsius
    float t = dht.readTemperature();
    // Read temperature as Fahrenheit
    float f = dht.readTemperature(true);

    // Check if any reads failed and exit early (to try again).
    if (isnan(h) || isnan(t) || isnan(f))
    {
        Serial.println("Failed to read from DHT sensor!");
        return;
    }

    // Compute heat index
    // Must send in temp in Fahrenheit!
    float hi = dht.computeHeatIndex(f, h);

    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.print(" *C ");
    Serial.print(f);
    Serial.print(" *F\t");
    Serial.print("Heat index: ");
    Serial.print(hi);
    Serial.println(" *F");
}
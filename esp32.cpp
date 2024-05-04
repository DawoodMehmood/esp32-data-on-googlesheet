
#include "DHT.h"
#include <Wire.h>
#include "Adafruit_SGP40.h"
#include <WiFi.h>
#include <HTTPClient.h>

Adafruit_SGP40 sgp;
#define DHTPIN 4      // what pin we're connected to
#define DHTTYPE DHT11 // DHT 11

// Initialize DHT sensor for normal 16mhz Arduino
DHT dht(DHTPIN, DHTTYPE);

// Define your WiFi credentials
const char *ssid = "wifi-name";
const char *password = "wifi-password";

// Google Sheets API endpoint
const char *GOOGLE_APPS_SCRIPT_URL = "YOUR_GOOGLE_APPS_SCRIPT_URL";

// Function to connect to WiFi
void connectWiFi()
{
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");
}

// Function to append data to Google Sheets
void appendDataToSheet(float temperature, float humidity, float heatIndex, uint16_t rawSGP40)
{
    HTTPClient http;
    http.begin(GOOGLE_APPS_SCRIPT_URL); // Specify the endpoint for appending data

    http.addHeader("Content-Type", "application/json");

    String httpRequestData = "{\"temperature\":" + String(temperature) + ",\"humidity\":" + String(humidity) + ",\"heatIndex\":" + String(heatIndex) + ",\"rawSGP40\":" + String(rawSGP40) + "}";
    int httpResponseCode = http.POST(httpRequestData);

    if (httpResponseCode > 0)
    {
        String response = http.getString();
        Serial.println(response);
    }
    else
    {
        Serial.print("Error on sending POST: ");
        Serial.println(httpResponseCode);
    }

    http.end();
}

void setup()
{
    Serial.begin(115200);
    connectWiFi();

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

void loop()
{
    // Wait a few seconds between measurements.
    delay(2000);
    uint16_t rawSGP40;

    rawSGP40 = sgp.measureRaw();

    Serial.print("Measurement SPG40: ");
    Serial.println(rawSGP40);

    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    float humidity = dht.readHumidity();
    // Read temperature as Celsius
    float temperature = dht.readTemperature();
    // Read temperature as Fahrenheit
    float tempFahrenheit = dht.readTemperature(true);

    // Check if any reads failed and exit early (to try again).
    if (isnan(humidity) || isnan(temperature) || isnan(tempFahrenheit))
    {
        Serial.println("Failed to read from DHT sensor!");
        return;
    }

    // Compute heat index
    // Must send in temp in Fahrenheit!
    float heatIndex = dht.computeHeatIndex(tempFahrenheit, humidity);

    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.print(" %\t");
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(" *C ");
    Serial.print(tempFahrenheit);
    Serial.print(" *F\t");
    Serial.print("Heat index: ");
    Serial.print(heatIndex);
    Serial.println(" *F");

    // Append data to Google Sheets
    appendDataToSheet(temperature, humidity, heatIndex, rawSGP40);

    delay(60000); // Wait for 1 minute before sending next data point
}
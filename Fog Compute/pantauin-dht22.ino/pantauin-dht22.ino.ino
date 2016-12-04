
//library

#include <DHT.h>;
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>



//Constants DHT22
#define DHTPIN 2     // D4 in wemos d1 mini
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// initialize the DHT Sensor

//Nanopb lib

#



//Variables
float humidity;  //Humidity value will be stored here
float temperature; //Temperature (Celsius) will be stored here


void setup() {
  
  Serial.begin(9600);
  dht.begin(); // begin the dht reading
  

}

void loop() {
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
  
  // put your main code here, to run repeatedly:

}

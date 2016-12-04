
// References :
// https://blog.noser.com/arduino-iot-with-mqtt-and-nanopb/
// https://github.com/jesionaj/ESP8266-MQTT-PB


//Sensor library

#include <DHT.h>;
#include <PubSubClient.h>

//ESP8266 Library
#include <ESP8266WiFi.h>

//MQTT Library
#include <PubSubClient.h>

//NanoProtoBuf Library
#include "pb.h"
#include "pb_encode.h"
#include "pantauinMessage.pb.h"

//Constants DHT22
#define DHTPIN 2     // D4 in wemos d1 mini
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// initialize the DHT Sensor



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

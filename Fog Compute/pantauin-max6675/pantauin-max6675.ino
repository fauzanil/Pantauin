
// References :
// https://blog.noser.com/arduino-iot-with-mqtt-and-nanopb/
// https://github.com/jesionaj/ESP8266-MQTT-PB


//Sensor library
#include <max6675.h>

#include <PubSubClient.h>

//ESP8266 Library
#include <ESP8266WiFi.h>

//MQTT Library
#include <PubSubClient.h>

//NanoProtoBuf Library
#include "pb.h"
#include "pb_encode.h"
#include "pantauinMessage.pb.h"

//Constants Max6675
int ktcSO = 12;
int ktcCS = 13;
int ktcCLK = 15;

MAX6675 ktc(ktcCLK, ktcCS, ktcSO);

//Wifi Credential
const char WiFiSSID[]="TP-LINK_8378FA";
const char WiFiPSK[] = "20061962";
WiFiClient WirelessCon;

//Variables
float data; //Sensor Value will be stored here
boolean sensorStatus; //used to mark substances detection 

// MQTT config

const char SERVER[] = "192.168.0.105";
const int SERVERPORT = 1883;
#define ID "max6657"
PubSubClient client(WirelessCon);

// Pin definitions
const int LED_PIN = 5; 

void connectWiFi()
{

  // Set WiFi mode to station
  WiFi.mode(WIFI_STA);

  // Start the WiFi connection
  WiFi.begin(WiFiSSID, WiFiPSK);

  // Wait for the WiFi client to connect, blinking the LED during that time
  Serial.print("Waiting for WiFi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(100);
  }
   Serial.println("");
   Serial.println("WiFi connected");
   Serial.println("IP address: ");
   Serial.println(WiFi.localIP());
  
}

// Connect and reconnect as necessary to the MQTT server.
void mqttConnect()
{
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    
    // Attempt to connect
    if (client.connect("ESP8266Client"))
    {
      Serial.println(" Connected.");
    }
    else
    {
      Serial.print(" Failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 2 second.s");
      
      // Wait 2 seconds before retrying
      delay(2000);
    }
}
  
}

void setup() {
  
  Serial.begin(9600);



  //connect to wifi
  connectWiFi();
  
  // Setup MQTT client
  client.setServer(SERVER, SERVERPORT);  
  

}




void loop() {

   // If the wifi disconnects, we need to reconnect
  while (WiFi.status() != WL_CONNECTED)
  {
    connectWiFi();
    delay(100);
  }

  // Connect for the first time or reconnect
  mqttConnect();

  // Create byte buffer for sending out on MQTT
  uint8_t sMsg[MQTT_MAX_PACKET_SIZE];

  Pantauin message;
  message.id =2;
  message.sensorValue = ktc.readCelsius();
  message.nodeStatus = 1;

  
  // Prepare to encode nessage
  pb_ostream_t buffer = pb_ostream_from_buffer(sMsg, sizeof(sMsg));

  // Try to encode
  if (!pb_encode(&buffer, Pantauin_fields, &message)) {
    Serial.println(F("Encoding failed"));
    Serial.println(PB_GET_ERROR(&buffer));
  }
  else
  {
    // If successful, send the message out
    client.publish("temp/1", sMsg, buffer.bytes_written);
  }

  delay(200); 
}



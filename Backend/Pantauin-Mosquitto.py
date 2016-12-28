
# !/usr/bin/env python
import sys
import pantauinMessage_pb2
import paho.mqtt.client as mqtt

# This is the Subscriber

def on_connect(client, userdata, flags, rc):
    print( "Connected with result code " +str(rc))
    client.subscribe("pantauin/max6675")
    client.subscribe("pantauin/max6675s")


def message_decoder(message):
    data = pantauinMessage_pb2.Pantauin()
    data.ParseFromString(message)
    return data.id,data.sensorValue,data.nodeStatus
    #[0] for id, [1] for data, [2] for status


def on_message(client, userdata, msg):
    if (msg.payload == "Hello world!"):
        print("Yes!")
        client.disconnect()

    else:
        print(message_decoder(msg.payload)[0])




client = mqtt.Client()
client.connect("localhost" ,1883 ,60)

client.on_connect = on_connect
client.on_message = on_message

client.loop_forever()


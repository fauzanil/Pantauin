
# !/usr/bin/env python
import sys
import pantauinMessage_pb2
import paho.mqtt.client as mqtt
import rethinkdb as r

r.connect("localhost", 28015).repl()


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
    data = message_decoder(msg.payload)
    r.db("geothermal").table("log_mustikajaya").insert(
        {"nodeID": data[0], "sensorValue": data[1], "nodeStatus": data[2] }
    ).run()
    print("Data Submitted")






client = mqtt.Client()
client.connect("localhost" ,1883 ,60)

client.on_connect = on_connect
client.on_message = on_message

client.loop_forever()


import paho.mqtt.client as mqtt
import json
from influxdb import client as influxdb

db = influxdb.InfluxDBClient('54.159.204.45',8086,'iot','iot','homeDB')

server = '54.159.204.45'

def on_connect(client, userdata, flags, rc):
    print("Connected with RC : " + str(rc))
    client.subscribe('/sensor/json')

def on_message(client, userdata, msg):
	global db
	measureName = "Home_inf"
    	if(msg.topic == '/sensor/json'):
        	json_string = str(msg.payload).replace("'","\"")
	        json_bytes = json_string.encode()[2:len(json_string)-1]
        	data = json.loads(json_bytes)
	        temp = int(data["TEMP"])
	        hum = int(data["HUM"])
	        cds = int(data["Cds"])
		
		json_body = [
		{
			"measurement": measureName,
			"tags": {
				"host": "flowey",
				"region": "Siheung"
			},
			"fields": {
				"temperature": temp,
				"humidity": hum,
				"lux": cds,
			},
		}
		]
		db.write_points(json_body)
client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message
client.connect(server, 1883, 60)


while client.loop() ==0:

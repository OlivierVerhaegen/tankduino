/**
 Adafruit HUZZAH32 - ESP32 Feather
 Name: feather.ino
 Opdracht3: 
 - Feather vraagt de laatste 5 metingen van de sensoren op met een interval van 1,25s.
 - Feather stuurt de data naar deze server mqtt.luytsm.be

 @author Olivier Verhaegen
 @version 1.0.0
*/

#include <Wire.h>

#include <WiFi.h>
#include <PubSubClient.h>

#define SENSOR_I2C 8

const char* ssid = "***"; // Enter your WiFi name
const char* password =  "***"; // Enter WiFi password
const char* mqtt_server = "mqtt.luytsm.be";
const int mqtt_port = 1883;
#define mqtt_port 1883
#define MQTT_SERIAL_PUBLISH_CH "/olivierV/ESP32/sensordata/tx"
#define MQTT_SERIAL_RECEIVER_CH "/icircuit/ESP32/serialdata/rx"

WiFiClient wifiClient;

PubSubClient client(wifiClient);

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  randomSeed(micros());
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      //Once connected, publish an announcement...
      client.publish("/icircuit/presence/ESP32/", "hello world");
      // ... and resubscribe
      client.subscribe(MQTT_SERIAL_RECEIVER_CH);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void callback(char* topic, byte *payload, unsigned int length) {
  Serial.println("-------new message from broker-----");
  Serial.print("channel:");
  Serial.println(topic);
  Serial.print("data:");  
  Serial.write(payload, length);
  Serial.println();
}

void setup() {
  // Initialize I2C bus (address optional for master).
  Wire.begin();

  // Initialize Serial.
  Serial.begin(9600);
  Serial.setTimeout(500);// Set time out for wifi
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  reconnect();
  Serial.println("Feather Initialized");
}

void publishData(byte *Data){
  if (!client.connected()) {
    reconnect();
  }
  client.publish(MQTT_SERIAL_PUBLISH_CH, Data, 1);
}

void loop() {
  client.loop();
  
  Serial.println("Requesting data from sensors");
  Wire.requestFrom(SENSOR_I2C, 5);
  while(Wire.available()) {
    byte rx_data[1] = { Wire.read() };
    Serial.println(rx_data[0]);
    publishData(rx_data);
  }
  delay(1250);
}

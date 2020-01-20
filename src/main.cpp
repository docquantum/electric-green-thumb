#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <SoftwareSerial.h>
#include <WiFiEsp.h>
#include <MQTT.h>

#define PHOTO_PIN A0
#define WATER_PIN A1
#define SOIL_PIN  A2
#define DHT11_PIN 4
#define LIGHT_PIN 2
#define PUMP_PIN  3

#define RX 6
#define TX 7

typedef struct {
  int waterLevel;
  int moistureLevel;
  int lightLevel;
  float temp;
  float humidity;
} SensorData;

DHT dht(DHT11_PIN, DHT11);
SoftwareSerial esp8266(RX,TX); //Define 8266 chip serial
WiFiEspClient net;
MQTTClient client;
SensorData data;

char ssid[] = "QuantumNet X";            // your network SSID (name)
char pass[] = "onetwothreefour";        // your network password
// char fbase_url[] = "https://electric-green-thumb.firebase.io/proto.json";
// char fbase_user[] = "";
// char fbase_pass[] = "";
int status = WL_IDLE_STATUS;     // the Wifi radio's status
unsigned long lastMillis = 0;

void error(){
  digitalWrite(LED_BUILTIN, HIGH);
  delay(200);
  digitalWrite(LED_BUILTIN, LOW);
  delay(200);
}

void connect() {
  // attempt to connect to WiFi network
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network
    status = WiFi.begin(ssid, pass);
    error();
  }

  Serial.println("You're connected to the network");

  //connect to server
  while (!client.connect("proto", "wjxsyrzm", "v6CafSkZknUn")) {
    error();
    delay(1000);
  }

  Serial.println("You're connected to the server");
  client.subscribe("/command");
}

void runPump(){
  digitalWrite(PUMP_PIN, HIGH);
  delay(1000);
  digitalWrite(PUMP_PIN, LOW);
}

void testRelays(){
  Serial.println("Testing Light");
  digitalWrite(LIGHT_PIN, HIGH);
  delay(1000);
  digitalWrite(LIGHT_PIN, LOW);
  delay(1000);

  Serial.println("Testing pump");
  digitalWrite(PUMP_PIN, HIGH);
  delay(1000);
  digitalWrite(PUMP_PIN, LOW);
  delay(1000);
}

void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);
  if(payload.equals("light_on")){
    digitalWrite(LIGHT_PIN, HIGH);
  } else if(payload.equals("light_off")){
    digitalWrite(LIGHT_PIN, LOW);
  } else if(payload.equals("pump_run")){
    runPump();
  } else if(payload.equals("test_relays")){
    testRelays();
  }
}

void readData(){
  data.lightLevel = analogRead(PHOTO_PIN);
  data.moistureLevel = analogRead(SOIL_PIN);
  data.waterLevel = analogRead(WATER_PIN);
  data.temp = dht.readTemperature(true);
  data.humidity = dht.readHumidity();
}

void printData(){
  Serial.println("{");
  Serial.print("\tlight_level: "); Serial.print(data.lightLevel); Serial.println(",");
  Serial.print("\tmoisture_level: "); Serial.print(data.moistureLevel); Serial.println(",");
  Serial.print("\twater_level: "); Serial.print(data.waterLevel); Serial.println(",");
  Serial.print("\ttemperature: "); Serial.print(data.temp); Serial.println(F("°F,"));
  Serial.print("\thumidity: "); Serial.print(data.humidity); Serial.println(F("%"));
  Serial.println("}\n");
}

void sendData(){
  client.publish("/data", String("{\"light_level\" : ") + data.lightLevel
    + ", \"moisture_level\" : " + data.moistureLevel
    + ", \"water_level\" : " + data.waterLevel
    + ", \"temperature\" : " + data.temp
    + ", \"humidity\" : " + data.humidity + "}");
}

void setup() {
  pinMode(LIGHT_PIN, OUTPUT);
  pinMode(PUMP_PIN, OUTPUT);
  pinMode(DHT11_PIN, INPUT);
  pinMode(SOIL_PIN, INPUT);
  pinMode(WATER_PIN, INPUT);
  pinMode(PHOTO_PIN, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  dht.begin();
  Serial.begin(9600); //Computer Connection
  esp8266.begin(9600); //ESP8266 Connection
  delay(500);

  // Initializes the esp8266
  WiFi.init(&esp8266);

  // Set up MQTT
  client.begin("tailor.cloudmqtt.com", 10354, net);
  client.onMessage(messageReceived);

  // Connects the network
  connect();

  testRelays();
}

void loop() {
  client.loop();
  delay(20);
  if(!client.connected()){
    connect();
  }

  if (millis() - lastMillis > 10000) {
    lastMillis = millis();
    readData();
    sendData();
  }
}
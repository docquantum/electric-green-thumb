#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <SoftwareSerial.h>


#define LOW_LIGHT 150
#define AMBIENT_LIGHT 350
#define BRIGHT_LIGHT 600

#define PHOTO_PIN A0
#define WATER_PIN A1
#define SOIL_PIN  A2
#define DHT11_PIN 4
#define LIGHT_PIN 2
#define PUMP_PIN  3

#define RX 10
#define TX 11

DHT dht(DHT11_PIN, DHT11);
SoftwareSerial esp8266(RX,TX); //Define 8266 chip serial

int countTrueCommand;
int countTimeCommand; 
boolean found = false; 
int valSensor = 1;
void sendCommand(String command, int maxTime, char readReplay[]);
String AP = "iPhone";       // CHANGE ME
String PASS = "hackathon"; // CHANGE ME

void setup() {
  pinMode(LIGHT_PIN, OUTPUT);
  pinMode(PUMP_PIN, OUTPUT);
  pinMode(DHT11_PIN, INPUT);
  pinMode(SOIL_PIN, INPUT);
  pinMode(WATER_PIN, INPUT);
  pinMode(PHOTO_PIN, INPUT);
  dht.begin();
  Serial.begin(9600); //Computer Connection
  esp8266.begin(115200); //ESP8266 Connection
  delay(1000);
  //sendCommand("AT",5,"OK");
  sendCommand("AT+CWMODE=1",5,"OK");
  sendCommand("AT+CWJAP=\""+ AP +"\",\""+ PASS +"\"",20,"OK");

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

void loop() {
  Serial.print("PResistor Val= "); Serial.print(analogRead(PHOTO_PIN)); Serial.println("\n");
  Serial.print("Soil Moisture = "); Serial.print(analogRead(SOIL_PIN)); Serial.println("\n");
  Serial.print("Water level = "); Serial.print(analogRead(WATER_PIN)); Serial.println("\n");
  Serial.print(F("Temperature: "));
  Serial.print(dht.readTemperature(false,false));
  Serial.println(F("°C"));
  
  // Get humidity event and print its value.
  Serial.print(F("Humidity: "));
  Serial.print(dht.readHumidity(false));
  Serial.println(F("%\n"));
  
  if(analogRead(PHOTO_PIN) < LOW_LIGHT){
    digitalWrite(LIGHT_PIN, HIGH);
  } else{
    digitalWrite(LIGHT_PIN, LOW);
  }

  delay(1000);
}

void sendCommand(String command, int maxTime, char readReplay[]) {
  Serial.print(countTrueCommand);
  Serial.print(". at command => ");
  Serial.print(command);
  Serial.print(" ");
  while(countTimeCommand < (maxTime*1))
  {
    esp8266.println(command);//at+cipsend
    if(esp8266.find(readReplay))//ok
    {
      found = true;
      break;
    }
  
    countTimeCommand++;
  }
  
  if(found == true)
  {
    Serial.println("OYI");
    countTrueCommand++;
    countTimeCommand = 0;
  }
  
  if(found == false)
  {
    Serial.println("Fail");
    countTrueCommand = 0;
    countTimeCommand = 0;
  }
  
  found = false;
 }
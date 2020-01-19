#include <Arduino.h>
#include "DHT.h"
#include <Adafruit_Sensor.h>

#define LIGHT_PIN   23  //D_out
#define PUMP_PIN    22  //D_out (inverted)
#define DHT11_PIN   32  //D_in/out
#define SOIL_PIN    39  //A_in
#define WATER_PIN   34  //A_in
#define PHOTO_PIN   36  //A_in

DHT dht(DHT11_PIN, DHT11);

void setup() {
  pinMode(LIGHT_PIN, OUTPUT);
  pinMode(PUMP_PIN, OUTPUT);
  pinMode(DHT11_PIN, INPUT);
  pinMode(SOIL_PIN, INPUT);
  pinMode(WATER_PIN, INPUT);
  pinMode(PHOTO_PIN, INPUT);
  dht.begin();
  Serial.begin(9600);
  delay(1000);

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
  
  if(analogRead(PHOTO_PIN) < 1200){
    digitalWrite(LIGHT_PIN, HIGH);
  } else{
    digitalWrite(LIGHT_PIN, LOW);
  }

  delay(1000);
}
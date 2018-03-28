// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain

#include "DHT.h"

#define DHTPIN 2     // what digital pin we're connected to

#define DHTTYPE DHT11   // DHT 11

// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT dht(DHTPIN, DHTTYPE);
int button = 3;
int buttonState = 0;
int state = 0;


float t;
float h;

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(3,INPUT);
}

void loop() {
  buttonState = digitalRead(button);
  if(buttonState == HIGH){
    if(state == 1){
      state = 0;
    }
    else{
      state++; 
    }
  }
  if(state == 0){
    float t = dht.readTemperature();
    delay(300);
    if (isnan(t)) {
      Serial.println("Failed to read TEMP !");
      return;
    }
    else{
      Serial.print("Temperature: ");
      Serial.print(t);
      Serial.println(" *C ");
    }
  }
  else if(state == 1){
    float h = dht.readHumidity();
    delay(300);
    if (isnan(h)) {
      Serial.println("Failed to read HUMIDITY !");
      return;
    }
    else{
      Serial.print("Humidity: ");
      Serial.println(h);
    } 
  }
}

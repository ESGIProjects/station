#include "DHT.h"
#include <ESP8266WiFi.h>
#include <time.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
int button = 3;
int buttonState = 0;
int state = 0;

float t;
float h;

String humidity;
String temp;

const char* ssid = "ESGI";
const char* password = "Reseau-GES";

int timezone = 3;
int dst = 0;

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  dht.begin();
  pinMode(3,INPUT);
/*
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("\nConnecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  configTime(3 * 3600, 0, "pool.ntp.org", "time.nist.gov");
  Serial.println("\nWaiting for time");
  while (!time(nullptr)) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("");*/
}

void loop() {

  time_t now = time(nullptr);
  //Serial.print(hour(now));
  Serial.println(ctime(&now));
  delay(1000);

  /*
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
      temp = "t-" + (String)t + "$";
      Serial.print("Temperature: ");
      Serial.print(t);
      Serial.println("C");
      writeString(temp);
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
      humidity = "h-" + (String)h + "$";
      Serial.print("Humidity: ");
      Serial.print(h);
      Serial.println("%");
      writeString(humidity);
    } 
  }
  delay(1000);*/
}

void writeString(String data){
  for(int i = 0; i < data.length(); i++){
    Serial1.write(data[i]);
  }
  Serial1.write('\0');
}

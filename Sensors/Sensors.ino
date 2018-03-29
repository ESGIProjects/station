#include "DHT.h"

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

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  dht.begin();
  pinMode(3,INPUT);
}

void loop() {
  if(Serial1.available() > 0){
    Serial.println(Serial1.read());
  }

  /*buttonState = digitalRead(button);
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

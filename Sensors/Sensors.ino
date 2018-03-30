#include "DHT.h"

// Setting up the DHT
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Pin used by the other sensors
#define button  3
#define buzzer  4

// States that the program can have
#define TIME        0
#define TEMPERATURE 1
#define HUMIDITY    2

int buttonState = 0, state = TIME;

float t, h;
String humidity, temp, currentTime;

// Global variables for receiving
char bytes[15];
int incomingByte = 0, index = 0;

void setup() {
  // Setting up pin mode for each
  pinMode(button, INPUT);
  pinMode(buzzer, OUTPUT);

  // Init Serial connection
  Serial.begin(9600);
  Serial1.begin(9600);

  // Needed on Leonardo board
  while (!Serial) { }
  while (!Serial1) { }

  // Connection to the DHT sensor
  dht.begin();
}

void loop() {
  // Read the current button state
  buttonState = digitalRead(button);
  
  if (buttonState == HIGH) {
    // Buzz and change program's state
    tone(buzzer, 800);
    delay(500);
    noTone(buzzer);

    state = (state + 1) % 3; // clean-up test

    /*
    if(state == 2){
      state = 0;
    }
    else{
      state++; 
    }
    */
  }

  switch (state) {
    case TIME:

      // Receive new data from the Wemos
      if (Serial1.available() > 0) {
        
        incomingByte = Serial1.read();
        bytes[index++] = incomingByte;

        // If the sequence is over, send the new time data
        if (incomingByte == '\0') {
          currentTime = "d" + String(bytes);
          Serial.println(currentTime);
          writeString(currentTime);
        }
      }
      break;

    case TEMPERATURE:

      t = dht.readTemperature();
      delay(300);

      if (isnan(t)) {
        Serial.println("Failed to read TEMP!");
        return;
      }
      else {
        temp = "t" + String(t); // to try: format the float with something like %.0f
        
        Serial.print("Temperature: ");
        Serial.print(t);
        Serial.println("C");

        // Send data
        writeString(temp);
      }
      
      break;

    case HUMIDITY:

      h = dht.readHumidity();
      delay(300);

      if (isnan(h)) {
        Serial.println("Failed to read HUMIDITY!");
        return;
      }
      else {
        humidity = "h" + String(h); 

        Serial.print("Humidity: ");
        Serial.print(h);
        Serial.println("%");

        // Send data
        writeString(humidity);
      }
    
      break;
    
  }

  // Wait 1s before sending new data
  delay(1000);
}

void writeString(String data){

  // Send each character of the string as a byte
  for(int i = 0; i < data.length(); i++){
    Serial1.write(data[i]);
  }

  // Send end sequence
  Serial1.write('\0');
}

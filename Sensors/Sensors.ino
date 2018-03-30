#include "DHT.h"
#include <ps2.h>
#include <Mouse.h>

// Setting up the DHT
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

//Setting up the touchpad
#define PS2_DATA 10
#define PS2_CLK 9
PS2 mouse(PS2_CLK, PS2_DATA);

// Pin used by the other sensors
#define button  3
#define buzzer  4

byte mstat1;
byte mstat2;
byte mxy;
byte mx;
byte my;
byte mz;
uint16_t msval[3];
uint16_t repeatCnt;

int buttonState = 0;
bool state = true;

float t, h;
String humidity, temp, currentTime;

// Global variables for receiving
char bytes[15];
int incomingByte = 0, index = 0;

unsigned long lastSensorReading = 0, now = 0, intervalBetweenReadings = 300;

void setup() {
  // Setting up pin mode for each
  pinMode(button, INPUT);
  pinMode(buzzer, OUTPUT);

  // Init Serial connection
  Serial.begin(9600);
  Serial1.begin(9600);
  Mouse.begin();

  // Needed on Leonardo board
  while (!Serial) { }
  while (!Serial1) { }

  // Connection to the DHT sensor
  dht.begin();

  // Init the mouse
  mouse_init(&mouse);
}

void loop() {
  char mstat;
  delay(10);
  mouse.write(0xeb);
  mouse.read();
  mstat = mouse.read();
  mouse.read();
  mouse.read();
  if(mstat & (1 << 0) || mstat & (1 << 1)){
    /*tone(buzzer, 800);
    delay(500);
    noTone(buzzer);*/
    state = !state;
  }
  else{
    Mouse.release();
  }


  // Read the current button state
  buttonState = digitalRead(button);
  
  if (buttonState == HIGH) {
    // Buzz and change program's state
    tone(buzzer, 800);
    delay(500);
    noTone(buzzer);
    state = !state;
  }

  switch (state) {
    case true:
      t = dht.readTemperature();
      now = millis();
      if (now - lastSensorReading >= intervalBetweenReadings) {
  
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
      }
      
      break;

    case false:

      h = dht.readHumidity();
      
      now = millis();
      if (now - lastSensorReading >= intervalBetweenReadings) {
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
      }
      break;
  }
  // Wait 1s before sending new data
  delay(200);
}

void writeString(String data){
  // Send each character of the string as a byte
  for(int i = 0; i < data.length(); i++){
    Serial1.write(data[i]);
  }
  // Send end sequence
  Serial1.write('\0');
}

void mouse_init(PS2 *mouse) {
    mouse->write(0xff);  // reset
    mouse->read();  // ack byte
    mouse->read();  // blank */
    mouse->read();  // blank */
    mouse->write(0xf0);  // remote mode
    mouse->read();  // ack
    delayMicroseconds(100);
}

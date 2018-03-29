#include <ESP8266WiFi.h>
#include <time.h>

const char* ssid = "ESGI";
const char* password = "Reseau-GES";

time_t now;
struct tm *now_tm;
int hour;
int minute;

int timezone = 1;
int dst = 0;

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);

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
  Serial.println("");
}

void loop() {
  now = time(NULL);
  now_tm = localtime(&now);
  hour = now_tm->tm_hour;
  minute = now_tm->tm_min;
  Serial1.write(hour);
  Serial1.write(minute);
  delay(1000);
}

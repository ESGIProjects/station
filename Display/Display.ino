#include <SoftwareSerial.h>

int d1 = 13;
int d2 = 10;
int d3 = 9;
int d4 = 7;
int segA = 12;
int segB = 8;
int segC = 5;
int segD = 3;
int segE = 2;
int segF = 11;
int segG = 6;
int dot = 4;

void setup() {
  // put your setup code here, to run once:
  /*pinMode(d1, OUTPUT);
  pinMode(d2, OUTPUT);
  pinMode(d3, OUTPUT);
  pinMode(d4, OUTPUT);
  pinMode(segA, OUTPUT);
  pinMode(segB, OUTPUT);
  pinMode(segC, OUTPUT);
  pinMode(segD, OUTPUT);
  pinMode(segE, OUTPUT);
  pinMode(segF, OUTPUT);
  pinMode(segG, OUTPUT); */

  Serial.begin(9600);
  Serial1.begin(9600);

  while (!Serial1) { }
  
}

char bytes[15];
int index = 0;
int inByte = 0;

void loop() {
  if (Serial1.available() > 0) {

    inByte = Serial1.read();
    bytes[index++] = inByte;

    if (inByte == '\0') {
      String str = String(bytes);
      Serial.println(str);

      str2display(str);      
      index = 0;
    }    
  }
}

void writeDigit(int screen, int digit) {

 if (screen < 1 || screen > 4) return;
 if (digit < 0 || digit > 9) return;

 switch (screen) {
  case 1:
    digitalWrite(d1, LOW);
    digitalWrite(d2, HIGH);
    digitalWrite(d3, HIGH);
    digitalWrite(d4, HIGH);
    break;

    case 2:
    digitalWrite(d1, HIGH);
    digitalWrite(d2, LOW);
    digitalWrite(d3, HIGH);
    digitalWrite(d4, HIGH);
    break;

    case 3:
    digitalWrite(d1, HIGH);
    digitalWrite(d2, HIGH);
    digitalWrite(d3, LOW);
    digitalWrite(d4, HIGH);
    break;

    case 4:
    digitalWrite(d1, HIGH);
    digitalWrite(d2, HIGH);
    digitalWrite(d3, HIGH);
    digitalWrite(d4, LOW);
    break;
    
    default:
    break;
  
 }

  switch (digit) {
    case 0: // A B C D E F
    digitalWrite(segA, HIGH);
  digitalWrite(segB, HIGH);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, HIGH);
  digitalWrite(segE, HIGH);
  digitalWrite(segF, HIGH);
  digitalWrite(segG, LOW);
  break;

  case 1: // B C
    digitalWrite(segA, LOW);
  digitalWrite(segB, HIGH);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, LOW);
  digitalWrite(segE, LOW);
  digitalWrite(segF, LOW);
  digitalWrite(segG, LOW);
  break;

  case 2: // A B D E G
   digitalWrite(segA, HIGH);
  digitalWrite(segB, HIGH);
  digitalWrite(segC, LOW);
  digitalWrite(segD, HIGH);
  digitalWrite(segE, HIGH);
  digitalWrite(segF, LOW);
  digitalWrite(segG, HIGH);
  break;

  case 3: // A B C D G
   digitalWrite(segA, HIGH);
  digitalWrite(segB, HIGH);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, HIGH);
  digitalWrite(segE, LOW);
  digitalWrite(segF, LOW);
  digitalWrite(segG, HIGH);
  break;

  case 4: // B C F G
   digitalWrite(segA, LOW);
  digitalWrite(segB, HIGH);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, LOW);
  digitalWrite(segE, LOW);
  digitalWrite(segF, HIGH);
  digitalWrite(segG, HIGH);
  break;

  case 5: // A C D F G
  digitalWrite(segA, HIGH);
  digitalWrite(segB, LOW);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, HIGH);
  digitalWrite(segE, LOW);
  digitalWrite(segF, HIGH);
  digitalWrite(segG, HIGH);
  break;

  case 6: // A C D E F G
    digitalWrite(segA, HIGH);
  digitalWrite(segB, LOW);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, HIGH);
  digitalWrite(segE, HIGH);
  digitalWrite(segF, HIGH);
  digitalWrite(segG, HIGH);
  break;

  case 7: // A B C
    digitalWrite(segA, HIGH);
  digitalWrite(segB, HIGH);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, LOW);
  digitalWrite(segE, LOW);
  digitalWrite(segF, LOW);
  digitalWrite(segG, LOW);
  break;

  case 8: // A B C D E F G
    digitalWrite(segA, HIGH);
  digitalWrite(segB, HIGH);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, HIGH);
  digitalWrite(segE, HIGH);
  digitalWrite(segF, HIGH);
  digitalWrite(segG, HIGH);
  break;

  case 9: // A B C D F G
    digitalWrite(segA, HIGH);
  digitalWrite(segB, HIGH);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, HIGH);
  digitalWrite(segE, LOW);
  digitalWrite(segF, HIGH);
  digitalWrite(segG, HIGH);
  break;

  default:
  break;
  }

  delay(1);
}

void str2display(String str) {

      char type = str.charAt(0);
      //char type = (char)bytes[0];
      Serial.println(type);

      int value1, value2, value3, value4;

      switch (type) {
        case 'h':
          value1 = (int)bytes[2] - 48;
          value2 = (int)bytes[3] - 48;

          writeDigit(2, value1);
          //writeDigit(3, value2);
          // afficher H
        case 't':
          value1 = (int)bytes[2] - 48;
          value2 = (int)bytes[3] - 48;

          writeDigit(2, value1);
          writeDigit(3, value2);
          // afficher C
        case 'd':
          value1 = (int)bytes[2] - 48;
          value2 = (int)bytes[3] - 48;
          value3 = (int)bytes[4] - 48;
          value4 = (int)bytes[5] - 48;

          writeDigit(1, value1);
          writeDigit(2, value2);
          writeDigit(3, value3);
          writeDigit(4, value4);
        default:
          break;
      }
}

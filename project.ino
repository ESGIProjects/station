#include <Time.h>

int pinButton = 13;
int previousState = 1;
int stateButton = 0;
int choice = 0;

/*int pinA = 2;
int pinB = 3;
int pinC = 4;
int pinD = 5;
int pinE = 6;
int pinF = 7;
int pinG = 8;
int D1 = 9;
int D2 = 10;
int D3 = 11;
int D4 = 12;*/

int pinA = 6;
int pinB = 7;
int pinC = 8;
int pinD = 9;
int pinE = 10;
int pinF = 11;
int pinG = 12;
int D1 = 2;
int D2 = 3;
int D3 = 4;
int D4 = 5;

void setup() {
  Serial.begin(9600);
  pinMode(pinA, OUTPUT);     
  pinMode(pinB, OUTPUT);     
  pinMode(pinC, OUTPUT);     
  pinMode(pinD, OUTPUT);     
  pinMode(pinE, OUTPUT);     
  pinMode(pinF, OUTPUT);     
  pinMode(pinG, OUTPUT);   
  pinMode(D1, OUTPUT);  
  pinMode(D2, OUTPUT);  
  pinMode(D3, OUTPUT);  
  pinMode(D4, OUTPUT);
  pinMode(pinButton, INPUT);
}

void loop() {
  stateButton = analogRead(pinButton);
  
  if(choice == 0){
    
  }
  else if(choice == 1){
    
  }
  else if(choice == 2){
    
  }
  else{
    
  }
  
  if (stateButton == HIGH) {
    digit0();
  }
  else {
    digit1();
  }
}

void digit0(){
  digitalWrite(D1, HIGH);
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);
  digitalWrite(D4, LOW); 
  digitalWrite(pinA, LOW);   
  digitalWrite(pinB, HIGH);   
  digitalWrite(pinC, LOW);   
  digitalWrite(pinD, LOW);   
  digitalWrite(pinE, HIGH);   
  digitalWrite(pinF, LOW);   
  digitalWrite(pinG, LOW);   
  delay(1);   
}

void digit1(){
  digitalWrite(D1, LOW);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, LOW);
  digitalWrite(D4, LOW); 

  digitalWrite(pinA, LOW);   
  digitalWrite(pinB, LOW);   
  digitalWrite(pinC, LOW);   
  digitalWrite(pinD, HIGH);   
  digitalWrite(pinE, LOW);   
  digitalWrite(pinF, LOW);   
  digitalWrite(pinG, LOW);   
  delay(1);     
}

void changeDisplay(){
  Serial1.print("time");
  Serial1.print("temp");
  Serial1.print("pression");
  Serial1.print("humidity");  
}

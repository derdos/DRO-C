#include <homepanel.h>
#include <panel.h>
#include <parent.h>
#include <EEPROMmod.h>
#include <dro.h>
#include <slcd.h>
 
// Encoder Pin Positions.
#define Encoder1PinA  19//2
#define Encoder1PinB  42
#define Encoder2PinA  3
#define Encoder2PinB  48
#define Encoder3PinA  20
#define Encoder3PinB  38
#define Encoder4PinA  21
#define Encoder4PinB  46
#define Temp          2

long Encoder1 = 0;

void setup()
{
  pinMode(Encoder1PinA, INPUT);
  digitalWrite(Encoder1PinA,HIGH);
  pinMode(Encoder1PinB, INPUT);
  digitalWrite(Encoder1PinB,HIGH);
  pinMode(Encoder2PinA, INPUT);
  digitalWrite(Encoder2PinA,HIGH);
  pinMode(Encoder2PinB, INPUT);
  digitalWrite(Encoder2PinB,HIGH);
  pinMode(Encoder3PinA, INPUT);
  digitalWrite(Encoder3PinA,HIGH);
  pinMode(Encoder3PinB, INPUT);
  digitalWrite(Encoder3PinB,HIGH);
  pinMode(Encoder4PinA, INPUT);
  digitalWrite(Encoder4PinA,HIGH);
  pinMode(Encoder4PinB, INPUT);
  digitalWrite(Encoder4PinB,HIGH);
  pinMode(Temp, INPUT);
  digitalWrite(Temp,HIGH);
  
  pinMode(A8, INPUT);           // set pin to input
  digitalWrite(A8, HIGH);       // turn on pullup resistors
  pinMode(A9, INPUT);        
  digitalWrite(A9, HIGH); 
  pinMode(A10, INPUT);        
  digitalWrite(10, HIGH); 
  pinMode(A11, INPUT);        
  digitalWrite(A11, HIGH);   
  
  attachInterrupt(4, Encoder1Int, CHANGE); //0 for pin 2, 4 for pin 19
  attachInterrupt(1, Encoder2Int, CHANGE); 
  attachInterrupt(3, Encoder3Int, CHANGE);
  attachInterrupt(2, Encoder4Int, CHANGE);
  
  Serial3.begin(115200);
  Serial.begin(115200);
  
  Serial.println("RESET");
  
  Parent parent;
  HomePanel homePanel(&parent);
  parent.setHomePanel(&homePanel);
  parent.run();
}
 
void loop()
{} 

//X Encoder
void Encoder1Int(){
  if (digitalRead(Encoder1PinA) == HIGH){
    if (digitalRead(Encoder1PinB) == LOW)
      DRO::incXCnt();
    else
      DRO::decXCnt();
  }
  else{ 
    if (digitalRead(Encoder1PinB) == LOW)
      DRO::decXCnt();
    else
      DRO::incXCnt();
  }
}

//Y Encoder
void Encoder2Int(){
  if (digitalRead(Encoder2PinA) == HIGH) {
    if (digitalRead(Encoder2PinB) == LOW)
      DRO::incYCnt();
    else
      DRO::decYCnt();
  }
  else { 
    if (digitalRead(Encoder2PinB) == LOW)
      DRO::decYCnt();
    else
      DRO::incYCnt();
  }
}

//Z Encoder
void Encoder3Int(){
  if (digitalRead(Encoder3PinA) == HIGH){
    if (digitalRead(Encoder3PinB) == LOW)
      DRO::incZCnt();
    else
      DRO::decZCnt();
  }
  else{ 
    if (digitalRead(Encoder3PinB) == LOW)
      DRO::decZCnt();
    else
      DRO::incZCnt();
  }
}

//R Encoder
void Encoder4Int(){
  // Read for data and bit changes
  // This is gray-code logic
  if (digitalRead(Encoder4PinA) == HIGH){
    if (digitalRead(Encoder4PinB) == LOW)
      DRO::incRCnt();
    else
      DRO::decRCnt();
  }
  else{ 
    if (digitalRead(Encoder4PinB) == LOW)
      DRO::decRCnt();
    else
      DRO::incRCnt();
  }
}


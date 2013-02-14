#include "Charliplexing.h"

#define SCREENX 14
#define SCREENY 9
#define RULESIZE 8

int rule = 30;
int row = 0;
int offset = 0;

byte buffer[SCREENX+2][SCREENY];
byte rules[8];


// This function is called once, when the sketch starts.
void setup() {
  LedSign::Init(GRAYSCALE);
  Serial.begin(9600);
  randomSeed(analogRead(0));
  
  byte b = 0;
  
  bitWrite(b, 2, 1);
  
  for(int i = 0; i < 8; i++){
    rules[i] = bitRead(rule, i);
    Serial.println(rules[i]);
  }
  
  Serial.println(b);
  
  for(int i = 0; i < SCREENX; i++){
    buffer[i][row] = random(2);
  }
  row++;
}



// This function is called every frame.
void loop() {
  
  for(int i = 0; i < SCREENX; i++){
    byte sample = 0;
    bitWrite(sample, 2, buffer[i][row-1]);
    bitWrite(sample, 1, buffer[i+1][row-1]);
    bitWrite(sample, 0, buffer[i+2][row-1]);
    Serial.print("Sample: ");
    Serial.println(sample);
    
    buffer[i + 1][row] = rules[sample];
  }
  
  for(int i = 0; i < SCREENX; i++){
    for(int j = 0; j < SCREENY; j++){
      LedSign::Set( i, j, buffer[i+1][j]);
    }
  }
  if(row < SCREENY-1){
    row++;
  }
  else{
    for(int i = 0; i < SCREENX+2; i++){
      for(int j = 0; j < SCREENY; j++){
        buffer[i][j-1] = buffer[i][j];
      }
    }
  }
  //delay(1000);
}


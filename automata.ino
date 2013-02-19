#include "Charliplexing.h"

#define SCREENX 14
#define SCREENY 9
#define RULESIZE 8
#define MAX 1000

int rule = 110;
int row = 0;
int offset = 0;

byte buffer[SCREENX][SCREENY];
byte rules[8];


// This function is called once, when the sketch starts.
void setup() {
  LedSign::Init(GRAYSCALE);
  randomSeed(analogRead(0));
  
  reset();
  
  row++;
}



// This function is called every frame.
void loop() {
  
  for(int i = 1; i < SCREENX; i++){
    byte sample = 0;
    bitWrite(sample, 2, buffer[(i-1 + SCREENX) % SCREENX][row-1]);
    bitWrite(sample, 1, buffer[i][row-1]);
    bitWrite(sample, 0, buffer[(i+1) % SCREENX][row-1]);
    
    buffer[i][row] = rules[sample];
  }
  
  for(int i = 0; i < SCREENX; i++){
    for(int j = 0; j < SCREENY; j++){
      LedSign::Set( i, j, buffer[i][j]);
    }
  }
  if(row < SCREENY-1){
    row++;
  }
  else{
    for(int i = 0; i < SCREENX; i++){
      for(int j = 0; j < SCREENY; j++){
        buffer[i][j-1] = buffer[i][j];
      }
    }
  }
  if(row > MAX){
    rule = random(256);
    reset();
  }
  delay(200);
}

void reset(){
  row = 0;
  
  for(int i = 0; i < 8; i++){
    rules[i] = bitRead(rule, i);
  }
  
  for(int i = 0; i < SCREENX; i++){
    for(int j = 1; j < SCREENY; j++){
      buffer[i][j] = 0;
    }
  }
  
  for(int i = 0; i < SCREENX; i++){
    buffer[i][row] = random(2);
  }
  //buffer[(SCREENX+MARGINS)/2][0] = 1;
}


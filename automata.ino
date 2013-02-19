/*
    LOL Automata for the Arduino Micro-Controller
    Copyright (C) 2013 John Ericksen

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see http://www.gnu.org/licenses/.
*/

#include "Charliplexing.h"

#define SCREENX 14
#define SCREENY 9
#define RULESIZE 8
#define MAX 1000

int rule = 30;
int row = 0;
int offset = 0;

byte buffer[SCREENX][SCREENY];
byte rules[8];

void setup() {
  LedSign::Init(GRAYSCALE);
  randomSeed(analogRead(0));
  reset();
}



// This function is called every frame.
void loop() {
  
  //update the last row, based on rule interpretation of the previous row
  for(int i = 1; i < SCREENX; i++){
    byte sample = 0;
    bitWrite(sample, 2, buffer[(i-1 + SCREENX) % SCREENX][row-1]);
    bitWrite(sample, 1, buffer[i][row-1]);
    bitWrite(sample, 0, buffer[(i+1) % SCREENX][row-1]);
    
    buffer[i][row] = rules[sample];
  }
  
  //update the entire LedSign
  for(int i = 0; i < SCREENX; i++){
    for(int j = 0; j < SCREENY; j++){
      LedSign::Set( i, j, buffer[i][j]);
    }
  }
  if(row < SCREENY-1){
    //move the row down (until it reaches the end of the screen)
    row++;
  }
  else{
    //move the screen up
    for(int i = 0; i < SCREENX; i++){
      for(int j = 0; j < SCREENY; j++){
        buffer[i][j-1] = buffer[i][j];
      }
    }
  }
  if(row > MAX){
    //reset and choose a new rule if MAX is hit.
    rule = random(256);
    reset();
  }
  delay(200);
}

void reset(){
  row = 0;
  
  //setup the rules based on wolfram notation
  for(int i = 0; i < 8; i++){
    rules[i] = bitRead(rule, i);
  }
  
  //clear the buffer
  for(int i = 0; i < SCREENX; i++){
    for(int j = 1; j < SCREENY; j++){
      buffer[i][j] = 0;
    }
  }
  
  //set the last row to a random sample
  for(int i = 0; i < SCREENX; i++){
    buffer[i][row] = random(2);
  }
  row = 1;
}


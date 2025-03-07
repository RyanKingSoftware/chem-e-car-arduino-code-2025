// Chem-E-Car Main Code
// Author: Ryan King
// 3/4/2025

#include <Wire.h>

#include "bh1750.h"
#include "moving_average.h"

MovingAverage<double, 5> bh1750Sma;
BH1750 bh1750;

#define START_SWITCH 11
#define MOTOR_SWITCH 13

void setup() {
  Serial.begin(9600);
  Serial.println("Setup");
  
  Wire.begin();

  pinMode(START_SWITCH, INPUT);
  pinMode(MOTOR_SWITCH , OUTPUT);
  digitalWrite(MOTOR_SWITCH, LOW);
  
  bh1750.init();
}

const int delayMilliseconds = 500;
const int stoppingThreshhold = 150;

bool isStopped = false;
bool isRunning = false;

void loop() {
  bh1750Sma.insert(bh1750.read());

  if(digitalRead(START_SWITCH) == HIGH && !isRunning && !isStopped)
  {
    isRunning = true;
    digitalWrite(MOTOR_SWITCH, HIGH);
  }

  if(bh1750Sma.getAverage() < stoppingThreshhold  && isRunning)
  {
    isStopped = true;
    isRunning = false;
    digitalWrite(MOTOR_SWITCH, LOW);
  }
  
  showState();
  
  delay(delayMilliseconds);
}

void showState() {
  Serial.print(bh1750Sma.getAverage());
  Serial.print(" ");
  Serial.print(isRunning);
  Serial.print(" ");
  Serial.println(isStopped);
}

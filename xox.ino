#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4Motors motors;
Zumo32U4IMU imu;
Zumo32U4OLED display;
Zumo32U4ButtonA buttonA;
Zumo32U4ButtonB buttonB;
Zumo32U4ButtonC buttonC;
Zumo32U4Buzzer buzzer;
Zumo32U4LineSensors lineSensors;

#include "TurnSensor.h"

#define NUM_SENSORS 5
uint16_t lineSensorValues[NUM_SENSORS];
bool useEmitters = true;
uint8_t selectedSensorIndex = 0;

String row1[3] = {".", ".", "."};
String row2[3] = {".", ".", "."};
String row3[3] = {".", ".", "."};

bool moveDone = true;
bool start = true;

bool won = false;

int xTarget = 0;
int yTarget = 0;

int xCurrent = 2;
int yCurrent = 3;

int speed = 120;

String direction = "north";
int32_t angle = 0;

void printBoard(){
  Serial1.print("------------------------------------------");
  Serial1.print('\n');

  for (int i = 0; i < 3; i++) {
    Serial1.print("[" + row1[i] + "]");
	}
	Serial1.print('\n');
	for (int i = 0; i < 3; i++) {
		Serial1.print("[" + row2[i] + "]");
	}
	Serial1.print('\n');
	for (int i = 0; i < 3; i++) {
	Serial1.print("[" + row3[i] + "]");
	}
	Serial1.print('\n');
}

void inputMove(){
  //take input from arduino and set move to the board

  char input;

  if (Serial1.available() > 0) {
    input = Serial1.read();
        Serial1.print(input);
        Serial1.print('\n');
        switch(input)
        {
        case 'q':   
            if(row1[0] == "."){
              row1[0] = "x";
              //printBoard();
              moveDone = true;
            }
            break;
        case 'w':   
            if(row1[1] == "."){
              row1[1] = "x";
              //printBoard();
              moveDone = true;
            }
            break;
        case 'e':   
            if(row1[2] == "."){
              row1[2] = "x";
             // printBoard();
              moveDone = true;
            }
            break;
        case 'a':   
            if(row2[0] == "."){
              row2[0] = "x";
              //printBoard();
              moveDone = true;
            }
            break;
        case 's':   
            if(row2[1] == "."){
              row2[1] = "x";
              //printBoard();
              moveDone = true;
            }
            break;
        case 'd':   
            if(row2[2] == "."){
              row2[2] = "x";
              //printBoard();
              moveDone = true;
            }
            break;
        case 'z':   
            if(row3[0] == "."){
              row3[0] = "x";
              //printBoard();
              moveDone = true;
            }
            break;
        case 'x':   
            if(row3[1] == "."){
              row3[1] = "x";
              printBoard();
              moveDone = true;
            }
            break;
        case 'c':   
            if(row3[2] == "."){
              row3[2] = "x";
              //printBoard();
              moveDone = true;
            }
            break;
    } 
  }
}

void cpuMove(){

  //calc how many Os in each row, col and diagonal 

  int row1c = 0;
  int row2c = 0;
  int row3c = 0;

  int col1c = 0;
  int col2c = 0;
  int col3c = 0;

  int diag1c = 0;
  int diag2c = 0;

  if(row1[0] == "o"){
    col1c += 1;
    diag2c +=1;
    row1c +=1;
  }
  if(row2[0] == "o"){
    col1c += 1;
    row2c += 1;
  }
  if(row3[0] == "o"){
    col1c += 1;
    diag1c +=1;
    row3c +=1;
  }
  if(row1[1] == "o"){
    col2c += 1;
    row1c +=1;
  }
  if(row2[1] == "o"){
    col2c += 1;
    diag2c +=1;
    diag1c +=1;
    row2c += 1;
  }
  if(row3[1] == "o"){
    col2c += 1;
    row3c +=1;
  }
  if(row1[2] == "o"){
    col3c += 1;
    row1c +=1;
    diag1c +=1;
  }
  if(row2[2] == "o"){
    col3c += 1;
    row2c += 1;
  }
  if(row3[2] == "o"){
    col3c += 1;
    diag2c +=1;
    row3c +=1;
  }


  bool moveMade = false;

  //for each potentionalcpu win, add win to board and set movement target

  if(row1c == 2 && !moveMade){
    for (int i = 0; i < 3; i++) {
      if(row1[i] == "."){
        row1[i] = "o";
        moveMade = true;
        printBoard();
        xTarget = i+1;
        yTarget = 1;
      }
    }
  }
  if(row2c == 2 && !moveMade){
    for (int i = 0; i < 3; i++) {
      if(row2[i] == "."){
        row2[i] = "o";
        moveMade = true;
        printBoard();
        xTarget = i+1;
        yTarget = 2;
      }
    }
  }
  if(row3c == 2 && !moveMade){
    for (int i = 0; i < 3; i++) {
      if(row3[i] == "."){
        row3[i] = "o";
        moveMade = true;
        printBoard();
        xTarget = i+1;
        yTarget = 3;
      }
    }
  }

  if(col1c == 2 && !moveMade){
    if(row1[0] == "."){
      row1[0] = "o";
      moveMade = true;
      printBoard();
      xTarget = 1;
      yTarget = 1;
      
    }
    if(row2[0] == "."){
      row2[0] = "o";
      moveMade = true;
      printBoard();
      xTarget = 1;
      yTarget = 2;
    }
    if(row3[0] == "."){
      row3[0] = "o";
      moveMade = true;
      printBoard();
      xTarget = 1;
      yTarget = 3;
    }
  }
  if(col2c == 2 && !moveMade){
    if(row1[1] == "."){
      row1[1] = "o";
      moveMade = true;
      printBoard();
      xTarget = 1+1;
      yTarget = 1;

    }
    if(row2[1] == "."){
      row2[1] = "o";
      moveMade = true;
      printBoard();
      xTarget = 1+1;
      yTarget = 2;
    }
    if(row3[1] == "."){
      row3[1] = "o";
      moveMade = true;
      printBoard();
      xTarget = 1+1;
      yTarget = 3;
    }
  }
  if(col3c == 2 && !moveMade){
    if(row1[2] == "."){
      row1[2] = "o";
      moveMade = true;
      printBoard();
      xTarget = 2+1;
      yTarget = 1;
    }
    if(row2[2] == "."){
      row2[2] = "o";
      moveMade = true;
      printBoard();
      xTarget = 2+1;
      yTarget = 2;
    }
    if(row3[2] == "."){
      row3[2] = "o";
      moveMade = true;
      printBoard();
      xTarget = 2+1;
      yTarget = 3;
    }
  }

  if(diag1c == 2 && !moveMade){
    if(row1[2] == "."){
      row1[2] = "o";
      moveMade = true;
      printBoard();
      xTarget = 2+1;
      yTarget = 1;
    }
    if(row2[1] == "."){
      row2[1] = "o";
      moveMade = true;
      printBoard();
      xTarget = 1+1;
      yTarget = 2;
    }
    if(row3[0] == "."){
      row3[0] = "o";
      moveMade = true;
      printBoard();
      xTarget = 0+1;
      yTarget = 3;
    }
  }

  if(diag2c == 2 && !moveMade){
    if(row1[0] == "."){
      row1[0] = "o";
      moveMade = true;
      printBoard();
      xTarget = 0+1;
      yTarget = 1;
    }
    if(row2[1] == "."){
      row2[1] = "o";
      moveMade = true;
      printBoard();
      xTarget = 1+1;
      yTarget = 2;
    }
    if(row3[2] == "."){
      row3[2] = "o";
      moveMade = true;
      printBoard();
      xTarget = 2+1;
      yTarget = 3;
    }
  }

  //set as win if O is placed
  if(moveMade){
    won = true;
  }

  //if not won calc next move
  if(!moveMade){
    calcMove();
  }
  
}

void calcMove(){

  int row1c = 0;
  int row2c = 0;
  int row3c = 0;

  int col1c = 0;
  int col2c = 0;
  int col3c = 0;

  int diag1c = 0;
  int diag2c = 0;

  //count all Xs for each row, column and diagonal
  
  if(row1[0] == "x"){
    col1c += 1;
    diag2c +=1;
    row1c +=1;
  }
  if(row2[0] == "x"){
    col1c += 1;
    row2c += 1;
  }
  if(row3[0] == "x"){
    col1c += 1;
    diag1c +=1;
    row3c +=1;
  }
  if(row1[1] == "x"){
    col2c += 1;
    row1c +=1;
  }
  if(row2[1] == "x"){
    col2c += 1;
    diag2c +=1;
    diag1c +=1;
    row2c += 1;
  }
  if(row3[1] == "x"){
    col2c += 1;
    row3c +=1;
  }
  if(row1[2] == "x"){
    col3c += 1;
    row1c +=1;
    diag1c +=1;
  }
  if(row2[2] == "x"){
    col3c += 1;
    row2c += 1;
  }
  if(row3[2] == "x"){
    col3c += 1;
    diag2c +=1;
    row3c +=1;
  }


  bool moveMade = false;

  //if user can win, set block on board and set move target

  if(row1c == 2 && !moveMade){
    for (int i = 0; i < 3; i++) {
      if(row1[i] == "."){
        row1[i] = "o";
        moveMade = true;
        printBoard();
        xTarget = i+1;
        yTarget = 1;
      }
    }
  }
  if(row2c == 2 && !moveMade){
    for (int i = 0; i < 3; i++) {
      if(row2[i] == "."){
        row2[i] = "o";
        moveMade = true;
        printBoard();
        xTarget = i+1;
        yTarget = 2;
      }
    }
  }
  if(row3c == 2 && !moveMade){
    for (int i = 0; i < 3; i++) {
      if(row3[i] == "."){
        row3[i] = "o";
        moveMade = true;
        printBoard();
        xTarget = i+1;
        yTarget = 3;
      }
    }
  }

  if(col1c == 2 && !moveMade){
    if(row1[0] == "."){
      row1[0] = "o";
      moveMade = true;
      printBoard();
      xTarget = 1;
      yTarget = 1;
      
    }
    if(row2[0] == "."){
      row2[0] = "o";
      moveMade = true;
      printBoard();
      xTarget = 1;
      yTarget = 2;
    }
    if(row3[0] == "."){
      row3[0] = "o";
      moveMade = true;
      printBoard();
      xTarget = 1;
      yTarget = 3;
    }
  }
  if(col2c == 2 && !moveMade){
    if(row1[1] == "."){
      row1[1] = "o";
      moveMade = true;
      printBoard();
      xTarget = 1+1;
      yTarget = 1;

    }
    if(row2[1] == "."){
      row2[1] = "o";
      moveMade = true;
      printBoard();
      xTarget = 1+1;
      yTarget = 2;
    }
    if(row3[1] == "."){
      row3[1] = "o";
      moveMade = true;
      printBoard();
      xTarget = 1+1;
      yTarget = 3;
    }
  }
  if(col3c == 2 && !moveMade){
    if(row1[2] == "."){
      row1[2] = "o";
      moveMade = true;
      printBoard();
      xTarget = 2+1;
      yTarget = 1;
    }
    if(row2[2] == "."){
      row2[2] = "o";
      moveMade = true;
      printBoard();
      xTarget = 2+1;
      yTarget = 2;
    }
    if(row3[2] == "."){
      row3[2] = "o";
      moveMade = true;
      printBoard();
      xTarget = 2+1;
      yTarget = 3;
    }
  }

  if(diag1c == 2 && !moveMade){
    if(row1[2] == "."){
      row1[2] = "o";
      moveMade = true;
      printBoard();
      xTarget = 2+1;
      yTarget = 1;
    }
    if(row2[1] == "."){
      row2[1] = "o";
      moveMade = true;
      printBoard();
      xTarget = 1+1;
      yTarget = 2;
    }
    if(row3[0] == "."){
      row3[0] = "o";
      moveMade = true;
      printBoard();
      xTarget = 0+1;
      yTarget = 3;
    }
  }

  if(diag2c == 2 && !moveMade){
    if(row1[0] == "."){
      row1[0] = "o";
      moveMade = true;
      printBoard();
      xTarget = 0+1;
      yTarget = 1;
    }
    if(row2[1] == "."){
      row2[1] = "o";
      moveMade = true;
      printBoard();
      xTarget = 1+1;
      yTarget = 2;
    }
    if(row3[2] == "."){
      row3[2] = "o";
      moveMade = true;
      printBoard();
      xTarget = 2+1;
      yTarget = 3;
    }
  }
  

  //pick random move, most likeley to pick best move

  while(!moveMade){
  int randomNum = random(1, 21);
  if(!moveMade && randomNum >= 1 && randomNum <= 2){
    if(row1[1] == "."){
      row1[1] = "o";
      moveMade = true;
      printBoard();
      xTarget = 2;
      yTarget = 1;
    }
  }
  if(!moveMade && randomNum >= 3 && randomNum <= 4){
    if(row2[0] == "."){
      row2[0] = "o";
      moveMade = true;
      printBoard();
      xTarget = 1;
      yTarget = 2;
    }
  }
  if(!moveMade && randomNum >= 5 && randomNum <= 6){
    if(row2[2] == "."){
      row2[2] = "o";
      moveMade = true;
      printBoard();
      xTarget = 3;
      yTarget = 2;
    }
  }
  if(!moveMade && randomNum >= 7 && randomNum <= 8){
    if(row3[1] == "."){
      row3[1] = "o";
      moveMade = true;
      printBoard();
      xTarget = 2;
      yTarget = 3;
    }
  }
  if(!moveMade && randomNum >= 9 && randomNum <= 16){
    if(row2[1] == "." && !moveMade){
      row2[1] = "o";
      moveMade = true;
      printBoard();
      xTarget = 2;
      yTarget = 2;
    }
  }
  if(!moveMade && randomNum == 17){
    if(row1[0] == "."){
      row1[0] = "o";
      moveMade = true;
      printBoard();
      xTarget = 1;
      yTarget = 1;
    }
  }
  if(!moveMade && randomNum == 18){
    if(row1[2] == "."){
      row1[2] = "o";
      moveMade = true;
      printBoard();
      xTarget = 3;
      yTarget = 1;
    }
  }
  if(!moveMade && randomNum == 19){
    if(row3[0] == "."){
      row3[0] = "o";
      moveMade = true;
      printBoard();
      xTarget = 1;
      yTarget = 3;
    }
  }
  if(!moveMade && randomNum == 20){
    if(row3[2] == "."){
      row3[2] = "o";
      moveMade = true;
      printBoard();
      xTarget = 3;
      yTarget = 3;
    }
  }

  }

}

void setup() {

  Serial1.begin(9600);

  long int t1 = millis();
  turnSensorSetup();
  delay(500);
  turnSensorReset();
  long int t2 = millis();
  randomSeed(t1-t2);

  

  lineSensors.initFiveSensors();
  loadCustomCharacters();

}

void loop() {

  if(!moveDone){
    inputMove();
  }else{
    //move on to board
    drive();

    //cpu calc move
    cpuMove();

    //cpu move and pay noise when done
    moveDone = false;
    zumoMove();
    buzzer.playFrequency(440, 200, 15);
    delay(200);

    //if won play tune
    if(won == true){
      winning();
      while(true){}
    }

    //set new target to starting pos and move
    xTarget = 2;
    yTarget = 4;
    zumoMove();
    turn180();
    direction = "north";
    xCurrent = 2;
    yCurrent = 3;
  }
}

void zumoMove(){
  //calc x and y diff and move that many squares

  int xDiff = abs(xTarget-xCurrent);
  faceX();
  for (int i = 0; i < xDiff; i++) {
    drive();
  }
  int yDiff = abs(yTarget-yCurrent);
  faceY();
  for (int i = 0; i < yDiff; i++) {
    drive();
  }
}

void faceX(){
  //turn direction to face x target

  if(xTarget < xCurrent){
    if(direction == "north"){
      left90();
      direction = "west";
    }
    if(direction == "south"){
      right90();
      direction = "west";
    }
    if(direction == "east"){
      turn180();
      direction = "west";
    }
  }
  if(xTarget > xCurrent){
    if(direction == "north"){
      right90();
      direction = "east";
    }
    if(direction == "south"){
      left90();
      direction = "east";
    }
    if(direction == "west"){
      turn180();
      direction = "east";
    }
  }  
  xCurrent = xTarget;
}

void faceY(){
  //turn direction to face y target
  
  if(yTarget > yCurrent){
    if(direction == "west"){
      left90();
      direction = "south";
    }
    else if(direction == "north"){
      turn180();
      direction = "south";
    }
    else if(direction == "east"){
      right90();
      direction = "south";
    }
  }
  else if(yTarget < yCurrent){
    if(direction == "east"){
      left90();
      direction = "north";
    }
    else if(direction == "south"){
      turn180();
      direction = "north";
    }
    else if(direction == "west"){
      right90();
      direction = "north";
    }
  }  
  yCurrent = yTarget;
}

void left90(){
  //turn left 90 degrees

  turnSensorReset();
  turnSensorUpdate();
  angle = getAngle();

  while(angle != 90){
    turnSensorUpdate();
    angle = getAngle();

    motors.setRightSpeed(speed);
    motors.setLeftSpeed(-speed);
  }
  motors.setRightSpeed(0);
  motors.setLeftSpeed(0);
}

void right90(){
  //turn right 90 degrees

  turnSensorReset();
  turnSensorUpdate();
  angle = getAngle();

  while(angle != -90){
    turnSensorUpdate();
    angle = getAngle();

    motors.setRightSpeed(-speed);
    motors.setLeftSpeed(speed);
  }
  motors.setRightSpeed(0);
  motors.setLeftSpeed(0);
}

void turn180(){
  //turn 180 dergees

  turnSensorReset();
  turnSensorUpdate();
  angle = getAngle();

  while(angle != -180){
    turnSensorUpdate();
    angle = getAngle();

    motors.setRightSpeed(-speed);
    motors.setLeftSpeed(speed);
  }
  motors.setRightSpeed(0);
  motors.setLeftSpeed(0);
}

void drive(){
  //move one square

  bool onFirst = true;
  bool offLine = false;
  bool onLine = false;

  motors.setRightSpeed(speed);
  motors.setLeftSpeed(speed);
  delay(200);

  while(!offLine || !onLine){
    updateSensors();
    turnSensorUpdate();
    angle = getAngle();

    motors.setRightSpeed(speed);
    motors.setLeftSpeed(speed);
    
    updateSensors();

    if(lineSensorValues[2] < 500 && !offLine && !onLine){
      offLine = true;
    }
    if(lineSensorValues[2] > 1000 && offLine){
      onLine = true;
    }
  }

  delay(20);
  motors.setRightSpeed(0);
  motors.setLeftSpeed(0);
  Serial1.print("done");
  Serial.print('\n');
  turnSensorReset();
  turnSensorUpdate();
  angle = getAngle();
}

int32_t getAngle() {
  // turnAngle is a variable defined in TurnSensor.cpp
  // This fancy math converts the number into degrees turned since the
  // last sensor reset.
  return (((int32_t)turnAngle >> 16) * 360) >> 16;
}

void updateSensors(){
  static uint16_t lastSampleTime = 0;

  if ((uint16_t)(millis() - lastSampleTime) >= 1)
  {
    lastSampleTime = millis();

    // Read the line sensors.
    lineSensors.read(lineSensorValues, useEmitters ? QTR_EMITTERS_ON : QTR_EMITTERS_OFF);

  }
}

void loadCustomCharacters()
{
  static const char levels[] PROGMEM = {
    0, 0, 0, 0, 0, 0, 0, 63, 63, 63, 63, 63, 63, 63
  };
  display.loadCustomCharacter(levels + 0, 0);  // 1 bar
  display.loadCustomCharacter(levels + 1, 1);  // 2 bars
  display.loadCustomCharacter(levels + 2, 2);  // 3 bars
  display.loadCustomCharacter(levels + 3, 3);  // 4 bars
  display.loadCustomCharacter(levels + 4, 4);  // 5 bars
  display.loadCustomCharacter(levels + 5, 5);  // 6 bars
  display.loadCustomCharacter(levels + 6, 6);  // 7 bars
}

void winning()
{
  //winning tune

  const uint16_t AVIATION[] = {196, 246, 294, 349, 392, 294, 392, 349, 294, 196, 246};
  const uint16_t AVIATION_DURATION[] = {200, 200, 200, 200, 400, 200, 200, 200, 400, 400, 400};
  const uint8_t AVIATION_VOLUME = 15;

  motors.setRightSpeed(speed);
  motors.setLeftSpeed(-speed);

  for (int i = 0; i < sizeof(AVIATION)/sizeof(uint16_t); i++) {
    buzzer.playNote(AVIATION[i]*0.15, AVIATION_DURATION[i], AVIATION_VOLUME);
    delay(AVIATION_DURATION[i] + 60); // Add a small delay between each note
  }

  delay(80);
  motors.setRightSpeed(-speed);
  motors.setLeftSpeed(speed);

  for (int i = 0; i < sizeof(AVIATION)/sizeof(uint16_t); i++) {
    buzzer.playNote(AVIATION[i]*0.15, AVIATION_DURATION[i], AVIATION_VOLUME);
    delay(AVIATION_DURATION[i] + 60); // Add a small delay between each note
  }

  delay(80);
  motors.setRightSpeed(speed);
  motors.setLeftSpeed(-speed);

  for (int i = 0; i < sizeof(AVIATION)/sizeof(uint16_t); i++) {
    buzzer.playNote(AVIATION[i]*0.15, AVIATION_DURATION[i], AVIATION_VOLUME);
    delay(AVIATION_DURATION[i] + 60); // Add a small delay between each note
  }

  motors.setRightSpeed(0);
  motors.setLeftSpeed(0);
}



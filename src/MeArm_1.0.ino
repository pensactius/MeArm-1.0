#include <Servo.h>

#define JOY_SW      6
#define JOY_Y       A1
#define JOY_X       A0
#define JOY_TL_MAX  600
#define JOY_TL_MIN  400

#define MOTOR_LEFT  3
#define MOTOR_RIGHT 2
#define MOTOR_BASE  5
#define MOTOR_CLAW  4

#define CERRADA     120
#define ABIERTA     20

#define SPEED_ARM   20    // Lower values -> faster
#define SPEED_BASE  50    // Lower values -> faster
#define BASE_MIN    10
#define BASE_MAX    170
#define START_L_ARM 90
#define START_R_ARM 90
#define START_BASE  90
#define END_L_ARM   50
#define END_R_ARM   140



Servo base;
Servo pinca;
Servo bracR;
Servo bracL;
int pos_base = 90;
int pos_rt = 90;
int pos_lt = 90;


void setup(){
  bracL.attach(MOTOR_LEFT);
  pinca.attach(MOTOR_CLAW);
  base.attach(MOTOR_BASE);
  bracR.attach(MOTOR_RIGHT);
  base.write(pos_base);
  pinca.write(CERRADA);
  bracR.write(pos_rt);
  bracL.write(pos_lt);
  pinMode(JOY_SW, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  //Base-->
  if(analogRead(JOY_Y)>JOY_TL_MAX){
    pos_base = pos_base+3;
      if(pos_base>=BASE_MAX){
      pos_base = BASE_MAX;
      }
    base.write(pos_base);
    delay(SPEED_BASE);
  }
  
  if(analogRead(JOY_Y)<JOY_TL_MIN){
    pos_base = pos_base-3;
      if(pos_base<=BASE_MIN){
        pos_base = BASE_MIN;
      }
    base.write(pos_base);
    delay(SPEED_BASE);
  }

  //<---Base
  
  //---------------------------------------------------------------------------
  //Claw
  //---------------------------------------------------------------------------
  if (digitalRead(JOY_SW)==1){
    pinca.write(CERRADA);
  }
  else{
    pinca.write(ABIERTA);
  }
  //Serial.println (digitalRead(JOY_SW));

  //Serial.println (analogRead(JOY_X));

  //---------------------------------------------------------------------------
  //Arm 
  //---------------------------------------------------------------------------
  if ( analogRead (JOY_X) > JOY_TL_MAX){
    pos_rt -= 1;
    if (pos_rt <= START_R_ARM) {
      pos_rt = START_R_ARM;
      pos_lt += 1;
      if (pos_lt >= START_L_ARM) pos_lt = START_L_ARM;
    }
  }

  if(analogRead(JOY_X)<JOY_TL_MIN){
    pos_rt += 1;
    if (pos_rt >= END_R_ARM) {
      pos_rt = END_R_ARM;
      pos_lt -= 1;
      if (pos_lt <= END_L_ARM) pos_lt = END_L_ARM;
    }

  }
  //Serial.println (pos_rt);
  bracR.write (pos_rt);
  bracL.write (pos_lt);
  delay(SPEED_ARM);
//<--Braç
}
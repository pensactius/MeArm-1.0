#include <Servo.h>
#define JOY_SW  6
Servo base;
Servo pinca;
Servo bracR;
Servo bracL;
int M = 90;
int BR = 90;
int BL = 90;
#define CERRADA 120
#define ABIERTA 20

void setup(){
  bracL.attach(3);
  pinca.attach(4);
  base.attach(5);
  bracR.attach(2);
  base.write(M);
  pinca.write(CERRADA);
  bracR.write(BR);
  bracL.write(BL);
  pinMode(JOY_SW, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  //Base-->
  if(analogRead(A1)>600){
    M = M+3;
      if(M>=170){
      M = 170;
      }
    base.write(M);
    delay(50);
  }
  
  if(analogRead(A1)<400){
    M = M-3;
      if(M<=10){
        M = 10;
      }
    base.write(M);
    delay(50);
  }

  //<---Base
  
  //Claw---->
  if (digitalRead(JOY_SW)==1){
    pinca.write(CERRADA);
  }
  else{
    pinca.write(ABIERTA);
  }
  Serial.println (digitalRead(JOY_SW));

  //<---Claw


  Serial.println (analogRead(A0));
  //Arm
  if ( analogRead (A0) > 600){
    BR -= 1;
    if (BR <= 90) {
      BR = 90;
      BL += 1;
      if (BL >= 90) BL = 90;
    }
  }

  if(analogRead(A0)<400){
    BR += 1;
    if (BR >= 140) {
      BR = 140;
      BL -= 1;
      if (BL <= 50) BL = 50;
    }

  }
  Serial.println (BR);
  bracR.write (BR);
  bracL.write (BL);

//<--Braç
}

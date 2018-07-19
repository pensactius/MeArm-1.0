#include <Servo.h>
Servo base;
Servo pinca;
Servo bracR;
Servo bracL;
int M = 90;
int BR = 30;
int BL = 90;
void setup(){
  bracL.attach(11);
  pinca.attach(8);
  base.attach(10);
  bracR.attach(7);
  base.write(M);
  pinca.write(70);
  bracR.write(BR);
  bracL.write(BL);
  pinMode(9, INPUT_PULLUP);
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
  if (digitalRead(9)==1){
    pinca.write(170);
  }
  else{
    pinca.write(90);
  }
  //<---Claw

  
  //Arm
  if(analogRead(A0)>600){
    if (BL<90){
      BL=BL+3;
      bracL.write(BL);
    }else{
      BR = BR-3;
        if(BR<=30){
          BR = 30;
        }
      bracR.write(BR);
    }

    delay(50);
  }  
  if(analogRead(A0)<400){
    BR = BR+3;
      if(BR>=75){
      BR= 75;
      }   
    bracR.write(BR);

     if(BR>=60){
      BL = BL-3;
      if (BL <= 15){ 
        BL = 15;
      }
      bracL.write(BL);
     }
    delay(100);
  }


//<--Braç
}

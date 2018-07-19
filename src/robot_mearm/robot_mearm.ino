#include <Servo.h>

// Definicion de pines
#define PIN_BASE        10
#define PIN_PINCA        8
#define PIN_SERVO_RIGHT  7
#define PIN_SERVO_LEFT  11
#define PIN_HORIZ       A1
#define PIN_VERT        A0
#define PIN_BUTTON       9

// Definición de los extremos de cada motor
#define BASE_MIN        10
#define BASE_MAX       170
#define RIGHT_MIN
#define RIGHT_MAX
#define LEFT_MIN

// Definición de las posiciones iniciales de los motores
#define BASE_INICI      90
#define RIGHT_INICI     30
#define LEFT_INICI      90
#define PINCA_TANCADA   90
#define PINCA_OBERTA   170

// Definición de variables para los motores
Servo base;
Servo pinca;
Servo servoRight;
Servo servoLeft;

// Posiciona todos los motores a sus posiciones iniciales
int angleBase = BASE_INICI;
int angleRight = RIGHT_INICI;
int angleLeft = LEFT_INICI;

/* -----------------------------------------------------------
       ____  ____  ____  _  _  ____ 
      / ___)(  __)(_  _)/ )( \(  _ \
      \___ \ ) _)   )(  ) \/ ( ) __/
      (____/(____) (__) \____/(__) 

   -----------------------------------------------------------
*/      
void setup(){

  // Configuración de pins de cada motor
  servoLeft.attach(PIN_SERVO_LEFT);
  pinca.attach(PIN_PINCA);
  base.attach(PIN_BASE);
  servoRight.attach(PIN_SERVO_RIGHT);

  // Configuración del pin del boton del joystick
  pinMode(PIN_BUTTON, INPUT_PULLUP);

  // Posiciona los motores a la posición inicial
  base.write(angleBase);
  pinca.write(PINCA_TANCADA);
  servoRight.write(angleRight);
  servoLeft.write(angleLeft);

}

/* -----------------------------------------------------------
           __     __    __  ____ 
          (  )   /  \  /  \(  _ \
          / (_/\(  O )(  O )) __/
          \____/ \__/  \__/(__)

 -----------------------------------------------------------
*/
void loop() {
  
  /* -------------------------------------------------------
                  BASE
    ------------------------------------------------------- 
   */

  // ¿Movemos el joystick a la izquierda?
  if (analogRead (PIN_HORIZ) > 600) 
  {
    // Aumentamos el ángulo de la base
    angleBase = angleBase + 3;
    
    // Mantenemos el servo en posiciones seguras
    if(angleBase >= BASE_MAX){
      angleBase = BASE_MAX;
    }

    // Actualizamos la posición del motor con el nuevo ángulo
    base.write(angleBase);
    delay(50);
  }
  
  // ¿Movemos el joystick a la derecha?
  if (analogRead (PIN_HORIZ) < 400)
  {
    // Decrementamos el ángulo de la base
    angleBase = angleBase - 3;

    // Mantenemos el servo en posiciones seguras
    if (angleBase <= BASE_MIN){
      angleBase = BASE_MIN;
    }
    base.write(angleBase);
    delay(50);
  }

  /* -------------------------------------------------------
                  PINÇA
    ------------------------------------------------------- 
   */
  
  if (digitalRead (PIN_BUTTON) == 1)
  {
    pinca.write(170);
  }
  else{
    pinca.write(90);
  }
  //<---Claw

  
  //Arm
  if(analogRead(PIN_VERT)>600){
    if (angleLeft<90){
      angleLeft=angleLeft+3;
      servoLeft.write(angleLeft);
    }else{
      angleRight = angleRight-3;
        if(angleRight<=30){
          angleRight = 30;
        }
      servoRight.write(angleRight);
    }

    delay(50);
  }  
  if(analogRead(PIN_VERT)<400){
    angleRight = angleRight+3;
      if(angleRight>=75){
      angleRight= 75;
      }   
    servoRight.write(angleRight);

     if(angleRight>=60){
      angleLeft = angleLeft-3;
      if (angleLeft <= 15){ 
        angleLeft = 15;
      }
      servoLeft.write(angleLeft);
     }
    delay(100);
  }


//<--Braç
}

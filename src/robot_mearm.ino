#include <Servo.h>

// Definicion de pines
#define PIN_BASE        10
#define PIN_PINCA        8
#define PIN_SERVO_RIGHT  7
#define PIN_SERVO_LEFT  11
#define PIN_HORIZ       A1  // Ry
#define PIN_VERT        A0  // Rx
#define PIN_BUTTON       9  // SW

// Definición de los extremos de cada motor
#define BASE_MIN        10
#define BASE_MAX       170
#define RIGHT_DOWN      30
#define RIGHT_UP        75
#define LEFT_DOWN       90
#define LEFT_UP         15

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
  // Si pulsamos el botón ...
  if (digitalRead (PIN_BUTTON) == 0)
  {
    // Abrimos pinza
    pinca.write(PINCA_OBERTA);
  }
  else // Si el botón no está pulsado...
  {    // Cerramos pinza
    pinca.write(PINCA_TANCADA);
  }

  /* -------------------------------------------------------
                  BRAÇ
    ------------------------------------------------------- 
   */

  // Si movemos el joystick hacia ARRIBA el brazo ha de moverse hacia abajo
  // La idea es mover primero el brazo izquierdo hasta llegar a un cierto ángulo,
  // a partir del cual, éste deja de moverse y comienza a bajar el brazo derecho.
  if (analogRead (PIN_VERT) > 600)
  {
    // Si el brazo no ha llegado a su extremos inferior...
    if (angleLeft < LEFT_DOWN)
    {
      // ... aumentamos el ángulo del motor izquierdo para que baje.
      angleLeft = angleLeft + 3;
      servoLeft.write(angleLeft);
    }
    else 
    { 
      // En este punto el brazo izquierdo ya ha llegado a su límite inferior,
      // comenzamos a bajar el brazo derecho
      angleRight = angleRight-3;

      // Si el brazo llega al límite inferior impedimos que pueda bajar más.
      if (angleRight <= RIGHT_DOWN)
      {
        angleRight = RIGHT_DOWN;
      }
      servoRight.write(angleRight);
    }

    delay(50);
  }  

  // Si movemos el joystick hacia ABAJO el brazo ha de subir, realizando el
  // movimiento a la inversa, es decir, primero sube el brazo derecho y después
  // sube el brazo izquierdo.
  if (analogRead (PIN_VERT) < 400)
  {
    // Comenzamos a subir el brazo derecho
    angleRight = angleRight+3;
    
    // Cuando el brazo derecho llega al límite superior, 
    // impedimos que pueda subir más.
    if(angleRight>=RIGHT_UP)
    {
      angleRight= RIGHT_UP;
    }
    servoRight.write(angleRight);

    // Si el motor derecho ha llegado a su límite superior...
    if(angleRight >= RIGHT_UP)
    {
      // ... disminuímos el ángulo del motor izquierdo para que suba
      // hasta llegar a su límite superior
      angleLeft = angleLeft - 3;
      if (angleLeft <= LEFT_UP)
      { 
        angleLeft = LEFT_UP;
      }      
      servoLeft.write (angleLeft);
    }
    delay(100);
  }


//<--Braç
}
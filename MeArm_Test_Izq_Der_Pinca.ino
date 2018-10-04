#include <Servo.h>

#define CERRADA 120
#define ABIERTA 20
Servo right, left, pinca;

void setup() {
  // put your setup code here, to run once:
  right.attach(2); left.attach(3); pinca.attach(4);
  right.write (90); left.write (90); pinca.write (CERRADA);
}

void loop() {
  for (int angulo = 140; angulo >= 70; angulo--) {
    right.write (angulo);
    delay (30);
  }
  for (int angulo = 90; angulo >= 50; angulo--) {
    left.write (angulo);
    delay (30);
  }

  pinca.write (ABIERTA);
  delay (2000);
  pinca.write (CERRADA);
  
  delay (1000);
  
  for (int angulo = 70; angulo <= 140; angulo++) {
    right.write (angulo);
    delay (30);
  }

  for (int angulo = 50; angulo <= 90; angulo++) {
    left.write (angulo);
    delay (30);
  }

  pinca.write (ABIERTA);
  delay (2000);
  pinca.write (CERRADA);
  delay (1000);
}

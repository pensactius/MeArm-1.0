#include <Servo.h>
const uint8_t BASE_PIN    = 5;
const uint8_t ANGLE_START = 90;

Servo base;

void setup() {
  base.attach (BASE_PIN);
  base.write (ANGLE_START);
}

void loop() {
//  for (uint8_t ang = ANGLE_START-50; ang != ANGLE_START+50; ++ang) {
//    base.write (ang);
//    delay (10);
//  }
//  for (uint8_t ang = ANGLE_START+50; ang != ANGLE_START-50; --ang) {
//    base.write (ang);
//    delay (10);
//  }
}

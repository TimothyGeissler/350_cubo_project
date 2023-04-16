#include <Servo.h>

//Pin 9: white (CTRL)
//GND: Black
//5V: Red

//PSU @ max 1.03A (max0 & 11V

Servo ESC;     // create servo object to control the ESC
byte pin = 9;

int potValue;  // value from the analog pin

void setup() {
  ESC.attach(pin);
  initESC();
}

void initESC() {
  delay(5000);
  ESC.writeMicroseconds(2000);
  delay(2500);
  ESC.writeMicroseconds(1000);
  delay(2500);
}

void loop() {
  potValue = analogRead(A0);   // reads the value of the potentiometer (value between 0 and 1023)
  potValue = map(potValue, 0, 1023, 1000, 2000);   // scale it to use it with the servo library (value between 0 and 180)
  // Attach the ESC on pin 9
  ESC.writeMicroseconds(potValue);
}

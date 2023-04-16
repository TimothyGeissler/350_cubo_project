#include <Servo.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

//Pin 9: white (CTRL)
//GND: Black
//5V: Red

//PSU @ max 1.03A (max0 & 11V

Servo ESC;     // create servo object to control the ESC
byte pin = 9;

int potValue;  // value from the analog pin

void setup() {
  ESC.attach(pin);

  Serial.begin(9600);

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);

  // initESC();
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

  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  /* Print out the values */
  Serial.print("Acceleration X: ");
  Serial.print(a.acceleration.x);
  Serial.print(", Y: ");
  Serial.print(a.acceleration.y);
  Serial.print(", Z: ");
  Serial.print(a.acceleration.z);
  Serial.println(" m/s^2");

  if (a.acceleration.x < -5) {
    ESC.writeMicroseconds(potValue);
  } else {
    if (-a.acceleration.y < a.acceleration.z) {
      ESC.writeMicroseconds(1000);
      Serial.println("Spin FWD");
    } else {
      ESC.writeMicroseconds(2000);
      Serial.println("Spin REV");
    }
  }

}

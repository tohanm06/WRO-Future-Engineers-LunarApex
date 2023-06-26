
#include <SPI.h>
#include <PWMServo.h>
#include <Servo.h>
#include "Wire.h"
#include <MPU6050_light.h>



// defines variables
// This is the main Pixy object

PWMServo head;
int i = 0;
const int trigleft = 11;
const int echoleft = 10;
const int trigright = 6;
const int echoright = 7;
// defines variables

double angle;

unsigned int interval = 2000;  //one minute in ms

bool clockwise = true;
double duration, distance;

float turnAmt = 90;


MPU6050 mpu(Wire);

int distance1 = 0;
void deterorei(int x) {
  while ((distanceleft() <= x) && (distanceright() <= x)) {
    forward();
  }
  if (distanceleft() > x) {
    clockwise = false;
  } else if (distanceright() > x) {
    clockwise = true;
  }
}
double anglec() {
  double amgle = mpu.getAngleZ();
  return amgle;
}
double distanceleft() {
  digitalWrite(trigleft, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigleft, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigleft, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoleft, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  return distance;
}
double distanceright() {
  digitalWrite(trigright, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigright, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigright, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoright, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  return distance;
}
void forward() {
  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);
}
void stop() {
  digitalWrite(7, HIGH);
  digitalWrite(8, LOW);
}
void setup() {
  Wire.begin();
  mpu.begin();
  Serial.begin(115200);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(trigleft, OUTPUT);  // Sets the trigPin as an Output
  pinMode(echoleft, INPUT);
  pinMode(trigright, OUTPUT);  // Sets the trigPin as an Output
  pinMode(echoright, INPUT);
  mpu.calcOffsets();
  delay(100);
  head.attach(9);
  head.write(60);
  deterorei(100);
}

void loop() {
  forward();
  double angleol = anglec();
  if (clockwise == true) {
    while (true) {

      if (distanceright() >= 100) {
        head.write(90);
        while (anglec() >= (angleol - 90)) {
          mpu.update();
          forward();
          delay(1);
          Serial.println(mpu.getAngleZ());
          Serial.println(angleol);
          
        }
        angleol -= 90;
      }

      head.write(60);
      forward();
    }

  } else if (clockwise == false) {
    while (true) {

      if (distanceleft() >= 100) {
        head.write(20);
        while (anglec() <= (angleol + 90)) {
          mpu.update();
          forward();
          delay(1);
          Serial.println(mpu.getAngleZ());
          Serial.println(angleol);
          
        }
        angleol += 90;
      }

      head.write(60);
      forward();
    }
  }
}

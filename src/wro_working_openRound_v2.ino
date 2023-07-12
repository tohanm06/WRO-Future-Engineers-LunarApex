
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
const int echoright = 4;
const int trigfront = 3;
const int echofront = 2;
int cor =0 ;
// defines variables

double angle;

unsigned int interval = 2000;  //one minute in ms

bool clockwise = true;
double duration,dl,dr;

float turnAmt = 90;


MPU6050 mpu(Wire);

int distance1 = 0;
bool sidedis(){
   dl = distance(trigleft,echoleft);
   dr = distance(trigright,echoright);
  double wallen = dl+dr+15;
  //Serial.println(wallen);
  if (dl-dr <= 5){
    return true;
  }
  else{
    return false;
  }
}
void drivest(double angleol){
  while (sidedis() && (abs(anglec()-angleol)<=10)) {
          head.write(60);
          forward();
        }
        head.write(60+(dr-dl)*3);
        
      }

void deterorei(int x) {
  while ((distance(trigleft,echoleft) <= x) && (distance(trigright,echoright) <= x)) {
    forward();
  }
  if (distance(trigleft,echoleft) > x) {
    clockwise = false;
  } else if (distance(trigright,echoright) > x) {
    clockwise = true;
  }
}
double anglec() {
  double amgle = mpu.getAngleZ();
  return amgle;
}
double distance(int trig,int echo) {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echo, HIGH);
  // Calculating the distance
  int distancei = duration * 0.034 / 2;
  Serial.println(distancei);
  return distancei;
}


void forward() {
  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);
}
void stop() {
  digitalWrite(7, LOW);
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
  
  double angleol = 0;
  if (clockwise == true) {
    while (true) {
      sidedis();
      if (distance(trigright,echoright) >= 100) {
        forward();
       // head.write(75);
        while (anglec() >= (angleol - 90)) {
          head.write(60-(((angleol - 90) - anglec())/2.25));
          mpu.update();
          forward();
          //delayMicroseconds(10);
          //Serial.println(mpu.getAngleZ());
          //Serial.println(angleol);
          
        }
        head.write(60);
        drivest(angleol);
        angleol -= 90;
        cor+=1;
      }

      head.write(60);
      forward();
    }

  } else if (clockwise == false) {
    while (true) {
      sidedis();
      if (distance(trigleft,echoleft) >= 100) {
        forward();
       // head.write(45);
        while (anglec() <= (angleol + 90)) {
          head.write(60 - (((angleol + 90) - anglec())/2.25));
          mpu.update();
          forward();
          //delayMicroseconds(10);
          //Serial.println(mpu.getAngleZ());
          //Serial.println(angleol);
          
        }
        head.write(60);
       drivest(angleol);
        angleol += 90;
        cor+=1;
      }

      head.write(60);
      forward();
    }
  }
}

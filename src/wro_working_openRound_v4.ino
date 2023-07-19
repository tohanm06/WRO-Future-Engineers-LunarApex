
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
const int trigright = 13;
const int echoright = 12;
// defines variables
int speed = 200;
double angle;
int cor = 0;
unsigned int interval = 2000;  //one minute in ms

bool clockwise = false;
double duration;

float turnAmt = 90;


MPU6050 mpu(Wire);

int distance1 = 0;
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
  //Serial.println(distancei);
  if ((distancei>500)||(distancei == 72)||(distancei == 71)||(distancei == 73)){
    return 0;
  }
  else{
  return distancei;
  }
}


void forward() {
  analogWrite(5,speed);
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
  pinMode(5,OUTPUT);
  mpu.calcOffsets();
  delay(100);
  head.attach(9);
  head.write(60);
  deterorei(100);
}

void loop() {
  int turan = 80;
  forward();
  double angleol = anglec();
  if (clockwise == true) {
    while (true) {
      if (cor < 12){
      if (distance(trigright,echoright) >= 100) {
       // head.write(75);
        while (anglec() >= (angleol - turan)) {
          head.write(60-(((angleol - turan) - anglec())/2.5));
          mpu.update();
          forward();
          delayMicroseconds(10);
          

          //Serial.println(mpu.getAngleZ());
          //Serial.println(angleol);
          
        }
        angleol -= 90;
        cor+=1;
        
      }
      double error = 42.5 -  distance(trigright,echoright);
      double angc = map(error, -42.5,42.5,45,75);
      head.write(angc);
      forward();
    }else{
      digitalWrite(8,LOW);
      digitalWrite(7,HIGH);
      delay(1000);
      digitalWrite(8,HIGH);
      digitalWrite(7,HIGH);
      break;
    }
    
    }

  } else if (clockwise == false) {
    while (true) {
      if (cor < 12){
      if (distance(trigleft,echoleft) >= 100) {
       // head.write(45);
        while (anglec() <= (angleol + turan)) {
          head.write(60 - (((angleol + turan) - anglec())/2.5));
          mpu.update();
          forward();
          delayMicroseconds(10);
          //Serial.println(mpu.getAngleZ());
          //Serial.println(angleol);
          
        }
        angleol += 90;
        cor+=1;
      }
      double error = 42.5 - distance(trigleft,echoleft);
      double angc = map(error, -42.5,42.5,45,75);
      head.write(angc);
      forward();
      
      }else{
      digitalWrite(8,LOW);
      digitalWrite(7,HIGH);
      delay(1000);
      digitalWrite(8,HIGH);
      digitalWrite(7,HIGH);
      break;
    }
      
    }
  }
      digitalWrite(8,HIGH);
      digitalWrite(7,HIGH);
      //break;
}

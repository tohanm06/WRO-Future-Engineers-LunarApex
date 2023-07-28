#include <Pixy2.h>
#define detdis 0.1
#include <SPI.h>
#include <PWMServo.h>
#include <Servo.h>
#include "Wire.h"
#include <MPU6050_light.h>



// defines variables
// This is the main Pixy object

PWMServo head;
int i = 0;
const int trigleft = 10;
const int echoleft = 6;
const int trigright = 3;
const int echoright = 2;
const int trigfront = 3;
const int echofront = 2;
const float mid = 58.5;
int curan, inang;
// defines variables
int speed = 175;
double angle;
int cor = 0;
unsigned int interval = 2000;  //one minute in ms
int time, currentMillis;
bool clockwise = false;
double duration;
int ska;
MPU6050 mpu(Wire);
int findr=0,findl=0;
int distance1 = 0;
float turnAmt = 90;
int fin = 0;
void write(int ang){
  int inpangl = constrain(ang,20,97);
  head.write(inpangl);
}
void rev(){
  digitalWrite(7,HIGH);
  digitalWrite(8,LOW);

}
double anglec() {
  mpu.update();
  double amgle = mpu.getAngleZ();
  return amgle;
}
double distance(int trig, int echo) {
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
  if ((distancei > 500) || (distancei == 72) || (distancei == 71) || (distancei == 73)) {
    return 0;
  } else {
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
  Serial.begin(115200);
  Wire.begin();
  mpu.begin();
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(trigleft, OUTPUT);  // Sets the trigPin as an Output
  pinMode(echoleft, INPUT);
  pinMode(trigright, OUTPUT);  // Sets the trigPin as an Output
  pinMode(echoright, INPUT);
  pinMode(5,OUTPUT);
  mpu.calcOffsets();
  delay(100);
  time = millis();
  head.attach(9);
  write(mid);
  inang = anglec();
  delay(5000);
}
void loop() {
  if (cor>11){
    if (fin!=1){
      digitalWrite(7,HIGH);
      digitalWrite(8,LOW);
      delay(1000);
      stop();
      digitalWrite(8,HIGH);
      digitalWrite(7,HIGH);
      fin = 1;
    }
}
else{
  double angleol = anglec();
  speed = 175;
  forward();
  findl = distance(10,6);
  findr = distance(3,2);
  if (findl>=80){
    while(anglec()<=(angleol+70)){
        mpu.update();
        write(30);
        forward();   
      }
      head.write(58.5);
      delay(500);
      cor++;
  }
  write(58.5);
  forward();
  }
}
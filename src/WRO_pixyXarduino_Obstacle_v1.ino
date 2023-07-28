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
MPU6050 mpu(Wire);

int distance1 = 0;
float turnAmt = 90;





// defines variables
// This is the main Pixy object
Pixy2 pixy;

// double heical, widcal, x, tot = 0, avg, posx, posy;
// double disblock(int blok) {
//   pixy.ccc.getBlocks();

//   // If there are detect blocks, print them!
//   if (pixy.ccc.numBlocks)

//   {
//     //Serial.print("Detected ");
//     //Serial.println(pixy.ccc.numBlocks);

//     for (c = 0; c < 2000; c++) {
//       heical = (double)32 / (pixy.ccc.blocks[blok].m_height);
//       widcal = (double)22 / (pixy.ccc.blocks[blok].m_width - 1);
//       posx = 158 - pixy.ccc.blocks[blok].m_x;
//       posy = 158 - pixy.ccc.blocks[blok].m_y;
//       x = (heical + widcal) / 2 * 20;
//       tot += x;
//     }
//     avg = tot / 2000;
//     tot = 0;
//     return avg;
//   }
// }
double sel(char ret) {
  double reat;

  // Serial.print("  block ");
  //Serial.print(i);
  //Serial.print(": ");
  //pixy.ccc.blocks[i].print();



  switch (ret) {
    case 'l':
      {

        reat = pixy.ccc.blocks[0].m_height;

        break;
      }
    case 'w':
      {

        reat = pixy.ccc.blocks[0].m_width;

        break;
      }

    case 's':
      {

        reat = pixy.ccc.blocks[0].m_signature;
        break;
      }
    case 'x':
      {

        reat = pixy.ccc.blocks[0].m_x;
        break;
      }
    case 'y':
      {

        reat = pixy.ccc.blocks[0].m_y;
        break;
      }
    case 'i':
      {

        reat = pixy.ccc.blocks[0].m_index;
        break;
      }
    case 'a':
      {

        reat = pixy.ccc.blocks[0].m_age;
        break;
      }
  }

  return reat;
}

bool breach(int angleol){
  mpu.update();
  if (((mpu.getGyroX()<=detdis)&&(mpu.getGyroX()>=(-detdis)))||((mpu.getGyroY()<=detdis)&&(mpu.getGyroY()>=(-detdis)))){
        rev();
        delay(1000);
        write((angleol-anglec())/2);
        return true;
      }
  else{
    return false;
  }
}
void write(int ang){
  int inpangl = constrain(ang,20,97);
  head.write(inpangl);
}
bool fronche(){
  int frontd = distance(3,2);
  if (frontd <= 10){
    return true;
  }
  else{
    return false;
  }
}
void rev(){
  digitalWrite(7,HIGH);
  digitalWrite(8,LOW);

}
void deterorei(int x) {
  while ((distance(trigleft, echoleft) <= x) && (distance(trigright, echoright) <= x)) {
    forward();
  }
  if (distance(trigleft, echoleft) > x) {
    clockwise = false;
  } else if (distance(trigright, echoright) > x) {
    clockwise = true;
  }
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

void decide() {
  //speed = 200;
  forward();
  pixy.ccc.getBlocks();
  //grab blocks!
  if (pixy.ccc.numBlocks){
  Serial.println((sel('w')*sel('l')));
  if (((sel('w')*sel('l'))>=400)){
  if (sel('s') == 1) {
    Serial.println(sel('s'));
while (anglec() >= (-30)) {
          write(58.5-(-60 - anglec())/1.5);
          speed = 175;
          forward();
      
 }
while (anglec() <= (0)) {
          write(58.5-(0 - anglec())/1.25);
          speed = 175;
          forward();
      
 }
 delay(300);
 stop();


  } else if (sel('s') == 2) {
    Serial.println(sel('s'));
    // for red block
    while (anglec() <= (30)) {
          write(58.5-(60 - anglec())/1.5);
          speed = speed = map(anglec(),0,30,150,180);;
          forward();
      
 }
while (anglec() >= (0)) {
          write(58.5-(0 - anglec())/1.25);
          speed = map(anglec(),0,30,150,180);
          forward();
      
 }
 delay(300);
 stop();
  }
}
}
  }
void forward() {
  analogWrite(5,200);
  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);
}
void stop() {
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
}
void setup() {
  Serial.begin(115200);
  pixy.init();
  pixy.setLamp(1, 1);
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
  deterorei(85);
  inang = anglec();
  
}
void loop() {
pixy.setLamp(1, 1);
  int turan = 80;
  speed = 175;
  forward();
  double angleol = 0;
  if (clockwise == true) {
    while (true) {
      if (cor < 12){
      if (distance(trigright,echoright) >= 80){
        //write(90);
        while (anglec() >= (angleol - turan)) {
          write(mid-(((angleol - turan) - anglec())/2.3));
          
          forward();
          //breach(angleol);
      //     if (millis() -  time >= 10000){
      //   breach(angleol);
      //   time = millis();
      // }
          

          //Serial.println(mpu.getAngleZ());
          //Serial.println(angleol);
          
        }
        angleol -= 90;
        cor+=1;
        
      }
      curan = anglec();
      double error = 42.5 -  distance(trigright,echoright);
      double angc = constrain(map(error, -52.5,52.5,mid-10,mid+10),mid-15,mid+15);
      write(angc);
      forward();
      decide();
      speed = 175;
      // if (millis() -  time >= 10000){
      //   breach(angleol);
      //   time = millis();
      // }
     }
    else{
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
      if (distance(trigleft,echoleft) >= 80) {
        //write(30);
        while (anglec() <= (angleol + turan)) {
          write(mid - (((angleol + turan) - anglec())/2.3));
          
          forward();
          //decide();
          //breach(angleol);
      //     if (millis() -  time >= 10000){
      //   breach(angleol);
      //   time = millis();
      // }
          //Serial.println(mpu.getAngleZ());
          //Serial.println(angleol);
          
        }
        angleol += 90;
        cor+=1;
      }
      double error = 42.5 - distance(trigleft,echoleft);
      double angc = constrain(map(error, -52.5,52.5,mid-10,mid+10),mid-15,mid+15);
      write(angc);
      forward();
      
      // if (millis() -  time >= 10000){
      //   breach(angleol);
      //   time = millis();
      // }
    
      }
      else{
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

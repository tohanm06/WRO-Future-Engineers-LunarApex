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
// const int trigfront = 3;
// const int echofront = 2;
const float mid = 58.5;
int curan, inang;
// defines variables
int speed;
double angle;
int cor = 0;
unsigned int interval = 2000;  //one minute in ms
int time, currentMillis;
bool clockwise = false;
double duration;
int ska;
MPU6050 mpu(Wire);
Pixy2 pixy;
int findr=0;
int findl=0;
int distance1 = 0;
float turnAmt = 90;
int fin = 0;
double angleol;
int r1 = 0;
int si1,si2=NULL,ex1,ex2=NULL;
void write(int ang){
  int inpangl = constrain(ang,20,97);
  head.write(inpangl);
}
void rev(){
  digitalWrite(7,HIGH);
  digitalWrite(8,LOW);

}
void conch(int numBlocks,int sig1, int sig2, int x1,int x2){
  if (numBlocks==1){
    switch(sig1){
      case 1:{//green

    }
    case 2:{//red

    }
  }
  }
  else{

  }
}
double anglec() {
  mpu.update();
  double amgle = mpu.getAngleZ();
  return amgle;
}
// void rot(int conf){
//   switch(conf){
//     case 1:{
//       speed = 220;
//       forward();
//       delay(500);
//       while (anglec() >= (-40)) {
//           write(58.5+28.5);
//           forward(); 
//       }
//       write(58.5);
//       forward();
//       delay(250);
//       while (anglec() <= (-8)) {
//           write(30);
//           forward(); 
//       }
//       write(58.5);
//       forward();
//       delay(500);
//       while (anglec() <= (40)) {
//                 write(58.5-28.5);
//                 forward(); 
//       }
//       write(58.5);
//       forward();
//       delay(250);
//       while (anglec() >= (0)) {
//                 write(87);
//                 forward(); 
//       }
//       write(58.5);
//       forward();
//       stop();
//     }//red left 
//     case 2:{
//       speed = 220;
//       forward();
//       delay(500);
//       while (anglec() >= (-40)) {
//                 write(58.5+28.5);
//                 forward(); 
//       }
//       write(58.5);
//       forward();
//       delay(250);
//       while (anglec() <= (-8)) {
//                 write(30);
//                 forward(); 
//       }
//       write(58.5);
//       forward();
//       delay(500);
//       while (anglec() <= (40)) {
//                 write(58.5-28.5);
//                 forward(); 
//       }
//       write(58.5);
//       forward();
//       delay(250);
//       while (anglec() >= (0)) {
//                 write(87);
//                 forward(); 
//       }
//       write(58.5);
//       forward();
//       stop();
//     }// red right
//     case 3:{
//           speed = 220;
//           forward();
//           delay(500);
//           while (anglec() >= (-40)) {
//                     write(58.5+28.5);
//                     forward(); 
//           }
//           write(58.5);
//           forward();
//           delay(250);
//           while (anglec() <= (-8)) {
//                     write(30);
//                     forward(); 
//           }
//           write(58.5);
//           forward();
//           delay(500);
//           while (anglec() <= (40)) {
//                     write(58.5-28.5);
//                     forward(); 
//           }
//           write(58.5);
//           forward();
//           delay(250);
//           while (anglec() >= (0)) {
//                     write(87);
//                     forward(); 
//           }
//           write(58.5);
//           forward();
//           stop();
//     }//green left
//     case 4:{
//         speed = 220;
//         forward();
//         delay(500);
//         while (anglec() >= (-40)) {
//                   write(58.5+28.5);
//                   forward(); 
//         }
//         write(58.5);
//         forward();
//         delay(250);
//         while (anglec() <= (-8)) {
//                   write(30);
//                   forward(); 
//         }
//         write(58.5);
//         forward();
//         delay(500);
//         while (anglec() <= (40)) {
//                   write(58.5-28.5);
//                   forward(); 
//         }
//         write(58.5);
//         forward();
//         delay(250);
//         while (anglec() >= (0)) {
//                   write(87);
//                   forward(); 
//         }
//         write(58.5);
//         forward();
//         stop();
//     }//green right
//   }
// }
void turn(int clc){
  if (clockwise==false){
    if(findl>=100){
      delay(100);
    while(anglec()<=(angleol+77.5)){
        speed = 200;
        mpu.update();
        write(30);
        forward();   
        decide();
      }
      cor++;
      angleol+=82.5;
      write(58.5);
      delay(600);
      //findl = distance(10,6);
      //findr = distance(3,2);
    }
    speed = 150;
    write(58.5);
  forward();
  decide();
  findl = distance(10,6);
  //findr = distance(3,2);
  }else if (clockwise==true){
    if(findr>=70){
      //delay(0);
    while(anglec()>=(angleol-90)){
        speed = 200;
        mpu.update();
        write(58.5+28.5);
        forward();   
        decide();
      }
      cor++;
      angleol-=82.5;
      write(58.5);
      delay(1000); 
    //  findl = distance(10,6);
      //findr = distance(3,2);
    }
    speed = 150;
    write(58.5);
  forward();
  decide();
  //findl = distance(10,6);
  findr = distance(3,2);
  }
  
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
  return distancei;
}
void decide() {
  //speed = 200;
  forward();
  pixy.ccc.getBlocks();
  if (pixy.ccc.numBlocks){
  Serial.println(sel('w')*sel('l'));
  if (sel('w')*sel('l')>=1000){
  if (sel('s')==2){
    speed = 200;
    forward();
    delay(50);
    while (anglec() >= (angleol-45)) {
              write(58.5+38.5);
              forward(); 
    }

    while (anglec() <= (angleol+40)) {
              write(58.5-38.5);
              forward(); 
    }
    while (anglec() >= (angleol+10)) {
              write(58.5+38.5);
              forward(); 
    }
    write(58.5);
    delay(10);
    stop();
    // digitalWrite(7, HIGH);
    // digitalWrite(8, LOW);
  }else if(sel('s')==1){
    speed = 200;
    forward();
    delay(50);
    while (anglec() <= (angleol + 40)) {
              write(58.5-28.5);
              forward(); 
    }

    while (anglec() >= (angleol -36)) {
              write(87);
              forward(); 
    }
    while (anglec() <= (angleol-8)) {
              write(58.5-28.5);
              forward(); 
    }
    write(58.5);
    delay(10);
    stop();
    // digitalWrite(7, HIGH);
    // digitalWrite(8, LOW);

  }
  }
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
double sel(char ret) {
  double reat;
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
void setup() { 
  Serial.begin(115200);
  Wire.begin();
  mpu.begin();
  pixy.init();
  //pixy.setLamp(1, 1);
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
  angleol = anglec();
  speed = 175;
}
void loop() {
  
  if (cor>11){
    if (fin!=1){
      digitalWrite(7,HIGH);
      digitalWrite(8,LOW);
      delay(1500);
      stop();
      digitalWrite(8,HIGH);
      digitalWrite(7,HIGH);
      fin = 1;
    }
}
else{
  if(r1 != 1){
    while((findl + findr) <= 120){
    
    forward();
    findr = distance(3,2);
    findl = distance(10,6);
    
    }
    if (findl>findr){
      clockwise = false;
    }
    else if(findr>findl){
      clockwise = true;
    }
    r1=1;
  }
  
  turn(clockwise);
  
  }
}
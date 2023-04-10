#include <Pixy2.h>
#include <SPI.h>
#include <PWMServo.h>
int i;
int c;


// defines variables
// This is the main Pixy object
Pixy2 pixy;
PWMServo head;
double heical, widcal, x, tot = 0, avg, posx, posy;

void setup() {
  Serial.begin(115200);
  Serial.print("Starting...\n");
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pixy.init();
  head.attach(9);
}

void loop() {


  //grab blocks!
  pixy.ccc.getBlocks();

  // If there are detect blocks, print them!
  if (pixy.ccc.numBlocks)

  {
    //Serial.print("Detected ");
    //Serial.println(pixy.ccc.numBlocks);
    for (i = 0; i < pixy.ccc.numBlocks; i++) {
      for (c = 0; c < 2000; c++) {
        heical = (double)32 / (pixy.ccc.blocks[i].m_height);
        widcal = (double)22 / (pixy.ccc.blocks[i].m_width - 1);
        posx = 158 - pixy.ccc.blocks[i].m_x;
        posy = 158 - pixy.ccc.blocks[i].m_y;
        x = (heical + widcal) / 2 * 20;
        tot += x;
      }
      avg = tot / 2000;
      tot = 0;
      //  if (avg <= 10){
      //    if ((posx <=30)&&(posx >=-30)){
      //      head.write(90);
      //    }
      //    else if (posx <0){
      //      head.write(90);
      //    }
      //    else{
      //      head.write(60);
      //    }
      //  }
      if (pixy.ccc.blocks[i].m_signature == 1) {

        //Serial.println(pixy.ccc.blocks[i].m_height);
        Serial.println("Green " + String(avg) + " cm away");
      }
      if (pixy.ccc.blocks[i].m_signature == 2) {
        Serial.println("Red at " + String(avg) + "cm away");
      }

      if (pixy.ccc.blocks[i].m_signature == 1) {
        digitalWrite(7, LOW);
        digitalWrite(8, HIGH);
      } else {
        digitalWrite(7, LOW);
        digitalWrite(8, LOW);
      }



      // Serial.print("  block ");
      // Serial.print(i);
      // Serial.print(": ");
      // pixy.ccc.blocks[i].print();
    }
  }
}

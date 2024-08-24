//www.elegoo.com
//2016.12.08
#include "SR04.h"
#include "pitches.h"
#include <Servo.h>

Servo myservo;
 
// notes in the melody:
int melody[] = {
  NOTE_C2, NOTE_D3, NOTE_E2, NOTE_F4, NOTE_G3, NOTE_A4, NOTE_B4, NOTE_C2};
int duration = 1000;  // 500 miliseconds

//For motor 
#define ENABLE 5
#define DIRA 3
#define DIRB 4

#define TRIG_PIN 12
#define ECHO_PIN 11
SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);
long a;

void setup() {
    //---set pin direction
   pinMode(ENABLE,OUTPUT);
   pinMode(DIRA,OUTPUT);
   pinMode(DIRB,OUTPUT);
   Serial.begin(9600);
   delay(1000);

   digitalWrite(DIRA,LOW); //one way
   digitalWrite(DIRB,HIGH);

   for (int thisNote = 0; thisNote < 8; thisNote++) {
    // pin8 output the voice, every scale is 0.5 sencond
    tone(8, melody[thisNote], duration);

    myservo.attach(22); //attach to pin 9
     
    // Output the voice after several minutes
    delay(150);
  }
}

void loop() {
   a=sr04.Distance();
   Serial.print(a);
   Serial.println("cm");

   //calculate motor speed


   //a 0 to 400

   int set_val = 0;

   if (a > 80)
   {
      set_val = 255 ;
   }
   else
   {
      set_val = (255/80) * a;
   }

   Serial.print("val : ");
   Serial.println(set_val);

   analogWrite(ENABLE,255 - set_val);
   tone(8, 255 - set_val , duration);

   myservo.write(255 - set_val);// move servos to center position -> 90° 

   delay(75);
}
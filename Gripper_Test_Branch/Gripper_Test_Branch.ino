//Gripper_Test_Branch
/*************************************************************
Code Origonally made by Randy Sarafan for Motor Sheild 2-Channel DC Motor Demo
Modified by Devin Becker to work with Robot

Original Code available here.
https://www.instructables.com/id/Arduino-Motor-Shield-Tutorial/



*************************************************************/
#include <Servo.h>
Servo myservo;

void setup(){
    Serial.begin(9600);
   myservo.attach(10);// pinMode(8,OUTPUT);
    myservo.write(90);
}

void close(){
    Serial.print("close\n");
    //digitalWrite(8,HIGH);
    myservo.write(95);
    
}

void open(){
  Serial.print("open\n");
  //digitalWrite(8,LOW);
  myservo.write(85);
}
void loop(){
  if(Serial.available()){
    int var = Serial.parseInt();
    switch (var) {
      case 1: {
        close();
        break; }
       case 2: {
        open();
        break;
      }
      default:{
    }
    }
  }
}
/*#define gripMotor 10
#include <Servo.h>                           // Include servo library
 
Servo servoLeft;                             // Declare left servo signal
Servo servoRight;                            // Declare right servo signal

void setup()                                 // Built in initialization block
{
  Serial.begin (9600);
  servoLeft.attach(gripMotor);                      // Attach left signal to pin 13
  servoRight.attach(gripMotor);                      // Attach left signal to pin 12
}  

void open() {
  servoLeft.writeMicroseconds(700);  
  Serial.println("open");
  delay(1000);
}

void close() {
  servoRight.writeMicroseconds(1500);
  Serial.println("close");
  delay(15);
}
void loop() {  
  Serial.println("waiting");
  delay(15);
  if (Serial.available()) {
     int var = Serial.parseInt();
      Serial.println("Signal REcived");
    switch (var) {
      case 1: { 
       // Forward
       open();
       break;   
      }
      case 0: { 
       // Left
       close();
       break;   
      }

      default: {
        Serial.print(" Open   1");
        Serial.print(" Close  0");
        break;
      }
    }
  }
}   
*/

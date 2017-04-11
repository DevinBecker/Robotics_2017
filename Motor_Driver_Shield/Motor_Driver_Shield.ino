/*************************************************************
Code Origonally made by Randy Sarafan for Motor Sheild 2-Channel DC Motor Demo
Modified by Devin Becker to work with Robot

Original Code available here.
https://www.instructables.com/id/Arduino-Motor-Shield-Tutorial/

*************************************************************/

void setup() {
  Serial.begin(9600);
  //Setup Channel A
  pinMode(12, OUTPUT); //Initiates Motor Channel A pin
  pinMode(9, OUTPUT); //Initiates Brake Channel A pin

  //Setup Channel B
  pinMode(13, OUTPUT); //Initiates Motor Channel A pin
  pinMode(8, OUTPUT);  //Initiates Brake Channel A pin
  
}

void loop() {
  if (Serial.available()) {
    int speed = Serial.parseInt();
    if (speed >= 0 && speed <= 255) {
      //Motor A forward @ full speed
      digitalWrite(12, HIGH); //Establishes forward direction of Channel A
      digitalWrite(9, LOW);   //Disengage the Brake for Channel A
      analogWrite(3, speed);   //Spins the motor on Channel A at full speed

      //Motor B backward @ half speed
      digitalWrite(13, HIGH);  //Establishes backward direction of Channel B
      digitalWrite(8, LOW);   //Disengage the Brake for Channel B
      analogWrite(11, speed);    //Spins the motor on Channel B at half speed
    }
  }
  delay(3000);
  //  digitalWrite(9, HIGH);  //Engage the Brake for Channel A
  //  digitalWrite(9, HIGH);  //Engage the Brake for Channel B
}



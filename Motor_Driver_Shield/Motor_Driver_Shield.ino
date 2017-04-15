/*************************************************************
Code Origonally made by Randy Sarafan for Motor Sheild 2-Channel DC Motor Demo
Modified by Devin Becker to work with Robot

Original Code available here.
https://www.instructables.com/id/Arduino-Motor-Shield-Tutorial/

*************************************************************/
int speed = 155;
int temp = 155;
boolean flagLeft;
boolean flagRight;
void setup() {
  Serial.begin(9600);
  //Setup Channel A
  pinMode(12, OUTPUT); //Initiates Motor Channel A pin
  pinMode(9, OUTPUT); //Initiates Brake Channel A pin

  //Setup Channel B
  pinMode(13, OUTPUT); //Initiates Motor Channel A pin
  pinMode(8, OUTPUT);  //Initiates Brake Channel A pin
  
}

 void forward() {
      flagRight = false;
      flagLeft = false;
      
      Serial.print("Forward\n");
      //Motor A forward @ full speed
      digitalWrite(12, HIGH); //Establishes forward direction of Channel A
      digitalWrite(9, LOW);   //Disengage the Brake for Channel A
      analogWrite(3, speed);   //Spins the motor on Channel A at full speed

      //Motor A forwards @ full speed
      digitalWrite(13, HIGH);  //Establishes backward direction of Channel B
      digitalWrite(8, LOW);   //Disengage the Brake for Channel B
      analogWrite(11, speed);    //Spins the motor on Channel B at half speed
}

void backwards() {
      flagRight = false;
      flagLeft = false;
      
      Serial.print("Backward\n");
      //Motor A backwards @ full speed
      digitalWrite(12, LOW); //Establishes forward direction of Channel A
      digitalWrite(9, LOW);   //Disengage the Brake for Channel A
      analogWrite(3, speed);   //Spins the motor on Channel A at full speed

      //Motor B backwards @ full speed
      digitalWrite(13, LOW);  //Establishes backward direction of Channel B
      digitalWrite(8, LOW);   //Disengage the Brake for Channel B
      analogWrite(11, speed);    //Spins the motor on Channel B at half speed
}

void left() {
      
      if (!flagLeft) temp = speed;
      flagLeft = true;
      flagRight = false;
      Serial.print(flagLeft);
      Serial.print("\n");

      Serial.print(flagRight);
      Serial.print("\n");      
      
      
      Serial.print("left\n");
      //Motor A backwards @ full speed
      digitalWrite(12, HIGH); //Establishes forward direction of Channel A
      digitalWrite(9, LOW);   //Disengage the Brake for Channel A
      analogWrite(3, speed);   //Spins the motor on Channel A at full speed

      //Motor B backwards @ full speed
      digitalWrite(13, HIGH);  //Establishes backward direction of Channel B
      digitalWrite(8, LOW);   //Disengage the Brake for Channel B
      temp = temp + 20;
      analogWrite(11, temp);    //Spins the motor on Channel B at half speed
      Serial.print(temp);
      Serial.print("\n");
}


void right() {
      
      if (!flagRight) temp = speed;
      flagRight = true;
      flagLeft = false;
      Serial.print(flagLeft);
      Serial.print("\n");

      Serial.print(flagRight);
      Serial.print("\n");      
      
      Serial.print("Right\n");
      //Motor A backwards @ full speed
      digitalWrite(12, HIGH); //Establishes forward direction of Channel A
      digitalWrite(9, LOW);   //Disengage the Brake for Channel A
      temp = temp + 20;
      analogWrite(3, temp);   //Spins the motor on Channel A at full speed
      Serial.print(temp);
      Serial.print("\n");
      
      //Motor B backwards @ full speed
      digitalWrite(13, HIGH);  //Establishes backward direction of Channel B
      digitalWrite(8, LOW);   //Disengage the Brake for Channel B
      analogWrite(11, speed);    //Spins the motor on Channel B at half speed
}

void stopp() {
      Serial.print("Stop\n");
      //Motor A backwards @ full speed
      analogWrite(3, 0);   //Spins the motor on Channel A at full speed
      //digitalWrite(9, HIGH);   //Disengage the Brake for Channel A
      
      //Motor B backwards @ full speed
      analogWrite(11, 0);    //Spins the motor on Channel B at half speed
      //digitalWrite(8, HIGH);   //Disengage the Brake for Channel B
}

void inSpeed() {
  Serial.print("faster\n");
  if (speed < 235) {
  speed += 20;
  temp = speed;}
  Serial.print(speed);
  Serial.print("\n");
}

void deSpeed() {
  Serial.print("slower\n");
  if (speed > 20) {
  speed -=20;
  temp = speed;}
  Serial.print(speed);
  Serial.print("\n");
}
//*************************************************************************//


void loop() {
  //Serial.print(speed);
  if (Serial.available()) {
     int var = Serial.parseInt();

    switch (var) {
      
      case 8: { 
       // Forward
       forward();
       break;   
      }
      case 4: { 
       // Left
       left();
       break;   
      }

      case 6: { 
       // Right
       right();
       break;   
      }
      case 2:{ 
       // Backwards
       backwards();
       break;   
      }
      case 5: { 
       // Stop
       stopp();
       break;   
      }

      case 7: {
       // Increase Speed
       inSpeed();
       break;
      }

      case 9: {
       // Decrease Speed
       deSpeed();
       break;
      }

      default: {
        Serial.print(" 7   8   9");
        Serial.print(" 4   5   6"); 
        Serial.print("     2");
        Serial.print(" Forward  8");
        Serial.print(" Left     4");
        Serial.print(" Right    6");
        Serial.print(" Backward 2");
        Serial.print(" Stop     5");
        Serial.print(" Faster   7");
        Serial.print(" Slower   9");
        break;
      }
    }
  }   
}







// Define global variables
// Motors
#define motorLeft 3 //Left  Motor
#define motorRight 5 //Right Motor
// Button for selectable wall
#define buttonPin 7
int lastButtonState = HIGH;
int buttonState;// = digitalRead(buttonPin);
//Wheel speed left and right wheel
int speedL = 85;
int speedR = 85;
//Left wall = 1, Right wall = 2
int wallPrefference = 1; 
// IR Sensor
int sensorValue;// = analogRead(A0); // read the input on analog pin 0:
boolean isThereAWall = 0;
float voltage = 0.0;
// Sonar Sensor
#define trigPinLeft  13
#define echoPinLeft  12
#define ledLeftSonar 11
#define trigPinRight 10
#define echoPinRight  9
#define ledRightSonar 8
boolean followingWall;
long distance;

long getDistance() {
    return distance;
}
void checkSonar() {
    long duration;
    int TrigPin = (wallPrefference == 1) ?  trigPinLeft  : trigPinRight;
    int EchoPin = (wallPrefference == 1) ?  echoPinLeft  : echoPinRight;
    int LED     = (wallPrefference == 1) ?  ledLeftSonar : ledRightSonar;    
    digitalWrite(TrigPin, LOW);  
    delayMicroseconds(2); 
    digitalWrite(TrigPin, HIGH);
    delayMicroseconds(10); 
    digitalWrite(TrigPin, LOW);
    duration = pulseIn(EchoPin, HIGH);
    distance = (duration/2) / 29.1;
    
    if (distance < 20) {  
        digitalWrite(LED,HIGH); 
        followingWall = 1;
        Serial.println(distance);
    }
    else {
        digitalWrite(LED,LOW);
        followingWall = 0;
    }
    delay(125);
}   
void setMotorSpeeds(int state) {
    switch(state) {
    case 1: turnLeft(); break;
    case 2: turnRight(); break;
    case 3: forward(); break;
    default: Serial.println("invalid setMotorSpeeds declaration\nUSAGE: pass an int 1-left 2-right 3-forward\n");
    }
}
void turnLeft() { // 1
   // Serial.println("LEFT");
    delay(525);
    speedL = 0;
    analogWrite(motorLeft, speedL);
}
void turnRight() { // 2
    //Serial.println("RIGHT");
    delay(525);
    speedR = 0;
    analogWrite(motorRight, speedR); 
}
void forward() { // 3
    long distanceFromWall = getDistance();
    if(wallPrefference == 1) {   
        if (distanceFromWall >=4 && distanceFromWall <=12) { 
            speedL = 85;
            speedR = 88;
        }
        else if (distanceFromWall >= 13) { 
            speedL = 85;//
            speedR = 90;
        }
        else if (distanceFromWall <= 3) { 
            speedL = 85;
            speedR = 90;//
        }
    }
    if(wallPrefference == 2) {   
        if (distanceFromWall >=4 && distanceFromWall <=12) { 
            speedL = 88;
            speedR = 85;
        }
        else if (distanceFromWall >= 13) { 
            speedL = 85;//
            speedR = 90;
        }
        else if (distanceFromWall <= 3) { 
            speedL = 90;//
            speedR = 85;
        }
    }
    analogWrite(motorLeft, speedL);
    analogWrite(motorRight, speedR);
}
void checkIR() {
    sensorValue = analogRead(A0);
    voltage = sensorValue * (5.0 / 1023.0); // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
    if (voltage >= 0.6) {
        isThereAWall = 0;
    }
    else if (voltage <= 0.6) {
        isThereAWall = 1;   
    }
}
void avoidFrontCollision(int wallPrefference) {
    //Left wall = 1, Right wall = 2
    if (wallPrefference == 2) {
        turnRight();
        Serial.println("TurnRight");
        delay(225);//
    }
    else {
        turnLeft();
        Serial.println("TurnLeft");
        delay(225);//
    }
}
void checkButton() {
    buttonState = digitalRead(buttonPin);
    if (buttonState==LOW && buttonState!=lastButtonState) {
        changeWallPrefference();  
    }
}
void changeWallPrefference() {
    if (wallPrefference==1) {
        wallPrefference = 2;
    }
    else {
        wallPrefference = 1;
    }
    lastButtonState = buttonState;
    delay(1000);
    lastButtonState = HIGH;
}
void setup() 
{ 
  // initialize serial communication at 9600 bits per second:
  pinMode(motorLeft, OUTPUT);
  pinMode(motorRight, OUTPUT);
  pinMode(buttonPin, INPUT); 
  pinMode(trigPinLeft, OUTPUT);
  pinMode(echoPinLeft, INPUT);
  pinMode(trigPinRight, OUTPUT);
  pinMode(echoPinRight, INPUT);
  pinMode(ledLeftSonar, OUTPUT);
  pinMode(ledRightSonar, OUTPUT);
  Serial.begin(9600);
} 
void loop() { 
    checkButton(); //checks to see if button is pressed and changes which wall the robot follows
    checkIR();
    checkSonar(); //checks to see if there is a wall ahead and avoids a forward collision based on wall prefference
    if (isThereAWall) {
        avoidFrontCollision(wallPrefference);
    }
    if (isThereAWall && !followingWall) {
        if (wallPrefference == 1) {
            speedR = 85;
            analogWrite(motorRight, speedR); 
        }
        else {
            speedL = 85;
            analogWrite(motorLeft, speedL);
        }
         avoidFrontCollision(wallPrefference);
    }
    if (!isThereAWall && followingWall) { //sets default forward direction if no wall is detected ahead
        setMotorSpeeds(3); // pass an int 1-left 2-right 3-forward
    }
    if (!isThereAWall && !followingWall) { //occurs if isThereAWall == 0 and !followingWall == 0, occurs when both false
        int noWallDetected  = (wallPrefference == 1) ? 2 : 1;
        setMotorSpeeds(noWallDetected);
    }   
}
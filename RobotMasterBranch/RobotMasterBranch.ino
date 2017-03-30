// **Define global variables**//

// Motors
#define motorLeft 3 //Left  Motor
#define motorRight 5 //Right Motor


//Wheel speed left and right wheel
int speedL = 85;
int speedR = 85;


// Sonar Sensor
#define trigPinLeft  13
#define echoPinLeft  12
#define ledLeftSonar 11
#define trigPinRight 10
#define echoPinRight  9
#define ledRightSonar 8
boolean followingWall;
long distance;

// Lift Motor
#define tempVar1 port#
#define tempVar2 port#
#define tempVar3 port#

//**Define Program Objects**//

long getSonarDistance()  {}

void checkSonar() { }   

void avoidCollision() {}

void setMotorSpeeds(int state) {}
    analogWrite(motorLeft, speedL);
    analogWrite(motorRight, speedR);
}

/*********************************************/
void setup() { 
} 

void loop() { 
// Main Execution Loop   
}
/*********************************************/

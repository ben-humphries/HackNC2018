#include <RedBot.h>

RedBotMotors motors;

RedBotEncoder encoder = RedBotEncoder(A4, 10);
int buttonPin = 12;

const int COUNTS_PER_REV = 192;
const float WHEEL_DIAMETER = 2.56; //inches
const float WHEEL_CIRCUMFRENCE = WHEEL_DIAMETER * PI; //inches
const float PIVOT_DIAMETER = 7; //inches
const float PIVOT_CIRCUMFRENCE = PIVOT_DIAMETER * PI; //inches


const int NUM_POINTS = 3;
const int MOTOR_POWER = 50;

float currentAngle = 0;

typedef struct {
  float x;
  float y;
} Point;

Point points [NUM_POINTS] = {
  {0,0},
  {1,1},
  {2,2}
};

void setup(){
    pinMode(buttonPin, INPUT_PULLUP);
}

void loop(void){

  for(int i = 0; i < NUM_POINTS-1; i++){

    encoder.clearEnc(BOTH);  // clear the encoder count
    
    float dx = points[i+1].x - points[i].x;
    float dy = points[i+1].y - points[i].y;

    float deltaAngle = atan(dx/dy);

    rotate(deltaAngle);

    driveForward(sqrt(dx*dx + dy*dy));
  }
  
}

void rotate(float deltaAngle){

  if(deltaAngle == 0){
    return;
  }
  
  float distance = (deltaAngle / 360) * PIVOT_CIRCUMFRENCE;
  float numRev = distance / WHEEL_CIRCUMFRENCE;

  long rCount = 0;

  encoder.clearEnc(BOTH);  // clear the encoder count
  
  if(deltaAngle > 0){
      motors.leftMotor(MOTOR_POWER);
  }
  else{
      motors.rightMotor(-MOTOR_POWER);
  }

  while(rCount < numRev*COUNTS_PER_REV){
    rCount = encoder.getTicks(RIGHT);
  }

  currentAngle += deltaAngle;
  motors.brake();
  
}

void driveForward(float distance){

  if(distance <= 0){
    return;
  }

  float numRev = distance / WHEEL_CIRCUMFRENCE;

  long rCount = 0;

  encoder.clearEnc(BOTH);  // clear the encoder count
  
  motors.drive(MOTOR_POWER);

  while(rCount < numRev*COUNTS_PER_REV){
    rCount = encoder.getTicks(RIGHT);
  }

  motors.brake();

  
  
}

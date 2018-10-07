#include <RedBot.h>

RedBotMotors motors;

RedBotEncoder encoder = RedBotEncoder(A2, A4);
int buttonPin = 12;

const int COUNTS_PER_REV = 192;
const float WHEEL_DIAMETER = 2.56; //inches
const float WHEEL_CIRCUMFRENCE = WHEEL_DIAMETER * PI; //inches
const float PIVOT_DIAMETER = 7; //inches
const float PIVOT_CIRCUMFRENCE = PIVOT_DIAMETER * PI; //inches

const float TO_DEGREES = 57.2957795;


const int NUM_POINTS = 40;
const int MOTOR_POWER = 70;

float currentAngle = 60;

typedef struct {
  float x;
  float y;
} Point;

Point points [NUM_POINTS] = {
{ 0 , 0.0 } ,
{ 0.25 , 0.4948079185090459 } ,
{ 0.5 , 0.958851077208406 } ,
{ 0.75 , 1.3632775200466685 } ,
{ 1.0 , 1.682941969615793 } ,
{ 1.25 , 1.8979692387111724 } ,
{ 1.5 , 1.994989973208109 } ,
{ 1.75 , 1.9679718937478738 } ,
{ 2.0 , 1.8185948536513634 } ,
{ 2.25 , 1.5561463937758426 } ,
{ 2.5 , 1.1969442882079129 } ,
{ 2.75 , 0.7633219841046633 } ,
{ 3.0 , 0.2822400161197344 } ,
{ 3.25 , -0.21639026906021674 } ,
{ 3.5 , -0.7015664553792397 } ,
{ 3.75 , -1.1431226374846877 } ,
{ 4.0 , -1.5136049906158564 } ,
{ 4.25 , -1.789978716457167 } ,
{ 4.5 , -1.955060235330194 } ,
{ 4.75 , -1.998585577950756 } ,
{ 5.0 , -1.917848549326277 } ,
{ 5.25 , -1.7178689868531842 } ,
{ 5.5 , -1.4110806511407838 } ,
{ 5.75 , -1.0165581549985165 } ,
{ 6.0 , -0.5588309963978517 } ,
{ 6.25 , -0.06635843309511363 } ,
{ 6.5 , 0.43023997617563103 } ,
{ 6.75 , 0.9000881475612352 } ,
{ 7.0 , 1.3139731974375781 } ,
{ 7.25 , 1.6461617580230108 } ,
{ 7.5 , 1.8759999535494778 } ,
{ 7.75 , 1.9891975582223522 } ,
{ 8.0 , 1.9787164932467636 } ,
{ 8.25 , 1.8452084204786805 } ,
{ 8.5 , 1.5969742252469805 } ,
{ 8.75 , 1.2494479075083849 } ,
{ 9.0 , 0.8242369704835132 } ,
{ 9.25 , 0.3477789707608671 }};

void setup(){
    pinMode(buttonPin, INPUT_PULLUP);

    Serial.begin(9600);
    
    for(int i = 1; i < NUM_POINTS-1; i++){
      Serial.println("");
      Serial.println(points[i].y);
      encoder.clearEnc(BOTH);  // clear the encoder count
      
      float dx = points[i+1].x - points[i].x;
      float dy = points[i+1].y - points[i].y;
  
      float deltaAngle = asin(dx/sqrt(dx*dx + dy*dy)) * TO_DEGREES - currentAngle;
      //float deltaAngle = -90;
      rotate(deltaAngle);
      delay(200);

      driveForward(sqrt(dx*dx + dy*dy));
      delay(200);
  }
}

void loop(void){
  
}

void rotate(float deltaAngle){
  Serial.print("Current: ");
  Serial.println(currentAngle);
  Serial.print("Delta: ");
  Serial.println(deltaAngle);
  if(deltaAngle == 0){
    return;
  }
  
  float distance = (deltaAngle / 360) * PIVOT_CIRCUMFRENCE;
  float numRev = abs(distance / WHEEL_CIRCUMFRENCE);

  long rCount = 0;

  encoder.clearEnc(BOTH);  // clear the encoder count
  
  if(deltaAngle > 0){
      motors.leftMotor(-MOTOR_POWER);
      motors.rightMotor(-MOTOR_POWER);
  }
  else{
      motors.rightMotor(MOTOR_POWER);
      motors.leftMotor(MOTOR_POWER);
  }

  while(abs(rCount) < numRev*COUNTS_PER_REV){
    rCount = encoder.getTicks(LEFT);
    Serial.print(rCount);
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

  while(abs(rCount) < numRev*COUNTS_PER_REV){
    rCount = encoder.getTicks(LEFT);
    Serial.print(rCount);
  }

  motors.brake();

  
  
}

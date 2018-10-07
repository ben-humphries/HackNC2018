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
{0 , 5.0 },
{ 0.5 , 4.5051920814909545 } ,
{ 1.0 , 4.041148922791594 } ,
{ 1.5 , 3.6367224799533315 } ,
{ 2.0 , 3.317058030384207 } ,
{ 2.5 , 3.1020307612888276 } ,
{ 3.0 , 3.005010026791891 } ,
{ 3.5 , 3.032028106252126 } ,
{ 4.0 , 3.1814051463486366 } ,
{ 4.5 , 3.4438536062241574 } ,
{ 5.0 , 3.803055711792087 } ,
{ 5.5 , 4.236678015895337 } ,
{ 6.0 , 4.717759983880265 } ,
{ 6.5 , 5.216390269060216 } ,
{ 7.0 , 5.70156645537924 } ,
{ 7.5 , 6.143122637484687 } ,
{ 8.0 , 6.513604990615857 } ,
{ 8.5 , 6.789978716457167 } ,
{ 9.0 , 6.955060235330194 } ,
{ 9.5 , 6.998585577950756 } ,
{ 3.0 , 6.994989973208109 } ,
{ 3.5 , 6.967971893747874 } ,
{ 4.0 , 6.818594853651364 } ,
{ 4.5 , 6.556146393775842 } ,
{ 5.0 , 6.196944288207913 } ,
{ 5.5 , 5.763321984104663 } ,
{ 6.0 , 5.282240016119735 } ,
{ 6.5 , 4.783609730939784 } ,
{ 7.0 , 4.29843354462076 },
{ 7.5 , 3.8568773625153123 }};

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

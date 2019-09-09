#include "datafield.h"
#include "arrays.h" 
#include "functions.h"
#include "cases.h" 

void setup() {
  
  Serial.begin(9600);

  pwm.begin();
  pwm.setPWMFreq(60);  
  
  
  pinMode (trigPin, OUTPUT);
  pinMode (echoPin, INPUT);
  pinMode (led,     OUTPUT);
  pinMode (LimFR,   INPUT_PULLUP);
  pinMode (LimFL,   INPUT_PULLUP);
  pinMode (LimBR,   INPUT_PULLUP);
  pinMode (LimBL,   INPUT_PULLUP);

  motionState = STOPPED;      
  turtleMode = T_STOPPED;
  aStoppedIndex = 0; 
  setTimer(2);      
}


void loop() {
  int status = STOPPED;
  Serial.println(currentLimSwitchFL);
  Serial.println(currentLimSwitchFR);
  currentLimSwitchFR = digitalRead(LimFR);
  currentLimSwitchFL = digitalRead(LimFL);
  currentLimSwitchBR = digitalRead(LimBR);
  currentLimSwitchBL = digitalRead(LimBL);
  turtleHeart();

  unsigned int distance = takeSounding_cm();  
  msecCount = millis();
  Serial.println(msecCount);

  if (motionTarget !=0 && msecCount > motionTarget) {
    changeMotionState = true;
    motionTarget = 0;  
  }
  
  if (legMotionTarget == 0) { 
   // pwm.setPWM(FR_Leg, 0, 410); 
    //pwm.setPWM(FL_Leg, 0, 320); 
   // pwm.setPWM(BR_Leg, 0, 320); 
   // pwm.setPWM(BL_Leg, 0, 410);
  }
  	else if (msecCount > legMotionTarget) {
	//invertLegDirection();
	 // setLegTimer(MOVE_LEG_TIME);
	}

  
  int brightness = analogRead(lightPin);



  /*************************************************************************
  Turtle operating modes 
    
  **************************************************************************/
  switch (turtleMode) {
    case T_FORWARD:
        heartRate = CALM;
          if (msecCount < 5000) {
            heartRate = CALM;
            turtleMode = T_CENTERFR;
            aForwardIndex = 0;
            aCenterIndex = 0;
            changeMotionState = true;
          }
       else if (analogRead( lightPin) >= minLight) {
          heartRate = HUNTING;
          turtleMode = T_HUNT;
          aForwardIndex = 0;
          aHuntIndex = 0;
          changeMotionState = true;
        }
        else if (distance <= minDistance) {
          heartRate = SCARED;
          turtleMode = T_BACK;
          aForwardIndex = 0;
          aBackwardsIndex = 0;  
          changeMotionState = true;  
        } else {
          status = ProcessCommand(aForwardCmd, &aForwardIndex, sizeof(aForwardCmd));
          if (status == END_CMD) {
            aForwardIndex = 0;
            turtleMode = T_HUNT;
          }
        }
      break;

    case T_BACK:
      if (distance >= 50){
        turtleMode = T_AVOIDANCE;
        aForwardIndex = 0;
        aAvoidanceIndex = 0;  
        changeMotionState = true;
      }
      
      else{
        status = ProcessCommand(aBackwardsCmd, &aBackwardsIndex, sizeof(aBackwardsCmd));
        if (status == END_CMD) {
          aBackwardsIndex = 0;
          turtleMode = T_FORWARD;
        }
      }
      break;

    case T_HUNT:
      if (analogRead(lightPin) >= maxLight){
        heartRate = HUNTING;
        turtleMode = T_HUNT2;
        aForwardIndex = 0;
        aHunt2Index = 0;  
        changeMotionState = true;
      }
      
      else{
       status = ProcessCommand(aHuntCmd, &aHuntIndex, sizeof(aHuntCmd));
        if (status == END_CMD) {
          aBackwardsIndex = 0;
          turtleMode = T_FORWARD;
        }
      }
      break;
      
    case T_HUNT2:
      status = ProcessCommand(aHunt2Cmd, &aHunt2Index, sizeof(aHunt2Cmd));
      heartRate = HUNTING;
      if (status == END_CMD) {
        aAvoidanceIndex = 0;
        turtleMode = T_AVOIDANCE;
        changeMotionState = true;
      }
      break;

    case T_AVOIDANCE:
      status = ProcessCommand(aAvoidanceCmd, &aAvoidanceIndex, sizeof(aAvoidanceCmd));
      heartRate = SCARED;
      if (status == END_CMD) {
        aAvoidanceIndex = 0;
        turtleMode = T_FORWARD;
        changeMotionState = true;
      }
      break;

    case T_STOPPED:
      status = ProcessCommand(aStoppedCmd, &aStoppedIndex,sizeof(aStoppedCmd));
      heartRate = CALM;
      if (status == END_CMD) {
        aStoppedIndex = 0;
        turtleMode = T_FORWARD;
        changeMotionState = true;     
      }
      break;

    case T_CENTERFR:
      status = ProcessCommand(aCenterFRCmd, &aCenterFRIndex, sizeof(aCenterFRCmd));
      heartRate = CALM;
      if (status == END_CMD) {
        aCenterFRIndex = 0;
        turtleMode = T_CENTERFL;
        changeMotionState = true;
      }
      else Serial.println("uh oh");
      break;

      case T_CENTERFL:
      status = ProcessCommand(aCenterFLCmd, &aCenterFLIndex, sizeof(aCenterFLCmd));
      heartRate = CALM;
      if (status == END_CMD) {
        aCenterFLIndex = 0;
        turtleMode = T_CENTERBL;
        changeMotionState = true;
      }
       else Serial.println("uh oh");
      break;

      case T_CENTERBL:
      status = ProcessCommand(aCenterBLCmd, &aCenterBLIndex, sizeof(aCenterBLCmd));
      heartRate = CALM;
      if (status == END_CMD) {
        aCenterBLIndex = 0;
        turtleMode = T_CENTERBR;
        changeMotionState = true;
      }
       else Serial.println("uh oh");
      break;

      case T_CENTERBR:
      status = ProcessCommand(aCenterBRCmd, &aCenterBRIndex, sizeof(aCenterBRCmd));
      heartRate = CALM;
      if (status == END_CMD) {
        aCenterBRIndex = 0;
        turtleMode = T_FORWARD;
        changeMotionState = true;
      }
       else Serial.println("uh oh");
      break;
         
    default:
    //  Serial.println("ILLEGAL MODE");
      break;
  }
}


int ProcessCommand(int cmdArray[], int *pIndex, int aSize) {

  if (changeMotionState) {
    changeMotionState = false;
    (*pIndex)++;   
    if(*pIndex > aSize) {
//      Serial.print("SOMETHING TERRIBLE HAPPENED!  INDEX ");
//      Serial.print(*pIndex);
//      Serial.print(" arraySize = ");
//      Serial.print(sizeof(cmdArray));
//      Serial.println(" OUT OF BOUNDS!");
      (*pIndex) = 0;
      return END_CMD;
    }
  
    int cmd = cmdArray[*pIndex];
    switch(cmd){
      case STOPPED:
        stopped( );
        break;
          
      case OPEN_MOUTH:
        openMouth( );
        break;
          
      case CLOSE_MOUTH:
        closeMouth( );
        break;
          
      case WAG_TAIL_LEFT:
        wagTailLeft( ); 
        break;
          
      case WAG_TAIL_RIGHT:
        wagTailRight( ); 
        break;
          
      case LEFT_FORWARD:
        leftForward( );
        break;

      case CENTER_FR:
        centerFR( );
        break;

      case CENTER_FL:
        centerFL( );
        break;
        
      case CENTER_BL:
        centerBL( );
        break;
        
      case CENTER_BR:
        centerBR( );
        break;
 
      case RIGHT_FORWARD:
        rightForward( );
        break;
          
      case RIGHT_BACK:
        rightBack( );
        break;
          
      case MOVE_FWD:        
        moveForward( );
        break;

       case MOVE_FWD2:        
         moveForward2( );
         break;
  
      case MOVE_NECK_FWD:
        moveNeckForward( );
        break;  
        
      case MOVE_NECK_BACK:
        moveNeckBack( );
        break;  

      case BACKWARDS:
        backwards( );
        break;
       
      case END_CMD:
        break;
    }
  }
  return cmdArray[*pIndex];
}

unsigned int takeSounding_cm() {
  static int lastDist= -1;
  digitalWrite (trigPin, LOW);
  delayMicroseconds (2);
  digitalWrite (trigPin, HIGH);
  delayMicroseconds (10);
  digitalWrite (trigPin, LOW);
  delayMicroseconds (2);
  unsigned long duration = pulseIn (echoPin, HIGH);
  unsigned int distance = duration * cmConversion;

  
  if (distance < 0){
    distance = 40; 
  }
  if (lastDist < 0) {
    if (distance != 0) {
      lastDist = distance;
    }
  }

  if (abs(lastDist - distance) < 8) {
    distance = lastDist;
  }
  
  return distance;
  
}

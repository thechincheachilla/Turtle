

void stopped( ) {
  pwm.setPWM(F_WheelTurn, 0, 285);              
  pwm.setPWM(F_WheelPower, 0, 349);  
  pwm.setPWM(B_WheelPower, 0, 349);          
  pwm.setPWM(Tail, 0, 400);
  motionState = STOPPED;
  setTimer(STOP_AVOID_TIME);  
}

void openMouth( ) {
  pwm.setPWM(Mouth, 0, 565);
  motionState = OPEN_MOUTH;
  setTimer(OPEN_MOUTH_TIME);
}

void closeMouth( ) {
  pwm.setPWM(Mouth, 0, 135);
  motionState = CLOSE_MOUTH;
  setTimer(CLOSE_MOUTH_TIME);
}

void wagTailLeft( ) {
  pwm.setPWM(Tail, 0, 230);
  motionState = WAG_TAIL_LEFT;
  setTimer(WAG_TAIL_TIME);
}

void wagTailRight( ) {
  pwm.setPWM(Tail, 0, 510);
  motionState = WAG_TAIL_RIGHT;
  setTimer(WAG_TAIL_TIME);
}

void leftForward( ) {          
  pwm.setPWM(F_WheelTurn, 0, 440);              
  pwm.setPWM(F_WheelPower, 0, 400);         
  pwm.setPWM(B_WheelPower, 0, 377);
  motionState = LEFT_FORWARD;
  setTimer(LEFT_FORWARD_TIME); 
}


void centerFR( ) {
  if (currentLimSwitchFR == PRESSED){
    pwm.setPWM(FR_Leg, 0, 500);
  } else if (currentLimSwitchFR == RELEASED){
    pwm.setPWM(FR_Leg, 0, 150);
  }
  motionState = CENTER_FR; 

}

void centerFL( ) {
  if (currentLimSwitchFL == PRESSED){
    pwm.setPWM(FL_Leg, 0, 150);
  } else if (currentLimSwitchFL == RELEASED){
      pwm.setPWM(FL_Leg, 0, 600); 
  }
  motionState = CENTER_FL; 
  setTimer(CENTER_LEGS_TIME);
}

void centerBL( ) {
  if (currentLimSwitchBL == PRESSED){
    pwm.setPWM(BL_Leg, 0, 350);
  } else if (currentLimSwitchBL == RELEASED){
      pwm.setPWM(BL_Leg, 0, 150);
  }
  motionState = CENTER_BL; 
  setTimer(CENTER_LEGS_TIME);
}

void centerBR( ) {
  if (currentLimSwitchBR == PRESSED){
    pwm.setPWM(BR_Leg, 0, 349);
  } else if (currentLimSwitchBR == RELEASED){
      pwm.setPWM(BR_Leg, 0, 600); 
  }
  motionState = CENTER_BR; 
  setTimer(CENTER_LEGS_TIME);
}



void rightForward( ) { 
  pwm.setPWM(F_WheelTurn, 0, 200);             
  pwm.setPWM(F_WheelPower, 0, 400);
  pwm.setPWM(B_WheelPower, 0, 377);          
  motionState = RIGHT_FORWARD;
  setTimer(RIGHT_FORWARD_TIME); 
}

void rightBack( ) {
  pwm.setPWM(F_WheelTurn, 0, 200);             
  pwm.setPWM(B_WheelPower, 0, 320);
  pwm.setPWM(F_WheelPower, 0, 250);   
  motionState = RIGHT_BACK;
  setTimer(RIGHT_BACK_TIME); 
}

void moveForward( ) {
  pwm.setPWM(F_WheelTurn, 0, 285);            
  pwm.setPWM(F_WheelPower, 0, 500);  
  pwm.setPWM(B_WheelPower, 0, 377);          
  pwm.setPWM(Tail, 0, 400);
}

void moveForward2( ){
  pwm.setPWM(F_WheelTurn, 0, 285);             
  pwm.setPWM(F_WheelPower, 0, 500);  
  pwm.setPWM(FR_Leg, 0, 150); 
  pwm.setPWM(FL_Leg, 0, 600); 
  pwm.setPWM(BR_Leg, 0, 600); 
  pwm.setPWM(BL_Leg, 0, 150);
  pwm.setPWM(B_WheelPower, 0, 377);          
  pwm.setPWM(Tail, 0, 400);
}

void moveNeckForward( ){
  pwm.setPWM(L_Neck, 0, 600);
  pwm.setPWM(R_Neck, 0, 150);
  motionState = MOVE_NECK_FWD;
  setTimer(NECK_FWD_TIME);
}

void moveNeckBack( ){
   pwm.setPWM(L_Neck, 0, 150);
   pwm.setPWM(R_Neck, 0, 600);
   motionState = MOVE_NECK_FWD;
   setTimer(NECK_BACK_TIME);
}

void backwards( ){
  pwm.setPWM(F_WheelPower, 0, 250);
  pwm.setPWM(B_WheelPower, 0, 320);
}

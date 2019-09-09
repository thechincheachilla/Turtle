void setTimer(unsigned long numSec) {
  motionTarget = msecCount + numSec;
  if (motionTarget == 0) {
    motionTarget++;
  }
}

void turtleHeart() {
  analogWrite(led, brightness); 
  
  if(loopCount == 0){
    
    //Serial.println(heartRate);
    loopCount=heartRate;
  
    brightness = brightness + fadeAmount;   
                                          
    if (brightness<=0 || brightness >=250){  
      fadeAmount = -fadeAmount;            
    }
  }
  loopCount--;

}


#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN  150 
#define SERVOMAX  600 

unsigned long msecCount = 0; 
unsigned int secCount = 0;

//-----------------------------
// Timeout Values (mSec)
//-----------------------------

#define STOP_AVOID_TIME      3000
#define OPEN_MOUTH_TIME      1500
#define CLOSE_MOUTH_TIME     1500
#define WAG_TAIL_TIME        1000
#define MOVE_LEG_TIME        500 
#define LEFT_FORWARD_TIME    2000
#define RIGHT_BACK_TIME      2000
#define RIGHT_FORWARD_TIME   2000
#define NECK_FWD_TIME        1000
#define NECK_BACK_TIME       1000
#define START_LEG_TIME       350
#define FIX_LEGS_TIME        10
#define CENTER_LEGS_TIME     2000

//-----------------------------
// End Timeout Values
//-----------------------------






//-----------------------------
// Motion States
//-----------------------------

#define BEGIN           0
#define STOPPED         1
#define MOVE_LEFT       2
#define MOVE_RIGHT      3
#define MOVE_UP         4
#define MOVE_DOWN       5
#define MOVE_FWD        6
#define MOVE_BACK       7
#define OPEN_MOUTH      8
#define CLOSE_MOUTH     9
#define WAG_TAIL_LEFT   10
#define WAG_TAIL_RIGHT  11
#define RIGHT_BACK      12
#define LEFT_BACK       13
#define LEFT_FORWARD    14
#define RIGHT_FORWARD   15
#define MOVE_NECK_FWD   16
#define MOVE_NECK_BACK  17
#define BACKWARDS       18
#define MOVE_FWD2       19
//#define CENTER_LEGS     20
#define CENTER_FR       21
#define CENTER_FL       22
#define CENTER_BL       23
#define CENTER_BR       24
#define START_UP_LEGS   25
#define END_CMD         255
boolean changeMotionState = false;
unsigned int     motionState       = STOPPED;
unsigned long    motionTarget      = 0;
unsigned long    legMotionTarget   = 0;
bool             leftLegForward    = true;
//int            servoPos          = 90;    // centered

//-----------------------------------------------------
// End Motion States
//-----------------------------------------------------



//-----------------------------------------------------
// LED States 
//-----------------------------------------------------
#define CALM      30
#define SCARED    2 
#define HUNTING   10 





//-----------------------------
// Turtle Modes
//-----------------------------
// Each turtle mode owns an array of commands that are executed
// when in that mode.
// Turtle Modes
#define T_STOPPED      0
#define T_FORWARD      1
#define T_AVOIDANCE    2
#define T_HUNT         3
#define T_HUNT2        4
#define T_BACK         5
//#define T_CENTER       6
#define T_CENTERFR     7
#define T_CENTERFL     8
#define T_CENTERBL     9
#define T_CENTERBR     10
int turtleMode  = T_FORWARD;
//-----------------------------
// End Turtle Modes
//-----------------------------




/*************************************************************************
  Heartrate
  Pinouts and variables for the LED strip
    
**************************************************************************/

int led = 9;
int brightness = 0;
int fadeAmount = 6; 
int heartRate = CALM; 
int loopCount = heartRate;

//-----------------------------
// End Heartrate
//-----------------------------


/*************************************************************************
  Eyes
  Pinouts and variables for photoresistor
    
**************************************************************************/

int lightPin  = 53;  
const unsigned int minLight = 3000; 
const unsigned int maxLight = 4000; 

//-----------------------------
// End Eyes
//-----------------------------




/*************************************************************************
  Limit Switches
  Pinouts and variables for limit switches
    
**************************************************************************/
#define PRESSED LOW
#define RELEASED HIGH

int currentLimSwitchFR = RELEASED;
int currentLimSwitchFL = RELEASED;
int currentLimSwitchBR = RELEASED;
int currentLimSwitchBL = RELEASED;

int LimFR = 23;
int LimFL = 22;
int LimBR = 25;
int LimBL = 24;

//-----------------------------
// End Limit Switches
//-----------------------------



/*************************************************************************
  Sensor
  Pinouts and variables for ultrasonic sensor
    
**************************************************************************/
const int echoPin   = 27;    
const int trigPin   = 29;    

const float cmConversion = 0.017;
const unsigned int   maxDistance  = 200;
const unsigned int   minDistance  = 40;   

//-----------------------------
// End Sensor
//-----------------------------



/*************************************************************************
  Motors
  Pinouts and variables for all servo motors. uint8_t calls the adafruit 
  i2c board. 
    
**************************************************************************/

uint8_t F_WheelTurn = 1;
uint8_t F_WheelPower = 0;
uint8_t B_WheelPower = 9;
uint8_t Tail = 2;
uint8_t BL_Leg = 6;
uint8_t BR_Leg = 5;
uint8_t FL_Leg = 8;
uint8_t FR_Leg = 7;
uint8_t L_Neck = 3;
uint8_t R_Neck = 4;
uint8_t Mouth = 10;

//-----------------------------
// End Motors
//-----------------------------

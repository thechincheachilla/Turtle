
//-----------------------------
// Arrays
//-----------------------------

int aAvoidanceIndex = 0;
int aForwardIndex   = 0;
int aStoppedIndex   = 0;
int aHuntIndex      = 0;
int aBackwardsIndex = 0;
int aHunt2Index     = 0;
int aCenterIndex    = 0;
int aCenterFRIndex  = 0;
int aCenterFLIndex  = 0;
int aCenterBLIndex  = 0;
int aCenterBRIndex  = 0;

int aAvoidanceCmd[] = {BEGIN, STOPPED, OPEN_MOUTH, WAG_TAIL_LEFT, WAG_TAIL_RIGHT, 
                       WAG_TAIL_LEFT, WAG_TAIL_RIGHT, RIGHT_BACK, LEFT_FORWARD, 
                      LEFT_FORWARD, RIGHT_FORWARD, END_CMD};

int aHuntCmd[]      = {BEGIN, MOVE_FWD, END_CMD};    

int aHunt2Cmd[]     = {BEGIN, STOPPED, MOVE_NECK_FWD, OPEN_MOUTH, CLOSE_MOUTH,
                      OPEN_MOUTH, CLOSE_MOUTH, MOVE_NECK_BACK, WAG_TAIL_LEFT, WAG_TAIL_RIGHT, 
                      RIGHT_BACK, LEFT_FORWARD, LEFT_FORWARD, RIGHT_FORWARD, END_CMD};

int aForwardCmd[]   = {BEGIN, MOVE_FWD, END_CMD};

int aStoppedCmd[]   = {BEGIN,  STOPPED, END_CMD};

int aBackwardsCmd[] = {BEGIN, STOPPED, BACKWARDS, END_CMD};

int aCenterFRCmd[]    = {BEGIN, CENTER_FR, END_CMD};

int aCenterFLCmd[]    = {BEGIN, CENTER_FL, END_CMD};

int aCenterBLCmd[]    = {BEGIN, CENTER_BL, END_CMD};

int aCenterBRCmd[]    = {BEGIN, CENTER_BR, END_CMD};

int aStartlegsCmd[] = {BEGIN, START_UP_LEGS, END_CMD};

//-----------------------------
// End Arrays
//-----------------------------


// ROTARY ENCODER
#define CLK 2
#define DT 3
long rotaryCount = 0;
long lastRotaryCount = 0;



// POTENTIOMETERS //

const int pot1 = A5;  // potentiometer pins
const int pot2 = A6;
const int pot3 = A7;
const int pot4 = A8;
const int pot5 = A9;

const int slidePot1 = A0;
const int slidePot2 = A1;
const int slidePot3 = A2;
const int slidePot4 = A3;
const int slidePot5 = A4;

int potVal1 = 0;
int potVal2 = 0;
int potVal3 = 0;
int potVal4 = 0;
int potVal5 = 0;

int slidePotVal1 = 0;
int slidePotVal2 = 0;
int slidePotVal3 = 0;
int slidePotVal4 = 0;
int slidePotVal5 = 0;

int lastPotVal1 = 0;
int lastPotVal2 = 0;
int lastPotVal3 = 0;
int lastPotVal4 = 0;
int lastPotVal5 = 0;

int lastSlidePotVal1 = 0;
int lastSlidePotVal2 = 0;
int lastSlidePotVal3 = 0;
int lastSlidePotVal4 = 0;
int lastSlidePotVal5 = 0;

// SWITCHES

int isPressed1 = 0;
int isPressed2 = 0;
int isPressed3 = 0;
int isPressed4 = 0;
int isPressed5 = 0;

int switch1 = 47;
int switch2 = 48;
int switch3 = 49;
int switch4 = 50;
int switch5 = 51;



void setup() {
  //   ROTARY ENCODER
  pinMode(CLK, INPUT_PULLUP);
  pinMode(DT, INPUT_PULLUP);
  attachInterrupt (0, rotaryTurn, RISING); 

  //SWITCHES

  pinMode(switch1, INPUT_PULLUP);
  pinMode(switch2, INPUT_PULLUP);
  pinMode(switch3, INPUT_PULLUP);
  pinMode(switch4, INPUT_PULLUP);
  pinMode(switch5, INPUT_PULLUP);
  
  
  Serial.begin(115200); // enable serial communication


}


void loop() {

  readSwitches();
  readPots();         // read potentiometers
  readRotaryEnc();

}

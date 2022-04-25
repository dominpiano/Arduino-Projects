
#define keyNum 10


bool currentState[keyNum] = {false};
bool requestState[keyNum];
int noteBase = 60;
int counter = 0;
bool even = true;
int octave = 0; // Add or subtract 8 to get higher or lower octave




void setup() {
  //setting up pins
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  pinMode(A6, INPUT);
  pinMode(A7, INPUT);
  pinMode(A8, INPUT);
  pinMode(A9, INPUT);
  
  
  Serial.begin(115200);
  
}

void loop() {
  readKeys();
  writeKeys();
  delay(1);
}

void readKeys(){
  for(int i = 0; i < keyNum; i++){
    if(analogRead(i) > 250){
      requestState[i] = true;
    }else{
      requestState[i] = false;
    }
  }
}

// Checking if any is on and requesting a note

void writeKeys(){
  for(int i = 0; i < keyNum; i++)
  {
    if(requestState[i] == true && currentState[i] == false){
      if(i%4 == 3){
          MIDImessage(144, noteBase + i * 2 - 1 - (i/4), 127);
      }else{
          MIDImessage(144, noteBase + i * 2 - 2 * (i/4) - (i/4) + (i/4)*2, 127);
      }
      currentState[i] = requestState[i];
    }
    
    if(requestState[i] == false && currentState[i] == true){
      if(i%4 == 3){
          MIDImessage(128, noteBase + i * 2 - 1 - (i/4), 127);
      }else{
          MIDImessage(128, noteBase + i * 2 - 2 * (i/4) - (i/4) + (i/4)*2, 127);
      }
      currentState[i] = requestState[i];
    }
  }
}


void MIDImessage(byte status, byte data1, byte data2){
  Serial.write(status);
  Serial.write(data1);
  Serial.write(data2);
}

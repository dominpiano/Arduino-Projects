void readSwitches(){
  if(digitalRead(switch1) == 0 && isPressed1 == 0){
    MIDImessage(178,0,127);
    isPressed1 = 1;
    delay(200);
  }
  if(digitalRead(switch1) == 0 && isPressed1 == 1){
    MIDImessage(178,0,0);
    isPressed1 = 0;
    delay(200);
  }

  if(digitalRead(switch2) == 0 && isPressed2 == 0){
    MIDImessage(178,1,127);
    isPressed2 = 1;
    delay(200);
  }
  if(digitalRead(switch2) == 0 && isPressed2 == 1){
    MIDImessage(178,1,0);
    isPressed2 = 0;
    delay(200);
  }
}

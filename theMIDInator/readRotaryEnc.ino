void readRotaryEnc(){ 
  if (lastRotaryCount != rotaryCount) {
    Serial.println(rotaryCount);
    lastRotaryCount = rotaryCount;
  }
}

void rotaryTurn(){
    if (digitalRead(DT)){
      if(rotaryCount < 20){
        rotaryCount++;
      }else{
        rotaryCount = 0;
      }
    }else{
      if(rotaryCount > 0){
        rotaryCount--;
      }else{
        rotaryCount = 20;
      }
    }
} 

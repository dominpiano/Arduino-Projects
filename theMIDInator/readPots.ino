void readPots() {

  int diff = 4; // difference amount

  // READ POTENTIOMETERS //
  
  potVal1 = analogRead(pot1);
  potVal2 = analogRead(pot2);
  potVal3 = analogRead(pot3);
  potVal4 = analogRead(pot4);
  potVal5 = analogRead(pot5);
  
  slidePotVal1 = analogRead(slidePot1);
  slidePotVal2 = analogRead(slidePot2);
  slidePotVal3 = analogRead(slidePot3);
  slidePotVal4 = analogRead(slidePot4);
  slidePotVal5 = analogRead(slidePot5);

  // CALCULATE DIFFERENCE BETWEEN NEW VALUE AND LAST RECORDED VALUE //
  
  int potVal1diff = potVal1 - lastPotVal1;
  int potVal2diff = potVal2 - lastPotVal2;
  int potVal3diff = potVal3 - lastPotVal3;
  int potVal4diff = potVal4 - lastPotVal4;
  int potVal5diff = potVal5 - lastPotVal5;
  
  int slidePotVal1diff = slidePotVal1 - lastSlidePotVal1;
  int slidePotVal2diff = slidePotVal2 - lastSlidePotVal2;
  int slidePotVal3diff = slidePotVal3 - lastSlidePotVal3;
  int slidePotVal4diff = slidePotVal4 - lastSlidePotVal4;
  int slidePotVal5diff = slidePotVal5 - lastSlidePotVal5;

  // SEND MIDI MESSAGE //
  
    //ROTPOTS------------------------------------------
    if (abs(potVal1diff) > diff){
      MIDImessage(176, rotaryCount*5 + 0, map(potVal1, 1023, 0, 0, 127));   // map sensor range to MIDI range
      lastPotVal1 = potVal1;                                                // reset old value with new reading
    }
  
    if (abs(potVal2diff) > diff){
      MIDImessage(176, rotaryCount*5 + 1, map(potVal2, 1023, 0, 0, 127));
      lastPotVal2 = potVal2;
    }
  
    if (abs(potVal3diff) > diff){
      MIDImessage(176, rotaryCount*5 + 2, map(potVal3, 1023, 0, 0, 127));
      lastPotVal3 = potVal3;
    }
    
    if (abs(potVal4diff) > diff){
      MIDImessage(176, rotaryCount*5 + 3, map(potVal4, 1023, 0, 0, 127));
      lastPotVal4 = potVal4;
    }
    
//    if (abs(potVal5diff) > diff){
//      MIDImessage(176, rotaryCount*5 + 4, map(potVal5, 1023, 0, 0, 127));
//      lastPotVal5 = potVal5;
//    }


    //SLIDES----------------------------------
    if (abs(slidePotVal1diff) > diff){
      MIDImessage(177, rotaryCount*5 + 0, map(slidePotVal1, 1023, 0, 0, 127));   // map sensor range to MIDI range
      lastSlidePotVal1 = slidePotVal1;                                           // reset old value with new reading
    }
  
    if (abs(slidePotVal2diff) > diff){
      MIDImessage(177, rotaryCount*5 + 1, map(slidePotVal2, 1023, 0, 0, 127));
      lastSlidePotVal2 = slidePotVal2;
    }
  
    if (abs(slidePotVal3diff) > diff){
      MIDImessage(177, rotaryCount*5 + 2, map(slidePotVal3, 1023, 0, 0, 127));
      lastSlidePotVal3 = slidePotVal3;
    }
    
    if (abs(slidePotVal4diff) > diff){
      MIDImessage(177, rotaryCount*5 + 3, map(slidePotVal4, 1023, 0, 0, 127));
      lastSlidePotVal4 = slidePotVal4;
    }
    
    if (abs(slidePotVal5diff) > diff){
      MIDImessage(177, rotaryCount*5 + 4, map(slidePotVal5, 1023, 0, 0, 127));
      lastSlidePotVal5 = slidePotVal5;
    }

  delay(2); // small delay further stabilizes sensor readings

}

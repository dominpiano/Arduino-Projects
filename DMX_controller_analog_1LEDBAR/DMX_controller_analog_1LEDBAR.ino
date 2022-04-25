#include <DmxSimple.h>

long strobeSpeed, effectSpeed = 2500;
float counter, counterColor = 0;
int red, green, blue, master;
int tmpMaster;
int flicCount = 0;

boolean isStrobe = false;
boolean isActive = true;
boolean playRainbow = false;
boolean playFlicker = false;
boolean offMaster = false;
boolean dontTouch = false;


unsigned long currTime = 0;
unsigned long prevTime = 0;


void setup() {
  pinMode(47, INPUT_PULLUP);
  pinMode(48, INPUT_PULLUP);
  pinMode(49, INPUT_PULLUP);
  pinMode(50, INPUT_PULLUP);
  
  DmxSimple.usePin(46);
}

void loop() {

  if(dontTouch == false){ // chodzi o to aby nie brac pozycji podczas gdy pracuje flicker
    red = map(analogRead(A0), 1024, 0, 0, 255);
    green = map(analogRead(A1), 1024, 0, 0, 255);
    blue = map(analogRead(A2), 1024, 0, 0, 255);
    
  }
  if(offMaster == false){
    master = map(analogRead(A3), 1024, 0, 0, 255);
  }
  strobeSpeed = map(analogRead(A4), 1024, 0, 1, 50) * 10;
  effectSpeed = map(analogRead(A4), 1024, 0, 1, 100) * 100;
      
  if (digitalRead(47) == LOW){
    if(isStrobe == false){
      isStrobe = true;
      delay(200);
    }else{
      isStrobe = false;
      master = tmpMaster;
      offMaster = false;
      delay(200);
    }
  }
  if (digitalRead(48) == LOW){
    if(playRainbow == false){
      playRainbow = true;
      playFlicker = false;
      dontTouch = false;
      counter = 0;
      delay(200);
    }else{
      playRainbow = false;
      delay(200);
    }
  }
  if (digitalRead(49) == LOW){
    if(playFlicker == false){
      playFlicker = true;
      playRainbow = false;
      dontTouch = true;
      flicCount = 0;
      delay(200);
    }else{
      playFlicker = false;
      dontTouch = false;
      delay(200);
    }
  }
  while(digitalRead(50) == LOW){
    DmxSimple.write(1, 0);
    DmxSimple.write(2, 0);
    DmxSimple.write(3, 0);
    DmxSimple.write(4, 0);
  }
  
  
  
  if(isStrobe){
    currTime = millis();
    if(currTime - prevTime >= strobeSpeed){
      if(isActive){  // czy jest aktywny w tym momencie stroboskop, jezeli tak to do pomocniczych zapisujemy aktualne pozycje by potem je odtworzyc
        tmpMaster = master;
        master = 0;
        offMaster = true;
        isActive = false;
      }else{
        master = tmpMaster;
        isActive = true;
        offMaster = false;
      }
      prevTime = currTime;
    }
  }

  lightUp();
}


void color(String col){
  if(col == "red"){
    red = 255;
    green = 0;
    blue = 0;
  }else if(col == "green"){
    red = 0;
    green = 255;
    blue = 0;
  }else if(col == "blue"){
    red = 0;
    green = 0;
    blue = 255;
  }else if(col == "white"){
    red = 255;
    green = 255;
    blue = 255;
  }else if(col == "yellow"){
    red = 255;
    green = 255;
    blue = 0;
  }else if(col == "pink"){
    red = 255;
    green = 0;
    blue = 255;
  }else if(col == "cyan"){
    red = 0;
    green = 255;
    blue = 255;
  }
}

void lightUp(){

  //----rainboowwwwww
  if(playRainbow){
    counterColor = map(counter, 0, effectSpeed, 0, 359);
    setLedColorHSV(counterColor, 1, 1);
    if(counterColor >= 359){
      counter = 0;
    }else{
      counter++;
    }
  }

  //-----flickerr
  if(playFlicker){
    currTime = millis();
    if(currTime - prevTime >= strobeSpeed){
      
      switch(flicCount){
        case 0:
          color("red");
          break;
        case 1:
          color("white");
          break;
        case 2:
          color("green");
          break;
        case 3:
          color("white");
          break;
        case 4:
          color("blue");
          break;
        case 5:
          color("white");
          break;
        case 6:
          color("yellow");
          break;
        case 7:
          color("pink");
          break;
        case 8:
          color("cyan");
          break;
        case 9:
          color("white");
          break;
      }
      if(flicCount < 10){
        flicCount++;
      }else{
        flicCount = 0;
      }
      
      prevTime = currTime;
    }
  }

  DmxSimple.write(1, red);
  DmxSimple.write(2, green);
  DmxSimple.write(3, blue);
  DmxSimple.write(4, master);
}


void setLedColorHSV(int h, double s, double v) {
  //this is the algorithm to convert from RGB to HSV
  double r=0; 
  double g=0; 
  double b=0;

  double hf=h/60.0;

  int i=(int)floor(h/60.0);
  double f = h/60.0 - i;
  double pv = v * (1 - s);
  double qv = v * (1 - s*f);
  double tv = v * (1 - s * (1 - f));

  switch (i)
  {
  case 0: //rojo dominante
    r = v;
    g = tv;
    b = pv;
    break;
  case 1: //verde
    r = qv;
    g = v;
    b = pv;
    break;
  case 2: 
    r = pv;
    g = v;
    b = tv;
    break;
  case 3: //azul
    r = pv;
    g = qv;
    b = v;
    break;
  case 4:
    r = tv;
    g = pv;
    b = v;
    break;
  case 5: //rojo
    r = v;
    g = pv;
    b = qv;
    break;
  }

  //set each component to a integer value between 0 and 255
  red = constrain((int)255*r,0,255);
  green = constrain((int)255*g,0,255);
  blue = constrain((int)255*b,0,255);


  
}

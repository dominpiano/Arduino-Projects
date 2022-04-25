#include <DmxSimple.h>


int count = 0;
char mess[10];

long strobeSpeed, effectSpeed = 2500;
float counter, counterColor = 0;
int red, green, blue, master;
int tmpMaster;

boolean isStrobe = false;
boolean isActive = true;
boolean playRainbow = false;
boolean playFlicker = false;
boolean effectOn = false;

unsigned long currTime = 0;
unsigned long prevTime = 0;


void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop() {
  if (Serial1.available() > 0) {
    char C = Serial1.read();

     if(C == '.') 
     {
        mess[count] = C;
        String message(mess);
        message = message.substring(0,message.indexOf("."));
        count = 0;
        //Serial.println(message);        
        if (message.startsWith("R")) {
          red = message.substring(1,message.length()).toInt();
          //delay(10);
          if(effectOn){
            effectOn = false;
          }
        }
        else if (message.startsWith("G")){
          green = message.substring(1,message.length()).toInt();
          //delay(10);
          if(effectOn){
            effectOn = false;
          }
        }
        else if (message.startsWith("B")){
          blue = message.substring(1,message.length()).toInt();
          //delay(10);
          if(effectOn){
            effectOn = false;
          }
        }
        else if (message.startsWith("SS")){
          strobeSpeed = message.substring(2,message.length()).toInt() * 10;
          //delay(10);
        }
        else if (message.startsWith("ES")){
          effectSpeed = message.substring(2,message.length()).toInt() * 1000;
          //delay(10);
          counter = 0;
        }
        else if (message.startsWith("M")){
          master = message.substring(1,message.length()).toInt();
          //delay(10);
        }
        else if (message == "strobeOn"){
          isStrobe = true;
        }
        else if (message == "strobeOff"){
          isStrobe = false;
          master = tmpMaster;
        }
        else if (message == "rainbow"){
          effectOn = true;
          playRainbow = true;
          counter = 0;
        }
        else if (message == "flicker"){
          effectOn = true;
          playFlicker = true;
          counter = 0;
        }
        
     }
     else  mess[count++] = C;
  }

  if(effectOn == false){
    playRainbow = false;
    playFlicker = false;
  }
  
  if(isStrobe){
    currTime = millis();
    if(currTime - prevTime >= strobeSpeed){
      if(isActive){  // czy jest aktywny w tym momencie stroboskop, jezeli tak to do pomocniczych zapisujemy aktualne pozycje by potem je odtworzyc
        tmpMaster = master;
        master = 0;
        isActive = false;
      }else{
        master = tmpMaster;
        isActive = true;
      }
      prevTime = currTime;
    }
  }
  lightUp();
}

void lightUp(){

  //----check for effects
  if(effectOn){

    //----rainboowwwwww
    if(playRainbow){
      counterColor = map(counter, 0, effectSpeed, 0, 359);
      setLedColorHSV(counterColor, 1, 1);
      if(counterColor > 359){
        counter = 0;
      }else{
        counter++;
      }
    }

    //-----flickerr
    if(playFlicker){
      
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

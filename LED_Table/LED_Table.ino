#include <FastLED.h>
#include <IRremote.h>

int RECV_PIN = 4;
IRrecv irrecv(RECV_PIN);
decode_results results;

#define LED_PIN     24
#define NUM_LEDS    25
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];
//------------------------TicTac---------------
int pins[9] = {0,2,4,10,12,14,20,22,24};
int player1tab[5] = {33,33,33,33,33};
int player2tab[5] = {33,33,33,33,33};
int i = 0;
int j = 0;
int player1 = 1;
int player2 = 0;
int clicked = 0;

//------------------------LEDS---------------------
int led;
int brightness = 100;
String message;
int count = 0;
int activeR = 255;
int activeG = 0;
int activeB = 150;
int backR = 255;
int backG = 255;
int backB = 0;
int r = 255;
int g = 0;
int b = 0;


int isActive = 0;
int isBack = 0;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
  Serial.println("IR Enabled");
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
    Serial1.begin(9600);
    FastLED.addLeds<LED_TYPE,LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
    FastLED.setBrightness(brightness);
    for(int i = 0;i<10;i++){
      leds[i] = CRGB(0,0,0);
    }
    FastLED.show();
    for (int pinNo = 0 + 29; pinNo <= 24 + 29; pinNo++) {
      pinMode(pinNo, INPUT);
    }                                          
}


void loop() {
  
  if (irrecv.decode(&results)){
 
    switch (results.value){
      
      case 0xF740BF: // OFF
        brightness = 0;
        FastLED.setBrightness(brightness);
        FastLED.show();
        break;
    
      case 0xF7C03F: // ON
        brightness = 100;
        FastLED.setBrightness(brightness);
        FastLED.show();
        break;
        
      case 0xF700FF: // INCREASE BRIGHTNESS
        if(brightness < 100){
          brightness = brightness + 20;
        }
        FastLED.setBrightness(brightness);
        FastLED.show();
        break;

      case 0xF7807F: // DECREASE BRIGHTNESS
        if(brightness > 0){
          brightness = brightness - 20;
        }
        FastLED.setBrightness(brightness);
        FastLED.show();
        break;
      
      case 0xF7D02F: // ACTIVE
        isActive = 1;
        isBack = 0;
        //Serial.println("ACTIVE");
        break;

      case 0xF7F00F: // BACKGROUND
        isActive = 0;
        isBack = 1;
        //Serial.println("BACKGROUND");
        break;

      case 0xF7C837: // RAINBOW1
        Serial.println("tencza");
        playAnim1();
        break;

      case 0xF7E817: // RAINBOW2
        delay(200);
        playAnim3();
        break;

      case 0xF720DF: // RED
        if(isActive == 1){
          activeR = 255;
          activeG = 0;
          activeB = 0;
          isActive = 0;
        }
        if(isBack == 1){
          backR = 255;
          backG = 0;
          backB = 0;
          isBack = 0;
        }
        break;
        
      case 0xF7A05F: // GREEN
        if(isActive == 1){
          activeR = 0;
          activeG = 255;
          activeB = 0;
          isActive = 0;
        }
        if(isBack == 1){
          backR = 0;
          backG = 255;
          backB = 0;
          isBack = 0;
        }
        break;

      case 0xF7609F: // BLUE
        if(isActive == 1){
          activeR = 0;
          activeG = 0;
          activeB = 255;
          isActive = 0;
        }
        if(isBack == 1){
          backR = 0;
          backG = 0;
          backB = 255;
          isBack = 0;
        }
        break;

      case 0xF7E01F: // WHITE
        if(isActive == 1){
          activeR = 255;
          activeG = 255;
          activeB = 255;
          isActive = 0;
        }
        if(isBack == 1){
          backR = 255;
          backG = 255;
          backB = 255;
          isBack = 0;
        }
        break;
        
      case 0xF710EF: // ORANGE/RED
        if(isActive == 1){
          activeR = 255;
          activeG = 51;
          activeB = 0;
          isActive = 0;
        }
        if(isBack == 1){
          backR = 255;
          backG = 51;
          backB = 0;
          isBack = 0;
        }
        break;

      case 0xF730CF: // ORANGE
        if(isActive == 1){
          activeR = 255;
          activeG = 102;
          activeB = 0;
          isActive = 0;
        }
        if(isBack == 1){
          backR = 255;
          backG = 102;
          backB = 0;
          isBack = 0;
        }
        break;

      case 0xF708F7: // ORANGE/YELLOW
        if(isActive == 1){
          activeR = 255;
          activeG = 153;
          activeB = 0;
          isActive = 0;
        }
        if(isBack == 1){
          backR = 255;
          backG = 153;
          backB = 0;
          isBack = 0;
        }
        break;

      case 0xF728D7: // YELLOW
        if(isActive == 1){
          activeR = 255;
          activeG = 255;
          activeB = 0;
          isActive = 0;
        }
        if(isBack == 1){
          backR = 255;
          backG = 255;
          backB = 0;
          isBack = 0;
        }
        break;

      case 0xF7906F: // GREEN/BLUE
        if(isActive == 1){
          activeR = 0;
          activeG = 255;
          activeB = 80;
          isActive = 0;
        }
        if(isBack == 1){
          backR = 0;
          backG = 255;
          backB = 80;
          isBack = 0;
        }
        break;

      case 0xF7B04F: // SKYBLUE
        if(isActive == 1){
          activeR = 0;
          activeG = 255;
          activeB = 255;
          isActive = 0;
        }
        if(isBack == 1){
          backR = 0;
          backG = 255;
          backB = 255;
          isBack = 0;
        }
        break;

      case 0xF78877: // TURQUOISE
        if(isActive == 1){
          activeR = 0;
          activeG = 190;
          activeB = 210;
          isActive = 0;
        }
        if(isBack == 1){
          backR = 0;
          backG = 190;
          backB = 210;
          isBack = 0;
        }
        break;

      case 0xF7A857: // DEEP TURQUOISE
        if(isActive == 1){
          activeR = 0;
          activeG = 110;
          activeB = 110;
          isActive = 0;
        }
        if(isBack == 1){
          backR = 0;
          backG = 110;
          backB = 110;
          isBack = 0;
        }
        break;

      case 0xF750AF: // BLUE/PURPLE
        if(isActive == 1){
          activeR = 110;
          activeG = 0;
          activeB = 230;
          isActive = 0;
        }
        if(isBack == 1){
          backR = 110;
          backG = 0;
          backB = 230;
          isBack = 0;
        }
        break;

      case 0xF7708F: // BORDO
        if(isActive == 1){
          activeR = 180;
          activeG = 0;
          activeB = 60;
          isActive = 0;
        }
        if(isBack == 1){
          backR = 180;
          backG = 0;
          backB = 60;
          isBack = 0;
        }
        break;

      case 0xF748B7: // DARK PINK
        if(isActive == 1){
          activeR = 230;
          activeG = 0;
          activeB = 115;
          isActive = 0;
        }
        if(isBack == 1){
          backR = 230;
          backG = 0;
          backB = 115;
          isBack = 0;
        }
        break;

      case 0xF76897: // PINK
        if(isActive == 1){
          activeR = 255; 
          activeG = 102;
          activeB = 153;
          isActive = 0;
        }
        if(isBack == 1){
          backR = 255;
          backG = 102;
          backB = 153;
          isBack = 0;
        }
        break;
        
    }
    irrecv.resume();
  }
  delay(200);

  if (Serial1.available() > 0) {
    
        message = Serial1.readString();
        message = message.substring(0,message.indexOf("."));
        Serial.println(message);

      
        if (message.startsWith("1")) {
          delay(10);
          String stringR = message.substring(message.indexOf("R") + 1, message.indexOf("G"));
          activeR = stringR.toInt();
          String stringG = message.substring(message.indexOf("G") + 1, message.indexOf("B"));
          activeG = stringG.toInt();
          String stringB = message.substring(message.indexOf("B") + 1, message.indexOf("E"));
          activeB = stringB.toInt();
        }
        
        //------------------------------
        
        else if (message.startsWith("2")) {
          String stringR = message.substring(message.indexOf("R") + 1, message.indexOf("G"));
          backR = stringR.toInt();
          String stringG = message.substring(message.indexOf("G") + 1, message.indexOf("B"));
          backG = stringG.toInt();
          String stringB = message.substring(message.indexOf("B") + 1, message.indexOf("E"));
          backB = stringB.toInt();
        }
        
        //----------------------------------
        
        else if (message.startsWith("3")){
          String stringBrightness = message.substring(message.indexOf("3") + 1, message.length());
          brightness = stringBrightness.toInt();
          FastLED.setBrightness(brightness);
          FastLED.show();
        }
        
        //-----------------------------------
        
        else if (message.startsWith("4")){
          if(message.substring(message.indexOf("4")+1, message.length()) == "rainbow"){
            playAnim1();
          }
        }
        
        //----------------------------------
        
        else if (message.startsWith("5")){
          if(message.substring(message.indexOf("5")+1, message.length()) == "off"){
            Serial.println("off");
            for(int y = 0;y<=NUM_LEDS;y++){
              leds[y] = CRGB(0,0,0);
            }
            FastLED.show();
          }
          
        }
        
        //----------------------------------
        
        else if (message.startsWith("6")){
          if(message.substring(message.indexOf("6")+1, message.length()) == "anim1"){
             playAnim2();
          }
        }

        //----------------------------------

        else if (message.startsWith("7")){
          if(message.substring(message.indexOf("7")+1, message.length()) == "tictac"){
             playTicTac();
          }
        }


        //----------------------------------

        else if (message.startsWith("9")){
          if(message.substring(message.indexOf("9")+1, message.length()) == "anim3"){
             playAnim3();
          }
        }
        
        //----------------------------------
        
        else if (message.startsWith("8")){
          if(message.substring(message.indexOf("8")+1, message.length()) == "check"){
             for(int y = 0;y<=NUM_LEDS;y++){
              leds[y] = CRGB(200,200,200);
             }
             FastLED.show();
             delay(500);
             for(int y = 0;y<=NUM_LEDS;y++){
              leds[y] = CRGB(0,0,0);
             }
             FastLED.show();
             delay(500);
             for(int y = 0;y<=NUM_LEDS;y++){
              leds[y] = CRGB(200,200,200);
             }
          }
        }
      }
  
  for (int pinNo = 0; pinNo <= NUM_LEDS-1; pinNo++) {
    leds[pinNo] = CRGB( backR, backG, backB);
    if ( digitalRead(pinNo + 29) == LOW ) {
      leds[pinNo] = CRGB(activeR, activeG, activeB);
    }
  }
  FastLED.show();
  delay(10);
}


void playAnim1(){
  irrecv.resume();
  Serial.println(results.value, HEX);
  while(results.value != 0xF740BF){
    Serial.println("no i czemu to nie działa");
    for(int hue=0;hue<360;hue++)
    {
      setLedColorHSV(hue,1,1);
      delay(40);
      if(Serial1.available()){
        break;
      }
      /*if(digitalRead(5) == HIGH){
        break;
      }
      */
      if(irrecv.decode(&results)){
        if(results.value == 0xF740BF){
          break;
        }
      }
    }
    if(Serial1.available()){
      break;
    }
    if(digitalRead(5) == HIGH){
      break;
    }
  }
}

void setLedColorHSV(int h, double s, double v){
  
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

        int red=constrain((int)255*r,0,255);
        int green=constrain((int)255*g,0,255);
        int blue=constrain((int)255*b,0,255);

        for(int a = 0;a<=25;a++){
           leds[a] = CRGB(red,green,blue);
        }
        FastLED.show();
}

void playAnim2(){
    leds[0] = CRGB(255, 0, 0);
    leds[1] = CRGB(255, 0, 0);
    leds[2] = CRGB(255, 0, 0);
    leds[3] = CRGB(255, 0, 0);
    leds[4] = CRGB(255, 0, 0);
    leds[5] = CRGB(255, 0, 0);
    leds[6] = CRGB(255, 255, 0);
    leds[7] = CRGB(255, 255, 0);
    leds[8] = CRGB(255, 255, 0);
    leds[9] = CRGB(255, 0, 0);
    leds[10] = CRGB(255, 0, 0);
    leds[11] = CRGB(255, 255, 0);
    leds[12] = CRGB(255, 0, 255);
    leds[13] = CRGB(255, 255, 0);
    leds[14] = CRGB(255, 0, 0);
    leds[15] = CRGB(255, 0, 0);
    leds[16] = CRGB(255, 255, 0);
    leds[17] = CRGB(255, 255, 0);
    leds[18] = CRGB(255, 255, 0);
    leds[19] = CRGB(255, 0, 0);
    leds[20] = CRGB(255, 0, 0);
    leds[21] = CRGB(255, 0, 0);
    leds[22] = CRGB(255, 0, 0);
    leds[23] = CRGB(255, 0, 0);
    leds[24] = CRGB(255, 0, 0);
    FastLED.show();
    delay(250);
    leds[0] = CRGB(0, 255, 255);
    leds[1] = CRGB(0, 255, 255);
    leds[2] = CRGB(0, 255, 255);
    leds[3] = CRGB(0, 255, 255);
    leds[4] = CRGB(0, 255, 255);
    leds[5] = CRGB(0, 255, 255);
    leds[6] = CRGB(0, 255, 0);
    leds[7] = CRGB(0, 255, 0);
    leds[8] = CRGB(0, 255, 0);
    leds[9] = CRGB(0, 255, 255);
    leds[10] = CRGB(0, 255, 255);
    leds[11] = CRGB(0, 255, 0);
    leds[12] = CRGB(255, 0, 0);
    leds[13] = CRGB(0, 255, 0);
    leds[14] = CRGB(0, 255, 255);
    leds[15] = CRGB(0, 255, 255);
    leds[16] = CRGB(0, 255, 0);
    leds[17] = CRGB(0, 255, 0);
    leds[18] = CRGB(0, 255, 0);
    leds[19] = CRGB(0, 255, 255);
    leds[20] = CRGB(0, 255, 255);
    leds[21] = CRGB(0, 255, 255);
    leds[22] = CRGB(0, 255, 255);
    leds[23] = CRGB(0, 255, 255);
    leds[24] = CRGB(0, 255, 255);
    FastLED.show();
    delay(250);
    leds[0] = CRGB(255, 0, 0);
    leds[1] = CRGB(255, 0, 0);
    leds[2] = CRGB(255, 0, 0);
    leds[3] = CRGB(255, 0, 0);
    leds[4] = CRGB(255, 0, 0);
    leds[5] = CRGB(255, 0, 0);
    leds[6] = CRGB(255, 255, 0);
    leds[7] = CRGB(255, 255, 0);
    leds[8] = CRGB(255, 255, 0);
    leds[9] = CRGB(255, 0, 0);
    leds[10] = CRGB(255, 0, 0);
    leds[11] = CRGB(255, 255, 0);
    leds[12] = CRGB(255, 0, 255);
    leds[13] = CRGB(255, 255, 0);
    leds[14] = CRGB(255, 0, 0);
    leds[15] = CRGB(255, 0, 0);
    leds[16] = CRGB(255, 255, 0);
    leds[17] = CRGB(255, 255, 0);
    leds[18] = CRGB(255, 255, 0);
    leds[19] = CRGB(255, 0, 0);
    leds[20] = CRGB(255, 0, 0);
    leds[21] = CRGB(255, 0, 0);
    leds[22] = CRGB(255, 0, 0);
    leds[23] = CRGB(255, 0, 0);
    leds[24] = CRGB(255, 0, 0);
    FastLED.show();
    delay(250);
    leds[0] = CRGB(0, 255, 255);
    leds[1] = CRGB(0, 255, 255);
    leds[2] = CRGB(0, 255, 255);
    leds[3] = CRGB(0, 255, 255);
    leds[4] = CRGB(0, 255, 255);
    leds[5] = CRGB(0, 255, 255);
    leds[6] = CRGB(0, 255, 0);
    leds[7] = CRGB(0, 255, 0);
    leds[8] = CRGB(0, 255, 0);
    leds[9] = CRGB(0, 255, 255);
    leds[10] = CRGB(0, 255, 255);
    leds[11] = CRGB(0, 255, 0);
    leds[12] = CRGB(255, 0, 0);
    leds[13] = CRGB(0, 255, 0);
    leds[14] = CRGB(0, 255, 255);
    leds[15] = CRGB(0, 255, 255);
    leds[16] = CRGB(0, 255, 0);
    leds[17] = CRGB(0, 255, 0);
    leds[18] = CRGB(0, 255, 0);
    leds[19] = CRGB(0, 255, 255);
    leds[20] = CRGB(0, 255, 255);
    leds[21] = CRGB(0, 255, 255);
    leds[22] = CRGB(0, 255, 255);
    leds[23] = CRGB(0, 255, 255);
    leds[24] = CRGB(0, 255, 255);
    FastLED.show();
    delay(250);
    leds[0] = CRGB(153, 0, 154);
    leds[1] = CRGB(153, 0, 154);
    leds[2] = CRGB(153, 0, 154);
    leds[3] = CRGB(153, 0, 154);
    leds[4] = CRGB(153, 255, 154);
    leds[5] = CRGB(153, 0, 154);
    leds[6] = CRGB(0, 255, 255);
    leds[7] = CRGB(0, 255, 255);
    leds[8] = CRGB(0, 255, 255);
    leds[9] = CRGB(153, 0, 154);
    leds[10] = CRGB(153, 0, 154);
    leds[11] = CRGB(0, 255, 255);
    leds[12] = CRGB(0, 255, 0);
    leds[13] = CRGB(0, 255, 255);
    leds[14] = CRGB(153, 0, 154);
    leds[15] = CRGB(153, 0, 154);
    leds[16] = CRGB(0, 255, 255);
    leds[17] = CRGB(0, 255, 255);
    leds[18] = CRGB(0, 255, 255);
    leds[19] = CRGB(153, 0, 154);
    leds[20] = CRGB(153, 0, 154);
    leds[21] = CRGB(153, 0, 154);
    leds[22] = CRGB(153, 0, 154);
    leds[23] = CRGB(153, 0, 154);
    leds[24] = CRGB(153, 0, 154);
    FastLED.show();
    delay(250);
    leds[8] = CRGB(153, 255, 154);
    leds[12] = CRGB(153, 255, 154);
    FastLED.show();
    delay(250);
    leds[16] = CRGB(153, 255, 154);
    leds[20] = CRGB(153, 255, 154);
    FastLED.show();
    delay(250);
    leds[21] = CRGB(153, 255, 154);
    leds[22] = CRGB(153, 255, 154);
    FastLED.show();
    delay(250);
    leds[23] = CRGB(153, 255, 154);
    leds[24] = CRGB(153, 255, 154);
    FastLED.show();
    delay(250);
    leds[2] = CRGB(153, 255, 154);
    leds[3] = CRGB(153, 255, 154);
    FastLED.show();
    delay(250);
    leds[0] = CRGB(153, 255, 154);
    leds[1] = CRGB(153, 255, 154);
    FastLED.show();
    delay(250);
    leds[0] = CRGB(255, 28, 154);
    leds[1] = CRGB(255, 28, 154);
    leds[2] = CRGB(255, 28, 154);
    leds[3] = CRGB(255, 28, 154);
    leds[4] = CRGB(255, 28, 154);
    leds[5] = CRGB(255, 28, 154);
    leds[6] = CRGB(255, 28, 154);
    leds[7] = CRGB(255, 28, 154);
    leds[8] = CRGB(255, 28, 154);
    leds[9] = CRGB(255, 28, 154);
    leds[10] = CRGB(255, 28, 154);
    leds[11] = CRGB(255, 28, 154);
    leds[12] = CRGB(255, 28, 154);
    leds[13] = CRGB(255, 28, 154);
    leds[14] = CRGB(255, 28, 154);
    leds[15] = CRGB(255, 28, 154);
    leds[16] = CRGB(255, 28, 154);
    leds[17] = CRGB(255, 28, 154);
    leds[18] = CRGB(255, 28, 154);
    leds[19] = CRGB(255, 28, 154);
    leds[20] = CRGB(255, 28, 154);
    leds[21] = CRGB(255, 28, 154);
    leds[22] = CRGB(255, 28, 154);
    leds[23] = CRGB(255, 28, 154);
    leds[24] = CRGB(255, 28, 154);
    FastLED.show();
    delay(250);
    leds[0] = CRGB(49, 114, 255);
    leds[1] = CRGB(49, 114, 255);
    leds[2] = CRGB(49, 114, 255);
    leds[3] = CRGB(49, 114, 255);
    leds[4] = CRGB(255, 143, 105);
    leds[5] = CRGB(49, 114, 255);
    leds[6] = CRGB(49, 114, 255);
    leds[7] = CRGB(49, 114, 255);
    leds[8] = CRGB(49, 114, 255);
    leds[9] = CRGB(49, 114, 255);
    leds[10] = CRGB(49, 114, 255);
    leds[11] = CRGB(49, 114, 255);
    leds[12] = CRGB(49, 114, 255);
    leds[13] = CRGB(49, 114, 255);
    leds[14] = CRGB(49, 114, 255);
    leds[15] = CRGB(49, 114, 255);
    leds[16] = CRGB(49, 114, 255);
    leds[17] = CRGB(49, 114, 255);
    leds[18] = CRGB(49, 114, 255);
    leds[19] = CRGB(49, 114, 255);
    leds[20] = CRGB(49, 114, 255);
    leds[21] = CRGB(49, 114, 255);
    leds[22] = CRGB(49, 114, 255);
    leds[23] = CRGB(49, 114, 255);
    leds[24] = CRGB(49, 114, 255);
    FastLED.show();
    delay(250);
    leds[2] = CRGB(255, 143, 105);
    leds[3] = CRGB(255, 143, 105);
    FastLED.show();
    delay(250);
    leds[0] = CRGB(255, 143, 105);
    leds[1] = CRGB(255, 143, 105);
    FastLED.show();
    delay(250);
    leds[5] = CRGB(255, 143, 105);
    leds[10] = CRGB(255, 143, 105);
    FastLED.show();
    delay(250);
    leds[15] = CRGB(255, 143, 105);
    leds[20] = CRGB(255, 143, 105);
    FastLED.show();
    delay(250);
    leds[21] = CRGB(255, 143, 105);
    leds[22] = CRGB(255, 143, 105);
    FastLED.show();
    delay(250);
    leds[23] = CRGB(255, 143, 105);
    leds[24] = CRGB(255, 143, 105);
    FastLED.show();
    delay(250);
    leds[14] = CRGB(255, 143, 105);
    leds[19] = CRGB(255, 143, 105);
    FastLED.show();
    delay(250);
    leds[0] = CRGB(8, 143, 255);
    leds[1] = CRGB(8, 143, 255);
    leds[2] = CRGB(8, 143, 255);
    leds[3] = CRGB(8, 143, 255);
    leds[4] = CRGB(8, 143, 255);
    leds[5] = CRGB(8, 143, 255);
    leds[6] = CRGB(255, 142, 104);
    leds[7] = CRGB(255, 142, 104);
    leds[8] = CRGB(255, 142, 104);
    leds[9] = CRGB(8, 143, 255);
    leds[10] = CRGB(8, 143, 255);
    leds[11] = CRGB(255, 142, 104);
    leds[12] = CRGB(8, 143, 255);
    leds[13] = CRGB(255, 142, 104);
    leds[14] = CRGB(8, 143, 255);
    leds[15] = CRGB(8, 143, 255);
    leds[16] = CRGB(255, 142, 104);
    leds[17] = CRGB(255, 142, 104);
    leds[18] = CRGB(255, 142, 104);
    leds[19] = CRGB(8, 143, 255);
    leds[20] = CRGB(8, 143, 255);
    leds[21] = CRGB(8, 143, 255);
    leds[22] = CRGB(8, 143, 255);
    leds[23] = CRGB(8, 143, 255);
    leds[24] = CRGB(8, 143, 255);
    FastLED.show();
    delay(250);
    leds[0] = CRGB(9, 142, 255);
    leds[1] = CRGB(9, 142, 255);
    leds[2] = CRGB(9, 142, 255);
    leds[3] = CRGB(9, 142, 255);
    leds[4] = CRGB(9, 142, 255);
    leds[5] = CRGB(9, 142, 255);
    leds[6] = CRGB(9, 142, 255);
    leds[7] = CRGB(9, 142, 255);
    leds[8] = CRGB(9, 142, 255);
    leds[9] = CRGB(9, 142, 255);
    leds[10] = CRGB(9, 142, 255);
    leds[11] = CRGB(9, 142, 255);
    leds[12] = CRGB(9, 142, 255);
    leds[13] = CRGB(9, 142, 255);
    leds[14] = CRGB(9, 142, 255);
    leds[15] = CRGB(9, 142, 255);
    leds[16] = CRGB(9, 142, 255);
    leds[17] = CRGB(9, 142, 255);
    leds[18] = CRGB(9, 142, 255);
    leds[19] = CRGB(9, 142, 255);
    leds[20] = CRGB(9, 142, 255);
    leds[21] = CRGB(9, 142, 255);
    leds[22] = CRGB(9, 142, 255);
    leds[23] = CRGB(9, 142, 255);
    leds[24] = CRGB(9, 142, 255);
    FastLED.show();
    delay(250);
    leds[0] = CRGB(0, 0, 0);
    leds[1] = CRGB(0, 0, 0);
    leds[2] = CRGB(0, 0, 0);
    leds[3] = CRGB(0, 0, 0);
    leds[4] = CRGB(0, 0, 0);
    leds[5] = CRGB(0, 0, 0);
    leds[6] = CRGB(0, 0, 0);
    leds[7] = CRGB(0, 0, 0);
    leds[8] = CRGB(0, 0, 0);
    leds[9] = CRGB(0, 0, 0);
    leds[10] = CRGB(0, 0, 0);
    leds[11] = CRGB(0, 0, 0);
    leds[13] = CRGB(0, 0, 0);
    leds[14] = CRGB(0, 0, 0);
    leds[15] = CRGB(0, 0, 0);
    leds[16] = CRGB(0, 0, 0);
    leds[17] = CRGB(0, 0, 0);
    leds[18] = CRGB(0, 0, 0);
    leds[19] = CRGB(0, 0, 0);
    leds[20] = CRGB(0, 0, 0);
    leds[21] = CRGB(0, 0, 0);
    leds[22] = CRGB(0, 0, 0);
    leds[23] = CRGB(0, 0, 0);
    leds[24] = CRGB(0, 0, 0);
    FastLED.show();
    delay(250);
}

void playAnim3(){
  while(1==1){
  leds[0] = CRGB(255, 150, 0);
leds[1] = CRGB(255, 117, 0);
leds[2] = CRGB(255, 85, 0);
leds[3] = CRGB(255, 55, 0);
leds[4] = CRGB(255, 29, 0);
leds[5] = CRGB(255, 117, 0);
leds[6] = CRGB(255, 85, 0);
leds[7] = CRGB(255, 55, 0);
leds[8] = CRGB(255, 29, 0);
leds[9] = CRGB(255, 8, 0);
leds[10] = CRGB(255, 85, 0);
leds[11] = CRGB(255, 55, 0);
leds[12] = CRGB(255, 29, 0);
leds[13] = CRGB(255, 8, 0);
leds[14] = CRGB(255, 0, 0);
leds[15] = CRGB(255, 55, 0);
leds[16] = CRGB(255, 29, 0);
leds[17] = CRGB(255, 8, 0);
leds[18] = CRGB(255, 0, 0);
leds[19] = CRGB(255, 14, 14);
leds[20] = CRGB(255, 29, 0);
leds[21] = CRGB(255, 8, 0);
leds[22] = CRGB(255, 0, 0);
leds[23] = CRGB(255, 14, 14);
leds[24] = CRGB(255, 31, 31);
FastLED.show();
delay(100);  if(Serial1.available()){ break;} if(digitalRead(5) == HIGH){break;}
leds[0] = CRGB(255, 198, 0);
leds[1] = CRGB(255, 169, 0);
leds[2] = CRGB(255, 138, 0);
leds[3] = CRGB(255, 107, 0);
leds[4] = CRGB(255, 76, 0);
leds[5] = CRGB(255, 168, 0);
leds[6] = CRGB(255, 137, 0);
leds[7] = CRGB(255, 106, 0);
leds[8] = CRGB(255, 75, 0);
leds[9] = CRGB(255, 47, 0);
leds[10] = CRGB(255, 136, 0);
leds[11] = CRGB(255, 105, 0);
leds[12] = CRGB(255, 74, 0);
leds[13] = CRGB(255, 46, 0);
leds[14] = CRGB(255, 22, 0);
leds[15] = CRGB(255, 104, 0);
leds[16] = CRGB(255, 73, 0);
leds[17] = CRGB(255, 45, 0);
leds[18] = CRGB(255, 22, 0);
leds[19] = CRGB(255, 4, 0);
leds[20] = CRGB(255, 72, 0);
leds[21] = CRGB(255, 45, 0);
leds[22] = CRGB(255, 21, 0);
leds[23] = CRGB(255, 3, 0);
leds[24] = CRGB(255, 2, 2);
FastLED.show();
delay(100);  if(Serial1.available()){ break;} if(digitalRead(5) == HIGH){break;}
leds[0] = CRGB(255, 248, 0);
leds[1] = CRGB(255, 232, 0);
leds[2] = CRGB(255, 209, 0);
leds[3] = CRGB(255, 181, 0);
leds[4] = CRGB(255, 150, 0);
leds[5] = CRGB(255, 232, 0);
leds[6] = CRGB(255, 209, 0);
leds[7] = CRGB(255, 181, 0);
leds[8] = CRGB(255, 150, 0);
leds[9] = CRGB(255, 117, 0);
leds[10] = CRGB(255, 209, 0);
leds[11] = CRGB(255, 181, 0);
leds[12] = CRGB(255, 150, 0);
leds[13] = CRGB(255, 117, 0);
leds[14] = CRGB(255, 85, 0);
leds[15] = CRGB(255, 181, 0);
leds[16] = CRGB(255, 150, 0);
leds[17] = CRGB(255, 117, 0);
leds[18] = CRGB(255, 85, 0);
leds[19] = CRGB(255, 55, 0);
leds[20] = CRGB(255, 150, 0);
leds[21] = CRGB(255, 117, 0);
leds[22] = CRGB(255, 85, 0);
leds[23] = CRGB(255, 55, 0);
leds[24] = CRGB(255, 29, 0);
FastLED.show();
delay(100);  if(Serial1.available()){ break;} if(digitalRead(5) == HIGH){break;}
leds[0] = CRGB(227, 252, 4);
leds[1] = CRGB(246, 252, 2);
leds[2] = CRGB(255, 248, 0);
leds[3] = CRGB(255, 232, 0);
leds[4] = CRGB(255, 209, 0);
leds[5] = CRGB(246, 252, 2);
leds[6] = CRGB(255, 248, 0);
leds[7] = CRGB(255, 232, 0);
leds[8] = CRGB(255, 209, 0);
leds[9] = CRGB(255, 181, 0);
leds[10] = CRGB(255, 248, 0);
leds[11] = CRGB(255, 232, 0);
leds[12] = CRGB(255, 209, 0);
leds[13] = CRGB(255, 181, 0);
leds[14] = CRGB(255, 150, 0);
leds[15] = CRGB(255, 232, 0);
leds[16] = CRGB(255, 209, 0);
leds[17] = CRGB(255, 181, 0);
leds[18] = CRGB(255, 150, 0);
leds[19] = CRGB(255, 117, 0);
leds[20] = CRGB(255, 209, 0);
leds[21] = CRGB(255, 181, 0);
leds[22] = CRGB(255, 150, 0);
leds[23] = CRGB(255, 117, 0);
leds[24] = CRGB(255, 85, 0);
FastLED.show();
delay(100);  if(Serial1.available()){ break;} if(digitalRead(5) == HIGH){break;}
leds[0] = CRGB(176, 246, 10);
leds[1] = CRGB(203, 252, 7);
leds[2] = CRGB(227, 252, 4);
leds[3] = CRGB(246, 252, 2);
leds[4] = CRGB(255, 248, 0);
leds[5] = CRGB(203, 252, 7);
leds[6] = CRGB(227, 252, 4);
leds[7] = CRGB(246, 252, 2);
leds[8] = CRGB(255, 248, 0);
leds[9] = CRGB(255, 232, 0);
leds[10] = CRGB(227, 252, 4);
leds[11] = CRGB(246, 252, 2);
leds[12] = CRGB(255, 248, 0);
leds[13] = CRGB(255, 232, 0);
leds[14] = CRGB(255, 209, 0);
leds[15] = CRGB(246, 252, 2);
leds[16] = CRGB(255, 248, 0);
leds[17] = CRGB(255, 232, 0);
leds[18] = CRGB(255, 209, 0);
leds[19] = CRGB(255, 181, 0);
leds[20] = CRGB(255, 248, 0);
leds[21] = CRGB(255, 232, 0);
leds[22] = CRGB(255, 209, 0);
leds[23] = CRGB(255, 181, 0);
leds[24] = CRGB(255, 150, 0);
FastLED.show();
delay(100);  if(Serial1.available()){ break;} if(digitalRead(5) == HIGH){break;}
leds[0] = CRGB(117, 224, 18);
leds[1] = CRGB(147, 236, 14);
leds[2] = CRGB(176, 246, 10);
leds[3] = CRGB(203, 252, 7);
leds[4] = CRGB(227, 252, 4);
leds[5] = CRGB(147, 236, 14);
leds[6] = CRGB(176, 246, 10);
leds[7] = CRGB(203, 252, 7);
leds[8] = CRGB(227, 252, 4);
leds[9] = CRGB(246, 252, 2);
leds[10] = CRGB(176, 246, 10);
leds[11] = CRGB(203, 252, 7);
leds[12] = CRGB(227, 252, 4);
leds[13] = CRGB(246, 252, 2);
leds[14] = CRGB(255, 248, 0);
leds[15] = CRGB(203, 252, 7);
leds[16] = CRGB(227, 252, 4);
leds[17] = CRGB(246, 252, 2);
leds[18] = CRGB(255, 248, 0);
leds[19] = CRGB(255, 232, 0);
leds[20] = CRGB(227, 252, 4);
leds[21] = CRGB(246, 252, 2);
leds[22] = CRGB(255, 248, 0);
leds[23] = CRGB(255, 232, 0);
leds[24] = CRGB(255, 209, 0);
FastLED.show();
delay(100);  if(Serial1.available()){ break;} if(digitalRead(5) == HIGH){break;}
leds[0] = CRGB(59, 200, 30);
leds[1] = CRGB(87, 211, 23);
leds[2] = CRGB(117, 224, 18);
leds[3] = CRGB(147, 236, 14);
leds[4] = CRGB(176, 246, 10);
leds[5] = CRGB(87, 211, 23);
leds[6] = CRGB(117, 224, 18);
leds[7] = CRGB(147, 236, 14);
leds[8] = CRGB(176, 246, 10);
leds[9] = CRGB(203, 252, 7);
leds[10] = CRGB(117, 224, 18);
leds[11] = CRGB(147, 236, 14);
leds[12] = CRGB(176, 246, 10);
leds[13] = CRGB(203, 252, 7);
leds[14] = CRGB(227, 252, 4);
leds[15] = CRGB(147, 236, 14);
leds[16] = CRGB(176, 246, 10);
leds[17] = CRGB(203, 252, 7);
leds[18] = CRGB(227, 252, 4);
leds[19] = CRGB(246, 252, 2);
leds[20] = CRGB(176, 246, 10);
leds[21] = CRGB(203, 252, 7);
leds[22] = CRGB(227, 252, 4);
leds[23] = CRGB(246, 252, 2);
leds[24] = CRGB(255, 248, 0);
FastLED.show();
delay(100);  if(Serial1.available()){ break;} if(digitalRead(5) == HIGH){break;}
leds[0] = CRGB(0, 180, 59);
leds[1] = CRGB(14, 183, 47);
leds[2] = CRGB(34, 190, 38);
leds[3] = CRGB(59, 200, 30);
leds[4] = CRGB(87, 211, 23);
leds[5] = CRGB(14, 183, 47);
leds[6] = CRGB(34, 190, 38);
leds[7] = CRGB(59, 200, 30);
leds[8] = CRGB(87, 211, 23);
leds[9] = CRGB(117, 224, 18);
leds[10] = CRGB(34, 190, 38);
leds[11] = CRGB(59, 200, 30);
leds[12] = CRGB(87, 211, 23);
leds[13] = CRGB(117, 224, 18);
leds[14] = CRGB(147, 236, 14);
leds[15] = CRGB(59, 200, 30);
leds[16] = CRGB(87, 211, 23);
leds[17] = CRGB(117, 224, 18);
leds[18] = CRGB(147, 236, 14);
leds[19] = CRGB(176, 246, 10);
leds[20] = CRGB(87, 211, 23);
leds[21] = CRGB(117, 224, 18);
leds[22] = CRGB(147, 236, 14);
leds[23] = CRGB(176, 246, 10);
leds[24] = CRGB(203, 252, 7);
FastLED.show();
delay(100);  if(Serial1.available()){ break;} if(digitalRead(5) == HIGH){break;}
leds[0] = CRGB(0, 186, 90);
leds[1] = CRGB(0, 182, 73);
leds[2] = CRGB(0, 180, 59);
leds[3] = CRGB(14, 183, 47);
leds[4] = CRGB(34, 190, 38);
leds[5] = CRGB(0, 182, 73);
leds[6] = CRGB(0, 180, 59);
leds[7] = CRGB(14, 183, 47);
leds[8] = CRGB(34, 190, 38);
leds[9] = CRGB(59, 200, 30);
leds[10] = CRGB(0, 180, 59);
leds[11] = CRGB(14, 183, 47);
leds[12] = CRGB(34, 190, 38);
leds[13] = CRGB(59, 200, 30);
leds[14] = CRGB(87, 211, 23);
leds[15] = CRGB(14, 183, 47);
leds[16] = CRGB(34, 190, 38);
leds[17] = CRGB(59, 200, 30);
leds[18] = CRGB(87, 211, 23);
leds[19] = CRGB(117, 224, 18);
leds[20] = CRGB(34, 190, 38);
leds[21] = CRGB(59, 200, 30);
leds[22] = CRGB(87, 211, 23);
leds[23] = CRGB(117, 224, 18);
leds[24] = CRGB(147, 236, 14);
FastLED.show();
delay(100);  if(Serial1.available()){ break;} if(digitalRead(5) == HIGH){break;}
leds[0] = CRGB(0, 203, 133);
leds[1] = CRGB(0, 194, 111);
leds[2] = CRGB(0, 186, 90);
leds[3] = CRGB(0, 182, 73);
leds[4] = CRGB(0, 180, 59);
leds[5] = CRGB(0, 194, 111);
leds[6] = CRGB(0, 186, 90);
leds[7] = CRGB(0, 182, 73);
leds[8] = CRGB(0, 180, 59);
leds[9] = CRGB(14, 183, 47);
leds[10] = CRGB(0, 186, 90);
leds[11] = CRGB(0, 182, 73);
leds[12] = CRGB(0, 180, 59);
leds[13] = CRGB(14, 183, 47);
leds[14] = CRGB(34, 190, 38);
leds[15] = CRGB(0, 182, 73);
leds[16] = CRGB(0, 180, 59);
leds[17] = CRGB(14, 183, 47);
leds[18] = CRGB(34, 190, 38);
leds[19] = CRGB(59, 200, 30);
leds[20] = CRGB(0, 180, 59);
leds[21] = CRGB(14, 183, 47);
leds[22] = CRGB(34, 190, 38);
leds[23] = CRGB(59, 200, 30);
leds[24] = CRGB(87, 211, 23);
FastLED.show();
delay(100);  if(Serial1.available()){ break;} if(digitalRead(5) == HIGH){break;}
leds[0] = CRGB(0, 224, 184);
leds[1] = CRGB(0, 212, 156);
leds[2] = CRGB(0, 203, 133);
leds[3] = CRGB(0, 194, 111);
leds[4] = CRGB(0, 186, 90);
leds[5] = CRGB(0, 212, 156);
leds[6] = CRGB(0, 203, 133);
leds[7] = CRGB(0, 194, 111);
leds[8] = CRGB(0, 186, 90);
leds[9] = CRGB(0, 182, 73);
leds[10] = CRGB(0, 203, 133);
leds[11] = CRGB(0, 194, 111);
leds[12] = CRGB(0, 186, 90);
leds[13] = CRGB(0, 182, 73);
leds[14] = CRGB(0, 180, 59);
leds[15] = CRGB(0, 194, 111);
leds[16] = CRGB(0, 186, 90);
leds[17] = CRGB(0, 182, 73);
leds[18] = CRGB(0, 180, 59);
leds[19] = CRGB(14, 183, 47);
leds[20] = CRGB(0, 186, 90);
leds[21] = CRGB(0, 182, 73);
leds[22] = CRGB(0, 180, 59);
leds[23] = CRGB(14, 183, 47);
leds[24] = CRGB(34, 190, 38);
FastLED.show();
delay(100);  if(Serial1.available()){ break;} if(digitalRead(5) == HIGH){break;}
leds[0] = CRGB(0, 234, 239);
leds[1] = CRGB(0, 234, 215);
leds[2] = CRGB(0, 224, 184);
leds[3] = CRGB(0, 212, 156);
leds[4] = CRGB(0, 203, 133);
leds[5] = CRGB(0, 234, 215);
leds[6] = CRGB(0, 224, 184);
leds[7] = CRGB(0, 212, 156);
leds[8] = CRGB(0, 203, 133);
leds[9] = CRGB(0, 194, 111);
leds[10] = CRGB(0, 224, 184);
leds[11] = CRGB(0, 212, 156);
leds[12] = CRGB(0, 203, 133);
leds[13] = CRGB(0, 194, 111);
leds[14] = CRGB(0, 186, 90);
leds[15] = CRGB(0, 212, 156);
leds[16] = CRGB(0, 203, 133);
leds[17] = CRGB(0, 194, 111);
leds[18] = CRGB(0, 186, 90);
leds[19] = CRGB(0, 182, 73);
leds[20] = CRGB(0, 203, 133);
leds[21] = CRGB(0, 194, 111);
leds[22] = CRGB(0, 186, 90);
leds[23] = CRGB(0, 182, 73);
leds[24] = CRGB(0, 180, 59);
FastLED.show();
delay(100);  if(Serial1.available()){ break;} if(digitalRead(5) == HIGH){break;}
leds[0] = CRGB(0, 218, 255);
leds[1] = CRGB(0, 234, 253);
leds[2] = CRGB(0, 234, 239);
leds[3] = CRGB(0, 234, 215);
leds[4] = CRGB(0, 224, 184);
leds[5] = CRGB(0, 234, 253);
leds[6] = CRGB(0, 234, 239);
leds[7] = CRGB(0, 234, 215);
leds[8] = CRGB(0, 224, 184);
leds[9] = CRGB(0, 212, 156);
leds[10] = CRGB(0, 234, 239);
leds[11] = CRGB(0, 234, 215);
leds[12] = CRGB(0, 224, 184);
leds[13] = CRGB(0, 212, 156);
leds[14] = CRGB(0, 203, 133);
leds[15] = CRGB(0, 234, 215);
leds[16] = CRGB(0, 224, 184);
leds[17] = CRGB(0, 212, 156);
leds[18] = CRGB(0, 203, 133);
leds[19] = CRGB(0, 194, 111);
leds[20] = CRGB(0, 224, 184);
leds[21] = CRGB(0, 212, 156);
leds[22] = CRGB(0, 203, 133);
leds[23] = CRGB(0, 194, 111);
leds[24] = CRGB(0, 186, 90);
FastLED.show();
delay(100);  if(Serial1.available()){ break;} if(digitalRead(5) == HIGH){break;}
leds[0] = CRGB(0, 143, 220);
leds[1] = CRGB(0, 184, 242);
leds[2] = CRGB(0, 218, 255);
leds[3] = CRGB(0, 234, 253);
leds[4] = CRGB(0, 234, 239);
leds[5] = CRGB(0, 184, 242);
leds[6] = CRGB(0, 218, 255);
leds[7] = CRGB(0, 234, 253);
leds[8] = CRGB(0, 234, 239);
leds[9] = CRGB(0, 234, 215);
leds[10] = CRGB(0, 218, 255);
leds[11] = CRGB(0, 234, 253);
leds[12] = CRGB(0, 234, 239);
leds[13] = CRGB(0, 234, 215);
leds[14] = CRGB(0, 224, 184);
leds[15] = CRGB(0, 234, 253);
leds[16] = CRGB(0, 234, 239);
leds[17] = CRGB(0, 234, 215);
leds[18] = CRGB(0, 224, 184);
leds[19] = CRGB(0, 212, 156);
leds[20] = CRGB(0, 234, 239);
leds[21] = CRGB(0, 234, 215);
leds[22] = CRGB(0, 224, 184);
leds[23] = CRGB(0, 212, 156);
leds[24] = CRGB(0, 203, 133);
FastLED.show();
delay(100);  if(Serial1.available()){ break;} if(digitalRead(5) == HIGH){break;}
leds[0] = CRGB(0, 85, 187);
leds[1] = CRGB(0, 109, 201);
leds[2] = CRGB(0, 143, 220);
leds[3] = CRGB(0, 184, 242);
leds[4] = CRGB(0, 218, 255);
leds[5] = CRGB(0, 109, 201);
leds[6] = CRGB(0, 143, 220);
leds[7] = CRGB(0, 184, 242);
leds[8] = CRGB(0, 218, 255);
leds[9] = CRGB(0, 234, 253);
leds[10] = CRGB(0, 143, 220);
leds[11] = CRGB(0, 184, 242);
leds[12] = CRGB(0, 218, 255);
leds[13] = CRGB(0, 234, 253);
leds[14] = CRGB(0, 234, 239);
leds[15] = CRGB(0, 184, 242);
leds[16] = CRGB(0, 218, 255);
leds[17] = CRGB(0, 234, 253);
leds[18] = CRGB(0, 234, 239);
leds[19] = CRGB(0, 234, 215);
leds[20] = CRGB(0, 218, 255);
leds[21] = CRGB(0, 234, 253);
leds[22] = CRGB(0, 234, 239);
leds[23] = CRGB(0, 234, 215);
leds[24] = CRGB(0, 224, 184);
FastLED.show();
delay(100);  if(Serial1.available()){ break;} if(digitalRead(5) == HIGH){break;}
leds[0] = CRGB(0, 53, 168);
leds[1] = CRGB(0, 75, 181);
leds[2] = CRGB(0, 98, 194);
leds[3] = CRGB(0, 123, 209);
leds[4] = CRGB(0, 167, 233);
leds[5] = CRGB(0, 74, 180);
leds[6] = CRGB(0, 98, 194);
leds[7] = CRGB(0, 122, 208);
leds[8] = CRGB(0, 166, 233);
leds[9] = CRGB(0, 203, 250);
leds[10] = CRGB(0, 97, 194);
leds[11] = CRGB(0, 121, 208);
leds[12] = CRGB(0, 164, 232);
leds[13] = CRGB(0, 202, 250);
leds[14] = CRGB(0, 229, 255);
leds[15] = CRGB(0, 120, 207);
leds[16] = CRGB(0, 163, 231);
leds[17] = CRGB(0, 201, 250);
leds[18] = CRGB(0, 228, 255);
leds[19] = CRGB(0, 234, 248);
leds[20] = CRGB(0, 162, 231);
leds[21] = CRGB(0, 200, 249);
leds[22] = CRGB(0, 228, 255);
leds[23] = CRGB(0, 234, 249);
leds[24] = CRGB(0, 234, 230);
FastLED.show();
delay(100);  if(Serial1.available()){ break;} if(digitalRead(5) == HIGH){break;}
leds[0] = CRGB(0, 23, 152);
leds[1] = CRGB(0, 41, 161);
leds[2] = CRGB(0, 62, 173);
leds[3] = CRGB(0, 85, 187);
leds[4] = CRGB(0, 109, 201);
leds[5] = CRGB(0, 41, 161);
leds[6] = CRGB(0, 62, 173);
leds[7] = CRGB(0, 85, 187);
leds[8] = CRGB(0, 109, 201);
leds[9] = CRGB(0, 143, 220);
leds[10] = CRGB(0, 62, 173);
leds[11] = CRGB(0, 85, 187);
leds[12] = CRGB(0, 109, 201);
leds[13] = CRGB(0, 143, 220);
leds[14] = CRGB(0, 184, 242);
leds[15] = CRGB(0, 85, 187);
leds[16] = CRGB(0, 109, 201);
leds[17] = CRGB(0, 143, 220);
leds[18] = CRGB(0, 184, 242);
leds[19] = CRGB(0, 218, 255);
leds[20] = CRGB(0, 109, 201);
leds[21] = CRGB(0, 143, 220);
leds[22] = CRGB(0, 184, 242);
leds[23] = CRGB(0, 218, 255);
leds[24] = CRGB(0, 234, 253);
FastLED.show();
delay(100);  if(Serial1.available()){ break;} if(digitalRead(5) == HIGH){break;}
leds[0] = CRGB(8, 0, 144);
leds[1] = CRGB(0, 9, 146);
leds[2] = CRGB(0, 23, 152);
leds[3] = CRGB(0, 41, 161);
leds[4] = CRGB(0, 62, 173);
leds[5] = CRGB(0, 9, 146);
leds[6] = CRGB(0, 23, 152);
leds[7] = CRGB(0, 41, 161);
leds[8] = CRGB(0, 62, 173);
leds[9] = CRGB(0, 85, 187);
leds[10] = CRGB(0, 23, 152);
leds[11] = CRGB(0, 41, 161);
leds[12] = CRGB(0, 62, 173);
leds[13] = CRGB(0, 85, 187);
leds[14] = CRGB(0, 109, 201);
leds[15] = CRGB(0, 41, 161);
leds[16] = CRGB(0, 62, 173);
leds[17] = CRGB(0, 85, 187);
leds[18] = CRGB(0, 109, 201);
leds[19] = CRGB(0, 143, 220);
leds[20] = CRGB(0, 62, 173);
leds[21] = CRGB(0, 85, 187);
leds[22] = CRGB(0, 109, 201);
leds[23] = CRGB(0, 143, 220);
leds[24] = CRGB(0, 184, 242);
FastLED.show();
delay(100);  if(Serial1.available()){ break;} if(digitalRead(5) == HIGH){break;}
leds[0] = CRGB(54, 0, 148);
leds[1] = CRGB(28, 0, 144);
leds[2] = CRGB(8, 0, 144);
leds[3] = CRGB(0, 9, 146);
leds[4] = CRGB(0, 23, 152);
leds[5] = CRGB(28, 0, 144);
leds[6] = CRGB(8, 0, 144);
leds[7] = CRGB(0, 9, 146);
leds[8] = CRGB(0, 23, 152);
leds[9] = CRGB(0, 41, 161);
leds[10] = CRGB(8, 0, 144);
leds[11] = CRGB(0, 9, 146);
leds[12] = CRGB(0, 23, 152);
leds[13] = CRGB(0, 41, 161);
leds[14] = CRGB(0, 62, 173);
leds[15] = CRGB(0, 9, 146);
leds[16] = CRGB(0, 23, 152);
leds[17] = CRGB(0, 41, 161);
leds[18] = CRGB(0, 62, 173);
leds[19] = CRGB(0, 85, 187);
leds[20] = CRGB(0, 23, 152);
leds[21] = CRGB(0, 41, 161);
leds[22] = CRGB(0, 62, 173);
leds[23] = CRGB(0, 85, 187);
leds[24] = CRGB(0, 109, 201);
FastLED.show();
delay(100);  if(Serial1.available()){ break;} if(digitalRead(5) == HIGH){break;}
leds[0] = CRGB(117, 0, 161);
leds[1] = CRGB(84, 0, 154);
leds[2] = CRGB(54, 0, 148);
leds[3] = CRGB(28, 0, 144);
leds[4] = CRGB(8, 0, 144);
leds[5] = CRGB(84, 0, 154);
leds[6] = CRGB(54, 0, 148);
leds[7] = CRGB(28, 0, 144);
leds[8] = CRGB(8, 0, 144);
leds[9] = CRGB(0, 9, 146);
leds[10] = CRGB(54, 0, 148);
leds[11] = CRGB(28, 0, 144);
leds[12] = CRGB(8, 0, 144);
leds[13] = CRGB(0, 9, 146);
leds[14] = CRGB(0, 23, 152);
leds[15] = CRGB(28, 0, 144);
leds[16] = CRGB(8, 0, 144);
leds[17] = CRGB(0, 9, 146);
leds[18] = CRGB(0, 23, 152);
leds[19] = CRGB(0, 41, 161);
leds[20] = CRGB(8, 0, 144);
leds[21] = CRGB(0, 9, 146);
leds[22] = CRGB(0, 23, 152);
leds[23] = CRGB(0, 41, 161);
leds[24] = CRGB(0, 62, 173);
FastLED.show();
delay(100);  if(Serial1.available()){ break;} if(digitalRead(5) == HIGH){break;}
leds[0] = CRGB(205, 0, 185);
leds[1] = CRGB(160, 0, 173);
leds[2] = CRGB(117, 0, 161);
leds[3] = CRGB(84, 0, 154);
leds[4] = CRGB(54, 0, 148);
leds[5] = CRGB(160, 0, 173);
leds[6] = CRGB(117, 0, 161);
leds[7] = CRGB(84, 0, 154);
leds[8] = CRGB(54, 0, 148);
leds[9] = CRGB(28, 0, 144);
leds[10] = CRGB(117, 0, 161);
leds[11] = CRGB(84, 0, 154);
leds[12] = CRGB(54, 0, 148);
leds[13] = CRGB(28, 0, 144);
leds[14] = CRGB(8, 0, 144);
leds[15] = CRGB(84, 0, 154);
leds[16] = CRGB(54, 0, 148);
leds[17] = CRGB(28, 0, 144);
leds[18] = CRGB(8, 0, 144);
leds[19] = CRGB(0, 9, 146);
leds[20] = CRGB(54, 0, 148);
leds[21] = CRGB(28, 0, 144);
leds[22] = CRGB(8, 0, 144);
leds[23] = CRGB(0, 9, 146);
leds[24] = CRGB(0, 23, 152);
FastLED.show();
delay(100);  if(Serial1.available()){ break;} if(digitalRead(5) == HIGH){break;}
leds[0] = CRGB(248, 0, 196);
leds[1] = CRGB(216, 0, 188);
leds[2] = CRGB(172, 0, 176);
leds[3] = CRGB(125, 0, 163);
leds[4] = CRGB(92, 0, 156);
leds[5] = CRGB(217, 0, 188);
leds[6] = CRGB(174, 0, 176);
leds[7] = CRGB(126, 0, 164);
leds[8] = CRGB(93, 0, 156);
leds[9] = CRGB(62, 0, 149);
leds[10] = CRGB(175, 0, 177);
leds[11] = CRGB(127, 0, 164);
leds[12] = CRGB(94, 0, 156);
leds[13] = CRGB(63, 0, 149);
leds[14] = CRGB(36, 0, 145);
leds[15] = CRGB(128, 0, 164);
leds[16] = CRGB(95, 0, 156);
leds[17] = CRGB(64, 0, 149);
leds[18] = CRGB(37, 0, 145);
leds[19] = CRGB(14, 0, 144);
leds[20] = CRGB(96, 0, 156);
leds[21] = CRGB(65, 0, 150);
leds[22] = CRGB(37, 0, 145);
leds[23] = CRGB(15, 0, 144);
leds[24] = CRGB(0, 5, 144);
FastLED.show();
delay(100);  if(Serial1.available()){ break;} if(digitalRead(5) == HIGH){break;}
leds[0] = CRGB(255, 24, 203);
leds[1] = CRGB(255, 13, 201);
leds[2] = CRGB(247, 0, 196);
leds[3] = CRGB(215, 0, 188);
leds[4] = CRGB(171, 0, 176);
leds[5] = CRGB(255, 13, 201);
leds[6] = CRGB(248, 0, 196);
leds[7] = CRGB(216, 0, 188);
leds[8] = CRGB(172, 0, 176);
leds[9] = CRGB(125, 0, 163);
leds[10] = CRGB(249, 0, 197);
leds[11] = CRGB(217, 0, 188);
leds[12] = CRGB(174, 0, 176);
leds[13] = CRGB(126, 0, 164);
leds[14] = CRGB(93, 0, 156);
leds[15] = CRGB(218, 0, 189);
leds[16] = CRGB(175, 0, 177);
leds[17] = CRGB(127, 0, 164);
leds[18] = CRGB(94, 0, 156);
leds[19] = CRGB(63, 0, 149);
leds[20] = CRGB(177, 0, 177);
leds[21] = CRGB(128, 0, 164);
leds[22] = CRGB(95, 0, 156);
leds[23] = CRGB(64, 0, 149);
leds[24] = CRGB(37, 0, 145);
FastLED.show();
delay(100);  if(Serial1.available()){ break;} if(digitalRead(5) == HIGH){break;}
leds[0] = CRGB(255, 0, 112);
leds[1] = CRGB(255, 0, 144);
leds[2] = CRGB(255, 0, 172);
leds[3] = CRGB(255, 0, 192);
leds[4] = CRGB(241, 0, 198);
leds[5] = CRGB(255, 0, 144);
leds[6] = CRGB(255, 0, 172);
leds[7] = CRGB(255, 0, 192);
leds[8] = CRGB(241, 0, 198);
leds[9] = CRGB(205, 0, 198);
leds[10] = CRGB(255, 0, 172);
leds[11] = CRGB(255, 0, 192);
leds[12] = CRGB(241, 0, 198);
leds[13] = CRGB(205, 0, 198);
leds[14] = CRGB(160, 0, 187);
leds[15] = CRGB(255, 0, 192);
leds[16] = CRGB(241, 0, 198);
leds[17] = CRGB(205, 0, 198);
leds[18] = CRGB(160, 0, 187);
leds[19] = CRGB(117, 0, 173);
leds[20] = CRGB(241, 0, 198);
leds[21] = CRGB(205, 0, 198);
leds[22] = CRGB(160, 0, 187);
leds[23] = CRGB(117, 0, 173);
leds[24] = CRGB(84, 0, 162);
FastLED.show();
delay(100);  if(Serial1.available()){ break;} if(digitalRead(5) == HIGH){break;}
leds[0] = CRGB(255, 0, 75);
leds[1] = CRGB(255, 0, 108);
leds[2] = CRGB(255, 0, 140);
leds[3] = CRGB(255, 0, 168);
leds[4] = CRGB(255, 0, 189);
leds[5] = CRGB(255, 0, 109);
leds[6] = CRGB(255, 0, 141);
leds[7] = CRGB(255, 0, 168);
leds[8] = CRGB(255, 0, 189);
leds[9] = CRGB(247, 0, 198);
leds[10] = CRGB(255, 0, 141);
leds[11] = CRGB(255, 0, 169);
leds[12] = CRGB(255, 0, 190);
leds[13] = CRGB(247, 0, 198);
leds[14] = CRGB(215, 0, 198);
leds[15] = CRGB(255, 0, 170);
leds[16] = CRGB(255, 0, 190);
leds[17] = CRGB(246, 0, 198);
leds[18] = CRGB(213, 0, 198);
leds[19] = CRGB(171, 0, 190);
leds[20] = CRGB(255, 0, 191);
leds[21] = CRGB(245, 0, 198);
leds[22] = CRGB(212, 0, 198);
leds[23] = CRGB(170, 0, 190);
leds[24] = CRGB(124, 0, 175);
FastLED.show();
delay(100);  if(Serial1.available()){ break;} if(digitalRead(5) == HIGH){break;}
leds[0] = CRGB(255, 0, 17);
leds[1] = CRGB(255, 0, 43);
leds[2] = CRGB(255, 0, 74);
leds[3] = CRGB(255, 0, 107);
leds[4] = CRGB(255, 0, 139);
leds[5] = CRGB(255, 0, 44);
leds[6] = CRGB(255, 0, 75);
leds[7] = CRGB(255, 0, 108);
leds[8] = CRGB(255, 0, 140);
leds[9] = CRGB(255, 0, 168);
leds[10] = CRGB(255, 0, 76);
leds[11] = CRGB(255, 0, 109);
leds[12] = CRGB(255, 0, 141);
leds[13] = CRGB(255, 0, 168);
leds[14] = CRGB(255, 0, 189);
leds[15] = CRGB(255, 0, 110);
leds[16] = CRGB(255, 0, 141);
leds[17] = CRGB(255, 0, 169);
leds[18] = CRGB(255, 0, 190);
leds[19] = CRGB(247, 0, 198);
leds[20] = CRGB(255, 0, 142);
leds[21] = CRGB(255, 0, 170);
leds[22] = CRGB(255, 0, 190);
leds[23] = CRGB(246, 0, 198);
leds[24] = CRGB(213, 0, 198);
FastLED.show();
delay(100);  if(Serial1.available()){ break;} if(digitalRead(5) == HIGH){break;}
leds[0] = CRGB(255, 0, 0);
leds[1] = CRGB(255, 0, 0);
leds[2] = CRGB(255, 0, 16);
leds[3] = CRGB(255, 0, 42);
leds[4] = CRGB(255, 0, 73);
leds[5] = CRGB(255, 0, 0);
leds[6] = CRGB(255, 0, 17);
leds[7] = CRGB(255, 0, 43);
leds[8] = CRGB(255, 0, 74);
leds[9] = CRGB(255, 0, 107);
leds[10] = CRGB(255, 0, 18);
leds[11] = CRGB(255, 0, 44);
leds[12] = CRGB(255, 0, 75);
leds[13] = CRGB(255, 0, 108);
leds[14] = CRGB(255, 0, 140);
leds[15] = CRGB(255, 0, 45);
leds[16] = CRGB(255, 0, 76);
leds[17] = CRGB(255, 0, 109);
leds[18] = CRGB(255, 0, 141);
leds[19] = CRGB(255, 0, 168);
leds[20] = CRGB(255, 0, 77);
leds[21] = CRGB(255, 0, 110);
leds[22] = CRGB(255, 0, 141);
leds[23] = CRGB(255, 0, 169);
leds[24] = CRGB(255, 0, 190);
FastLED.show();
delay(100);  if(Serial1.available()){ break;} if(digitalRead(5) == HIGH){break;}
leds[2] = CRGB(255, 0, 0);
leds[3] = CRGB(255, 0, 0);
leds[4] = CRGB(255, 0, 16);
leds[6] = CRGB(255, 0, 0);
leds[7] = CRGB(255, 0, 0);
leds[8] = CRGB(255, 0, 16);
leds[9] = CRGB(255, 0, 42);
leds[10] = CRGB(255, 0, 0);
leds[11] = CRGB(255, 0, 0);
leds[12] = CRGB(255, 0, 17);
leds[13] = CRGB(255, 0, 43);
leds[14] = CRGB(255, 0, 74);
leds[15] = CRGB(255, 0, 0);
leds[16] = CRGB(255, 0, 18);
leds[17] = CRGB(255, 0, 44);
leds[18] = CRGB(255, 0, 75);
leds[19] = CRGB(255, 0, 108);
leds[20] = CRGB(255, 0, 19);
leds[21] = CRGB(255, 0, 45);
leds[22] = CRGB(255, 0, 76);
leds[23] = CRGB(255, 0, 109);
leds[24] = CRGB(255, 0, 141);
FastLED.show();
delay(100);  if(Serial1.available()){ break;} if(digitalRead(5) == HIGH){break;}
  }
  return;
}

void playTicTac(){
  makePool();
  
  //----------------------player 1-----round1--------
  while(player1 == 1){
    while(clicked == 0){
      if(Serial1.available()){
        delay(50);
        loop();
        return;
      }
      Serial.println("now");
      for (int pinNo = 0; pinNo <= NUM_LEDS-1; pinNo++) {
        if (digitalRead(pinNo + 29) == LOW) {
          int player1pin1 = pinNo;
          for(int x = 0;x<=8;x++){
            if(player1pin1 == pins[x]){
              leds[player1pin1] = CRGB(255,0,0);
              FastLED.show();
              clicked = 1;
              player1 = 0;
              player2 = 1;
              subtract(player1pin1, "playerFir");
            }
          }
        }
      }
    }
  }
  //---------------------player 2-------round1------
  delay(1000);
  clicked = 0;
  while(player2 == 1){
    while(clicked == 0){
      if(Serial1.available()){
       return;
      }
      for (int pinNo = 0; pinNo <= NUM_LEDS-1; pinNo++) {
        if ( digitalRead(pinNo + 29) == LOW){
          int player2pin1 = pinNo;
          for(int x = 0;x<=8;x++){
            if(player2pin1 == pins[x]){
              leds[player2pin1] = CRGB(0,0,255);
              FastLED.show();
              clicked = 1;
              player1 = 1;
              player2 = 0;
              subtract(player2pin1, "playerSec");
            }
          }
        }
      }
    }
  }
  //--------------------player 1------round2------
  delay(1000);
  clicked = 0;
  while(player1 == 1){
    while(clicked == 0){
      for (int pinNo = 0; pinNo <= NUM_LEDS-1; pinNo++) {
        if (digitalRead(pinNo + 29) == LOW) {
          int player1pin2 = pinNo;
          for(int x = 0;x<=8;x++){
            if(player1pin2 == pins[x]){
              leds[player1pin2] = CRGB(255,0,0);
              FastLED.show();
              clicked = 1;
              player1 = 0;
              player2 = 1;
              subtract(player1pin2, "playerFir");
            }
          }
        }
      }
    }
  }
  //---------------------player 2---------round2-------
  delay(1000);
  clicked = 0;
  while(player2 == 1){
    while(clicked == 0){
      for (int pinNo = 0; pinNo <= NUM_LEDS-1; pinNo++) {
        if ( digitalRead(pinNo + 29) == LOW){
          int player2pin2 = pinNo;
          for(int x = 0;x<=8;x++){
            if(player2pin2 == pins[x]){
              leds[player2pin2] = CRGB(0,0,255);
              FastLED.show();
              clicked = 1;
              player1 = 1;
              player2 = 0;
              subtract(player2pin2, "playerSec");
            }
          }
        }
      }
    }
  }
  //---------------------player 1------------round3------
  delay(1000);
  clicked = 0;
  while(player1 == 1){
    while(clicked == 0){
      for (int pinNo = 0; pinNo <= NUM_LEDS-1; pinNo++) {
        if (digitalRead(pinNo + 29) == LOW) {
          int player1pin3 = pinNo;
          for(int x = 0;x<=8;x++){
            if(player1pin3 == pins[x]){
              leds[player1pin3] = CRGB(255,0,0);
              FastLED.show();
              clicked = 1;
              player1 = 0;
              player2 = 1;
              subtract(player1pin3, "playerFir");
            }
          }
        }
      }
    }
  }
  checkwin();
  //---------------------player 2--------round3--------
  delay(1000);
  clicked = 0;
  while(player2 == 1){
    while(clicked == 0){
      for (int pinNo = 0; pinNo <= NUM_LEDS-1; pinNo++) {
        if ( digitalRead(pinNo + 29) == LOW){
          int player2pin3 = pinNo;
          for(int x = 0;x<=8;x++){
            if(player2pin3 == pins[x]){
              leds[player2pin3] = CRGB(0,0,255);
              FastLED.show();
              clicked = 1;
              player1 = 1;
              player2 = 0;
              subtract(player2pin3, "playerSec");
            }
          }
        }
      }
    }
  }

  checkwin();
  //---------------------player 1------------round4------
  delay(1000);
  clicked = 0;
  while(player1 == 1){
    while(clicked == 0){
      for (int pinNo = 0; pinNo <= NUM_LEDS-1; pinNo++) {
        if (digitalRead(pinNo + 29) == LOW) {
          int player1pin4 = pinNo;
          for(int x = 0;x<=8;x++){
            if(player1pin4 == pins[x]){
              leds[player1pin4] = CRGB(255,0,0);
              FastLED.show();
              clicked = 1;
              player1 = 0;
              player2 = 1;
              subtract(player1pin4, "playerFir");
            }
          }
        }
      }
    }
  }

  checkwin();
  //---------------------player 2--------round4--------
  delay(1000);
  clicked = 0;
  while(player2 == 1){
    while(clicked == 0){
      for (int pinNo = 0; pinNo <= NUM_LEDS-1; pinNo++) {
        if ( digitalRead(pinNo + 29) == LOW){
          int player2pin4 = pinNo;
          for(int x = 0;x<=8;x++){
            if(player2pin4 == pins[x]){
              leds[player2pin4] = CRGB(0,0,255);
              FastLED.show();
              clicked = 1;
              player1 = 1;
              player2 = 0;
              subtract(player2pin4, "playerSec");
            }
          }
        }
      }
    }
  }

  checkwin();
  //---------------------player 1------------round5------
  delay(1000);
  clicked = 0;
  while(player1 == 1){
    while(clicked == 0){
      for (int pinNo = 0; pinNo <= NUM_LEDS-1; pinNo++) {
        if (digitalRead(pinNo + 29) == LOW) {
          int player1pin5 = pinNo;
          for(int x = 0;x<=8;x++){
            if(player1pin5 == pins[x]){
              leds[player1pin5] = CRGB(255,0,0);
              FastLED.show();
              clicked = 1;
              player1 = 0;
              player2 = 1;
              subtract(player1pin5, "playerFir");
            }
          }
        }
      }
    }
  }
  /*
  for(int x = 0;x<=4;x++){
    Serial.println(player1tab[x]);
  }
  Serial.println("--------------");
  for(int x = 0;x<=4;x++){
    Serial.println(player2tab[x]);
  }
  */
  checkwin();
  resetTicTac();  
}


void subtract(int ledNum, String player){
  for(int g = 0;g<=8;g++){
    if(pins[g] == ledNum){
      Serial.println(pins[g]);
      if(player == "playerFir"){
        Serial.println("fir");
        player1tab[j] = pins[g];
        j += 1;
      }

      if(player == "playerSec"){
        Serial.println("sec");
        player2tab[i] = pins[g];
        i += 1;
      }
      pins[g] = 33;
    }
  }
}

void checkwin(){
  //------------------------------------------------------player 1------------------------------------------------------------
  for(int x=0;x<=4;x++){
    //-----------------------------------------------left down corner------------------------------------------------------
    if(player1tab[x] == 20){
      //------------------right------------------------
      for(int x=0;x<=4;x++){
        if(player1tab[x] == 22){     
          for(int x=0;x<=4;x++){
            if(player1tab[x] == 24){
              blinkwin("red");
            }
          }
        }
      }
      //-------------------up--------------------------
      for(int x=0;x<=4;x++){
        if(player1tab[x] == 10){     
          for(int x=0;x<=4;x++){
            if(player1tab[x] == 0){
              blinkwin("red");
            }
          }
        }
      }
      //-----------------diagonal----------------------
      for(int x=0;x<=4;x++){
        if(player1tab[x] == 12){     
          for(int x=0;x<=4;x++){
            if(player1tab[x] == 4){
              blinkwin("red");
            }
          }
        }
      } 
    }
    //-----------------------------------------------left center-----------------------------------------------------------
    if(player1tab[x] == 10){ 
      //---------------------right---------------------    
      for(int x=0;x<=4;x++){
        if(player1tab[x] == 12){
          for(int x=0;x<=4;x++){
            if(player1tab[x] == 14){
              blinkwin("red");
            }
          }
        }
      } 
    }     
    //-----------------------------------------------left up corner--------------------------------------------------------
    if(player1tab[x] == 0){ 
      //---------------------right---------------------    
      for(int x=0;x<=4;x++){
        if(player1tab[x] == 2){
          for(int x=0;x<=4;x++){
            if(player1tab[x] == 4){
              blinkwin("red");
            }
          }
        }
      }
      //--------------------diagonal-------------------
      for(int x=0;x<=4;x++){
        if(player1tab[x] == 12){
          for(int x=0;x<=4;x++){
            if(player1tab[x] == 24){
              blinkwin("red");
            }
          }
        }
      } 
    }
    //-----------------------------------------------up center-------------------------------------------------------------
    if(player1tab[x] == 2){ 
      //---------------------down---------------------    
      for(int x=0;x<=4;x++){
        if(player1tab[x] == 12){
          for(int x=0;x<=4;x++){
              if(player1tab[x] == 22){
              blinkwin("red");
            }
          }
        }
      } 
    }
    //-----------------------------------------------up right corner-------------------------------------------------------
    if(player1tab[x] == 4){ 
      //---------------------down---------------------    
      for(int x=0;x<=4;x++){
        if(player1tab[x] == 14){
          for(int x=0;x<=4;x++){
              if(player1tab[x] == 24){
              blinkwin("red");
            }
          }
        }
      } 
    }
  //}
  //------------------------------------------------------player 2------------------------------------------------------------
  //for(int x=0;x<=4;x++){
    //-----------------------------------------------left down corner------------------------------------------------------
    if(player2tab[x] == 20){
      //------------------right------------------------
      for(int x=0;x<=4;x++){
        if(player2tab[x] == 22){     
          for(int x=0;x<=4;x++){
            if(player2tab[x] == 24){
              blinkwin("blue");
            }
          }
        }
      }
      //-------------------up--------------------------
      for(int x=0;x<=4;x++){
        if(player2tab[x] == 10){     
          for(int x=0;x<=4;x++){
            if(player2tab[x] == 0){
              blinkwin("blue");
            }
          }
        }
      }
      //-----------------diagonal----------------------
      for(int x=0;x<=4;x++){
        if(player2tab[x] == 12){     
          for(int x=0;x<=4;x++){
            if(player2tab[x] == 4){
              blinkwin("blue");
            }
          }
        }
      } 
    }
    //-----------------------------------------------left center-----------------------------------------------------------
    if(player2tab[x] == 10){ 
      //---------------------right---------------------    
      for(int x=0;x<=4;x++){
        if(player2tab[x] == 12){
          for(int x=0;x<=4;x++){
            if(player2tab[x] == 14){
              blinkwin("blue");
            }
          }
        }
      } 
    }     
    //-----------------------------------------------left up corner--------------------------------------------------------
    if(player2tab[x] == 0){ 
      //---------------------right---------------------    
      for(int x=0;x<=4;x++){
        if(player2tab[x] == 2){
          for(int x=0;x<=4;x++){
            if(player2tab[x] == 4){
              blinkwin("blue");
            }
          }
        }
      }
      //--------------------diagonal-------------------
      for(int x=0;x<=4;x++){
        if(player2tab[x] == 12){
          for(int x=0;x<=4;x++){
            if(player2tab[x] == 24){
              blinkwin("blue");
            }
          }
        }
      } 
    }
    //-----------------------------------------------up center-------------------------------------------------------------
    if(player2tab[x] == 2){ 
      //---------------------down---------------------    
      for(int x=0;x<=4;x++){
        if(player2tab[x] == 12){
          for(int x=0;x<=4;x++){
              if(player2tab[x] == 22){
              blinkwin("blue");
            }
          }
        }
      } 
    }
    //-----------------------------------------------up right corner-------------------------------------------------------
    if(player2tab[x] == 4){ 
      //---------------------down---------------------    
      for(int x=0;x<=4;x++){
        if(player2tab[x] == 14){
          for(int x=0;x<=4;x++){
              if(player2tab[x] == 24){
              blinkwin("blue");
            }
          }
        }
      } 
    }
  }
}


void blinkwin(String color){
  if(color == "red"){
    fill_solid(leds, NUM_LEDS, CRGB(255,0,0));
    FastLED.show();
    delay(400);
    fill_solid(leds, NUM_LEDS, CRGB(0,0,0));
    FastLED.show();
    delay(400);
    fill_solid(leds, NUM_LEDS, CRGB(255,0,0));
    FastLED.show();
    delay(400);
    fill_solid(leds, NUM_LEDS, CRGB(0,0,0));
    FastLED.show();
    delay(400);
    fill_solid(leds, NUM_LEDS, CRGB(255,0,0));
    FastLED.show();
    delay(400);
    fill_solid(leds, NUM_LEDS, CRGB(0,0,0));
    FastLED.show();
    delay(400);
    resetTicTac();
  }
  if(color == "blue"){
    fill_solid(leds, NUM_LEDS, CRGB(0,0,255));
    FastLED.show();
    delay(400);
    fill_solid(leds, NUM_LEDS, CRGB(0,0,0));
    FastLED.show();
    delay(400);
    fill_solid(leds, NUM_LEDS, CRGB(0,0,255));
    FastLED.show();
    delay(400);
    fill_solid(leds, NUM_LEDS, CRGB(0,0,0));
    FastLED.show();
    delay(400);
    fill_solid(leds, NUM_LEDS, CRGB(0,0,255));
    FastLED.show();
    delay(400);
    fill_solid(leds, NUM_LEDS, CRGB(0,0,0));
    FastLED.show();
    delay(400);
    resetTicTac();
  }
}

void makePool(){
  leds[0] = CRGB(0, 0, 0);
  leds[1] = CRGB(255, 240, 0);
  leds[2] = CRGB(0, 0, 0);
  leds[3] = CRGB(255, 240, 0);
  leds[4] = CRGB(0, 0, 0);
  leds[5] = CRGB(255, 240, 0);
  leds[6] = CRGB(255, 240, 0);
  leds[7] = CRGB(255, 240, 0);
  leds[8] = CRGB(255, 240, 0);
  leds[9] = CRGB(255, 240, 0);
  leds[10] = CRGB(0, 0, 0);
  leds[11] = CRGB(255, 240, 0);
  leds[12] = CRGB(0, 0, 0);
  leds[13] = CRGB(255, 240, 0);
  leds[14] = CRGB(0, 0, 0);
  leds[15] = CRGB(255, 240, 0);
  leds[16] = CRGB(255, 240, 0);
  leds[17] = CRGB(255, 240, 0);
  leds[18] = CRGB(255, 240, 0);
  leds[19] = CRGB(255, 240, 0);
  leds[20] = CRGB(0, 0, 0);
  leds[21] = CRGB(255, 240, 0);
  leds[22] = CRGB(0, 0, 0);
  leds[23] = CRGB(255, 240, 0);
  leds[24] = CRGB(0, 0, 0);
  FastLED.show();
}

void resetTicTac(){
  pins[0] = 0;
  pins[1] = 2;
  pins[2] = 4;
  pins[3] = 10;
  pins[4] = 12;
  pins[5] = 14;
  pins[6] = 20;
  pins[7] = 22;
  pins[8] = 24;
  for(int x = 0;x<=4;x++){
    player1tab[x] = 33;
    player2tab[x] = 33;
  }
  player1 = 1;
  player2 = 0;
  clicked = 0;
  i = 0;
  j = 0;
  delay(500);
  playTicTac();
  
}

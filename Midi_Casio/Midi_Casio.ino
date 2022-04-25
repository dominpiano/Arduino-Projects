// works with keyboards with matrix 7x8
#define matrix1 8
#define matrix2 8

#include "MIDI.h"
MIDI MidiUSB;

int octave = 0; // add or subtract 8 for one octave
bool currentState[matrix1 * matrix2];
bool requestState[matrix1 * matrix2];
void setup() 
{
  //-----matrix1 number of pins-------
  pinMode(2,INPUT); //1
  pinMode(3,INPUT); //2
  pinMode(4,INPUT); //3
  pinMode(5,INPUT); //4
  pinMode(6,INPUT); //5
  pinMode(7,INPUT); //6
  pinMode(8,INPUT); //7
  pinMode(9,INPUT); //8

  //-----matrix2 number of pins-------
  //each matrix2 pin must be one above the previous one
  
  pinMode(12,INPUT); //1
  pinMode(13,INPUT); //2
  pinMode(14,INPUT); //3
  pinMode(15,INPUT); //4
  pinMode(16,INPUT); //5
  pinMode(17,INPUT); //6
  pinMode(18,INPUT); //7
  pinMode(19,INPUT); //8

  
}

void loop() 
{
  readKeys();
  writeKeys();
  delay(1);
}

void readKeys()
{
  for(int i=0; i<matrix2; i++)
  {
    //---------matrix2 pins-----------
    pinMode(12,INPUT); //1
    pinMode(13,INPUT); //2
    pinMode(14,INPUT); //3
    pinMode(15,INPUT); //4
    pinMode(16,INPUT); //5
    pinMode(17,INPUT); //6
    pinMode(18,INPUT); //7
    pinMode(19,INPUT); //8
    pinMode(i+12,OUTPUT); // <-- (this is your first pin number)
    
    digitalWrite(i,LOW);
    delayMicroseconds(1000);

    //you have to repeat this function matrix1 times
    requestState[i*matrix1+0] = !digitalRead(2);
    requestState[i*matrix1+1] = !digitalRead(3);
    requestState[i*matrix1+2] = !digitalRead(4);
    requestState[i*matrix1+3] = !digitalRead(5);
    requestState[i*matrix1+4] = !digitalRead(6);
    requestState[i*matrix1+5] = !digitalRead(7);
    requestState[i*matrix1+6] = !digitalRead(8);
    requestState[i*matrix1+7] = !digitalRead(9);
  }
}


void writeKeys()
{
  for(int i=0; i<matrix1 * matrix2; i++)
  {
    if(requestState[i]==true && currentState[i] == false)
    {
      noteOn(0, 36+octave+(i*matrix2)%matrix1 * matrix2+i/matrix1, 64);
      currentState[i] = requestState[i];
    }
    
    if(requestState[i]==false && currentState[i] == true)
    {
      noteOff(0, 36+octave+(i*matrix2)%matrix1 * matrix2+i/matrix1, 64);
      currentState[i] = requestState[i];
    }
  }
  MidiUSB.flush();
}


void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}

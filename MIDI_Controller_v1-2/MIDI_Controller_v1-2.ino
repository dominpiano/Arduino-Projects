#include <MIDI.h>
#include "Controller.h"


MIDI_CREATE_DEFAULT_INSTANCE();

//************************************************************
byte NUMBER_BUTTONS = 0;
byte NUMBER_POTS = 1;
byte NUMBER_MUX_BUTTONS = 0;
byte NUMBER_MUX_POTS = 0;
//************************************************************


Mux M1(10, 16, false); //Digital multiplexer on Arduino pin 10
Mux M2(A5, 8, true); //Analog multiplexer on Arduino analog pin A0
//*******************************************************************

Pot *POTS[] {&PO1};
//*******************************************************************



Button BU1(2, 0, 60, 1, 5 );
Button BU2(3, 0, 61, 1, 5 );
Button BU3(4, 0, 62, 1, 5 );
Button *BUTTONS[] {};
//*******************************************************************


void setup() {
  MIDI.begin(MIDI_CHANNEL_OFF);
}

void loop() {
  if (NUMBER_BUTTONS != 0) updateButtons();
  if (NUMBER_POTS != 0) updatePots();
}


//*****************************************************************
void updateButtons() {

  // Cycle through Button array
  for (int i = 0; i < NUMBER_BUTTONS; i = i + 1) {
    byte message = BUTTONS[i]->getValue();

    //  Button is pressed
    if (message == 0) {
      switch (BUTTONS[i]->Bcommand) {
        case 0: //Note
          MIDI.sendNoteOn(BUTTONS[i]->Bvalue, 127, BUTTONS[i]->Bchannel);
          break;
        case 1: //CC
          MIDI.sendControlChange(BUTTONS[i]->Bvalue, 127, BUTTONS[i]->Bchannel);
          break;
        case 2: //Toggle
          if (BUTTONS[i]->Btoggle == 0) {
            MIDI.sendControlChange(BUTTONS[i]->Bvalue, 127, BUTTONS[i]->Bchannel);
            BUTTONS[i]->Btoggle = 1;
          }
          else if (BUTTONS[i]->Btoggle == 1) {
            MIDI.sendControlChange(BUTTONS[i]->Bvalue, 0, BUTTONS[i]->Bchannel);
            BUTTONS[i]->Btoggle = 0;
          }
          break;
      }
    }

    //  Button is not pressed
    if (message == 1) {
      switch (BUTTONS[i]->Bcommand) {
        case 0:
          MIDI.sendNoteOff(BUTTONS[i]->Bvalue, 0, BUTTONS[i]->Bchannel);
          break;
        case 1:
          MIDI.sendControlChange(BUTTONS[i]->Bvalue, 0, BUTTONS[i]->Bchannel);
          break;
      }
    }
  }
}


void updatePots() {
  for (int i = 0; i < NUMBER_POTS; i = i + 1) {
    byte potmessage = POTS[i]->getValue();
    if (potmessage != 255) MIDI.sendControlChange(POTS[i]->Pcontrol, potmessage, POTS[i]->Pchannel);
  }
}

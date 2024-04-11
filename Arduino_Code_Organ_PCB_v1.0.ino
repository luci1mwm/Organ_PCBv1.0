#include <MIDI.h> // Library created by Francois Best
struct MIDISettings : public midi::DefaultSettings
{
  static const long BaudRate = 115200; // 115200 (Serial MIDI USB), 31250 (MIDI Connector Application)
};
MIDI_CREATE_CUSTOM_INSTANCE(HardwareSerial, Serial, MIDI, MIDISettings);
byte midiCh = 2; // MIDI channel
byte note = 30; // Initial note
byte note2 = 70;
byte cc = 1;


const int N_BUTTONS = 5; // le nombre de boutons
const int N_BUTTONS2 = 8;

const int N_POTS = 8;
const int N_POTS2 = 4;



int buttonState[N_BUTTONS] = { 0 };
int buttonPState[N_BUTTONS] = { 0 };

int buttonState2[N_BUTTONS2] = { 0 };
int buttonPState2[N_BUTTONS2] = { 0 };


int potState[N_POTS] = { 0 };
int potPState[N_POTS] = { 0 };
byte midiState[N_POTS] = { 0 };
byte midiPState[N_POTS] = { 0 };

int potState2[N_POTS2] = { 0 };
int potPState2[N_POTS2] = { 0 };
byte midiState2[N_POTS2] = { 0 };
byte midiPState2[N_POTS2] = { 0 };

byte VarPot = 0;
byte VarPot2 = 0;


const byte PIN_ENABLE = A4;
const byte PIN_ADDR_A = 3;
const byte PIN_ADDR_B = 5;
const byte PIN_ADDR_C = 6;
const byte PIN_SIG = A0;

const byte PIN_ENABLE2 = A4;
const byte PIN_ADDR_A2 = 8;
const byte PIN_ADDR_B2= 9;
const byte PIN_ADDR_C2= 10;
const byte PIN_SIG2 = A1;

//const pour le mux pots
const int PIN_ENABLE3 = A4;
const int PIN_ADDR_A3 = 11;
const int PIN_ADDR_B3= 12;
const int PIN_ADDR_C3= 13;
const int PIN_SIG3 = A2;

const int PIN_ENABLE4 = A4;
const int PIN_ADDR_A4 = A5;
const int PIN_ADDR_B4= 4;
const int PIN_ADDR_C4= 7;
const int PIN_SIG4 = A3;


//byte BUTTON_CH = 0;

//byte POT_CH = 0;

int buttonPin[N_BUTTONS] = { 30, 31, 32, 33, 34};
int buttonPin2[N_BUTTONS2] = {70, 71, 72, 73, 74, 75, 76, 77};

//int potCC[N_POTS] = { 1, 2};

int readDigitalMux(byte channel) {
digitalWrite(PIN_ADDR_A, bitRead(channel, 0));
digitalWrite(PIN_ADDR_B, bitRead(channel, 1));
digitalWrite(PIN_ADDR_C, bitRead(channel, 2));
return digitalRead(PIN_SIG);
};
int readDigitalMux2(byte channel) {
digitalWrite(PIN_ADDR_A2, bitRead(channel, 0));
digitalWrite(PIN_ADDR_B2, bitRead(channel, 1));
digitalWrite(PIN_ADDR_C2, bitRead(channel, 2));
return digitalRead(PIN_SIG2);
};


void SetMuxChannel13(byte channel) {
digitalWrite(PIN_ADDR_A3, bitRead(channel, 0));
digitalWrite(PIN_ADDR_B3, bitRead(channel, 1));
digitalWrite(PIN_ADDR_C3, bitRead(channel, 2));
digitalWrite(PIN_ENABLE3, bitRead(channel, 3));
};

void SetMuxChannel14(byte channel) {
digitalWrite(PIN_ADDR_A4, bitRead(channel, 0));
digitalWrite(PIN_ADDR_B4, bitRead(channel, 1));
digitalWrite(PIN_ADDR_C4, bitRead(channel, 2));
digitalWrite(PIN_ENABLE4, bitRead(channel, 3));
};

  

void setup() {

pinMode(PIN_ADDR_A, OUTPUT);
pinMode(PIN_ADDR_B, OUTPUT);
pinMode(PIN_ADDR_C, OUTPUT);

pinMode(PIN_ADDR_A2, OUTPUT);
pinMode(PIN_ADDR_B2, OUTPUT);
pinMode(PIN_ADDR_C2, OUTPUT);


pinMode(PIN_ADDR_A3, OUTPUT);
pinMode(PIN_ADDR_B3, OUTPUT);
pinMode(PIN_ADDR_C3, OUTPUT);
pinMode(PIN_ENABLE3, OUTPUT);
pinMode(PIN_SIG3, INPUT);

pinMode(PIN_ADDR_A4, OUTPUT);
pinMode(PIN_ADDR_B4, OUTPUT);
pinMode(PIN_ADDR_C4, OUTPUT);
pinMode(PIN_ENABLE4, OUTPUT);
pinMode(PIN_SIG4, INPUT);


digitalWrite(PIN_ADDR_A, LOW);
digitalWrite(PIN_ADDR_B, LOW);
digitalWrite(PIN_ADDR_C, LOW);

digitalWrite(PIN_ADDR_A2, LOW);
digitalWrite(PIN_ADDR_B2, LOW);
digitalWrite(PIN_ADDR_C2, LOW);


pinMode(PIN_ENABLE, OUTPUT);
digitalWrite(PIN_ENABLE, LOW);

pinMode(PIN_ENABLE2, OUTPUT);
digitalWrite(PIN_ENABLE2, LOW);


Serial.begin(115200);
Serial.println("hello world");
// Setup des broches des boutons
for (int i = 0; i < N_BUTTONS; i++) {
pinMode(buttonPin[i], INPUT_PULLUP); // Utilisation de la résistance de pull-up interne
  }

for (int i = 0; i < N_BUTTONS2; i++) {
pinMode(buttonPin2[i], INPUT_PULLUP); // Utilisation de la résistance de pull-up interne
  }

}

void loop() {

//POTENTIOMETERS

for (int i = 0; i < N_POTS; i++) {

  SetMuxChannel13(i);
    potState[i] = analogRead (PIN_SIG3);
    midiState[i] = map(potState[i], 0, 1023, 0, 127); // Arduino reads all pots and convert the analog voltage (0-5V) into digital values (0-127)
    VarPot = abs(potPState[i] - potState[i]);

    if (VarPot > 6)
    {
      if(midiState[i] != midiPState[i]) 
      {
      MIDI.sendControlChange(0 + i , midiState[i], 2); // cc number, cc value, midi channel
      
      midiPState[i] = midiState[i];
      potPState[i] = potState[i];
      }
   } 
}

for (int i = 0; i < N_POTS2; i++) {

  SetMuxChannel14(i);
    potState2[i] = analogRead (PIN_SIG4);
    midiState2[i] = map(potState2[i], 0, 1023, 0, 127); // Arduino reads all pots and convert the analog voltage (0-5V) into digital values (0-127)
    VarPot2 = abs(potPState2[i] - potState2[i]);

    if (VarPot2 > 6)
    {
      if(midiState2[i] != midiPState2[i]) 
      {
      MIDI.sendControlChange(8 + i , midiState2[i], 2); // cc number, cc value, midi channel
    
      midiPState2[i] = midiState2[i];
      potPState2[i] = potState2[i];
      }
   } 
}

//BUTTONS

for (byte i = 0; i < N_BUTTONS; i++) {

buttonState[i] = readDigitalMux(i);

if (buttonState[i] != buttonPState[i]) {
if (buttonState[i] == HIGH) {
        // if the button is not pressed (pin state High) send the following message
        MIDI.sendNoteOn(note + i, 127, midiCh);
      } else {
        // if the button is pressed (pin state LOW) send the following message
        MIDI.sendNoteOn(note + i, 0, midiCh);
      } 

    delay(20);
    }
    buttonPState[i] = buttonState[i];
    
  }

for (byte i = 0; i < N_BUTTONS2; i++) {

buttonState2[i] = readDigitalMux2(i);

if (buttonState2[i] != buttonPState2[i]) {
if (buttonState2[i] == HIGH) {
        // if the button is not pressed (pin state High) send the following message
        MIDI.sendNoteOn(note2 + i, 127, midiCh);
      } else {
        // if the button is pressed (pin state LOW) send the following message
        MIDI.sendNoteOn(note2 + i, 0, midiCh);
      } 

    delay(20);
    }
    buttonPState2[i] = buttonState2[i];
    
  }  
}

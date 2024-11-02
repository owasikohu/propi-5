/*  Example changing the gain of a sinewave,
    using Mozzi sonification library.

    Demonstrates the use of a control variable to influence an
    audio signal.

    Circuit: Audio output on digital pin 9 on a Uno or similar, or
    DAC/A14 on Teensy 3.1, or
    check the README or http://sensorium.github.io/Mozzi/

    Mozzi documentation/API
    https://sensorium.github.io/Mozzi/doc/html/index.html

    Mozzi help/discussion/announcements:
    https://groups.google.com/forum/#!forum/mozzi-users

    Copyright 2012-2024 Tim Barrass and the Mozzi Team

    Mozzi is licensed under the GNU Lesser General Public Licence (LGPL) Version 2.1 or later.
*/


#include <Arduino.h>
#include <Adafruit_TinyUSB.h>
#include <MIDI.h>

#include <Mozzi.h>
#include <Oscil.h> 
#include <mozzi_midi.h>
#include <ADSR.h>
#include <tables/saw8192_int8.h>

#define NUM_VOICES 4


Oscil <8192, MOZZI_AUDIO_RATE> osc1(SAW8192_DATA);

ADSR <AUDIO_RATE, AUDIO_RATE> envelope;


unsigned int Dur, Atk, Dec, Sus, Rel;

// USB MIDI object
Adafruit_USBD_MIDI usb_midi;

// Create a new instance of the Arduino MIDI Library
MIDI_CREATE_INSTANCE(Adafruit_USBD_MIDI, usb_midi, MIDI);



void setup(){

  if (!TinyUSBDevice.isInitialized()) {
    TinyUSBDevice.begin(0);
  }

  Serial.begin(115200);

  MIDI.begin(MIDI_CHANNEL_OMNI);

  MIDI.setHandleNoteOn(handleNoteOn);
  MIDI.setHandleNoteOff(handleNoteOff);


  startMozzi(128); 
  osc1.setFreq(440);
  Atk = 10;
  Dec = 10;
  Sus = 100;
  Rel = 500;
  envelope.setADLevels(255, 128);
  envelope.setTimes(Atk, Dec, Sus, Rel);
  
}


void updateControl(){
  TinyUSBDevice.task();
  MIDI.read();
}


AudioOutput updateAudio(){
  envelope.update();
  return MonoOutput::from16Bit(osc1.next() * envelope.next());
}


void loop(){
  audioHook(); // required here
}




void handleNoteOn(byte channel, byte pitch, byte velocity) {
  // Log when a note is played
  Serial.print("Note On: ");
  Serial.print("Channel = ");
  Serial.print(channel);
  Serial.print(", Pitch = ");
  Serial.print(pitch);
  Serial.print(", Velocity = ");
  Serial.println(velocity);
  osc1.setFreq(mtof(pitch));
  envelope.noteOn();
}

void handleNoteOff(byte channel, byte pitch, byte velocity) {
  // Log when a note is released
  Serial.print("Note Off: ");
  Serial.print("Channel = ");
  Serial.print(channel);
  Serial.print(", Pitch = ");
  Serial.print(pitch);
  Serial.print(", Velocity = ");
  Serial.println(velocity);
  envelope.noteOff();
}
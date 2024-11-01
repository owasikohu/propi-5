/*  Example of a sound being triggered by MIDI input.

    Demonstrates playing notes with Mozzi in response to MIDI input,
    using  Arduino MIDI library v4.2
    (https://github.com/FortySevenEffects/arduino_midi_library/releases/tag/4.2)

    Circuit:
      MIDI input circuit as per http://arduino.cc/en/Tutorial/Midi
      Note: midi input on rx pin, not tx as in the illustration on the above page.
      Midi has to be disconnected from rx for sketch to upload.
      Audio output on digital pin 9 on a Uno or similar.

   Mozzi documentation/API
   https://sensorium.github.io/Mozzi/doc/html/index.html

   Mozzi help/discussion/announcements:
   https://groups.google.com/forum/#!forum/mozzi-users

   Copyright 2013-2024 Tim Barrass and the Mozzi Team

   Mozzi is licensed under the GNU Lesser General Public Licence (LGPL) Version 2.1 or later.
*/
#include <Arduino.h>
#include <Adafruit_TinyUSB.h>
#include <MIDI.h>
// use #define for MOZZI_CONTROL_RATE, not a constant
#define MOZZI_CONTROL_RATE 128 // Hz, powers of 2 are most reliable
#include <Mozzi.h>
#include <Oscil.h>
#include <tables/sin2048_int8.h>

Oscil <2048, MOZZI_AUDIO_RATE> aSin(SIN2048_DATA);

// USB MIDI object
Adafruit_USBD_MIDI usb_midi;

// Create a new instance of the Arduino MIDI Library
MIDI_CREATE_INSTANCE(Adafruit_USBD_MIDI, usb_midi, MIDI);


void setup() {
    // Initialize USB
  if (!TinyUSBDevice.isInitialized()) {
    TinyUSBDevice.begin(0);
  }

  Serial.begin(115200);

  // Initialize MIDI
  MIDI.begin(MIDI_CHANNEL_OMNI);

  // Allow interrupts for MIDI
  MIDI.setHandleNoteOn(handleNoteOn);
  MIDI.setHandleNoteOff(handleNoteOff);

  aSin.setFreq(440);
  startMozzi();
}


void updateControl(){
  TinyUSBDevice.task();
  MIDI.read();
}


AudioOutput updateAudio(){
  return MonoOutput::from16Bit(aSin.next());
}


void loop() {
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
}

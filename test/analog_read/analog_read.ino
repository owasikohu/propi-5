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
#include <Mozzi.h>
#include <Oscil.h> 
#include <tables/saw4096_int8.h>

Oscil <4096, MOZZI_AUDIO_RATE> osc1(SAW4096_DATA);

void setup(){
   Serial.begin(115200);

  startMozzi(); // start with default control rate of 64
  osc1.setFreq(440); // set the frequency
}


void updateControl(){
  int pw = map(mozziAnalogRead16(A0), 0, 65535, 0, 255); //補正
  Serial.println(pw);
}


AudioOutput updateAudio(){
  return MonoOutput::from16Bit(osc1.next() * 8);
}


void loop(){
  audioHook(); // required here
}
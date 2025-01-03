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

#include <Mozzi.h>
#include <Oscil.h> // oscillator template
#include <tables/smoothsquare8192_int8.h>
#include <tables/saw8192_int8.h>
#include <tables/triangle_warm8192_int8.h>
#include <tables/whitenoise8192_int8.h>

#define CONTROL_RATE 128

#define NUM_VOICES 4

// use: Oscil <table_size, update_rate> oscilName (wavetable), look in .h file of table #included above
Oscil <8192, MOZZI_AUDIO_RATE> osc1;
Oscil <8192, MOZZI_AUDIO_RATE> osc2;

// control variable, use the smallest data size you can for anything used in audio



void setup(){
  0-255
    /*
  int osc1_wave =
  int osc1_pitch =

  int osc2_wave =
  int osc2_pitch =
  int osc2_detune = 

  int mix_osc1_vol =
  int mix_osc2_vol =
  
  int fil_cutoff =
  int fil_resonance =

  int eg_attack =
  int eg_decay =
  int eg_sustain =
  int eg_release =

  int lfo_mode =
  int lfo_rate
  int lfo_depth
  */
  startMozzi(); // start with default control rate of 64
  osc1.setFreq(440); // set the frequency
}


void updateControl(){
  // as byte, this will automatically roll around to 255 when it passes 0
  
}


AudioOutput updateAudio(){
  return MonoOutput::from16Bit(osc1.next() * 8);
}


void loop(){
  audioHook(); // required here
}
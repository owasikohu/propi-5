/*********************************************************************
 Adafruit invests time and resources providing this open source code,
 please support Adafruit and open-source hardware by purchasing
 products from Adafruit!

 MIT license, check LICENSE for more information
 Copyright (c) 2019 Ha Thach for Adafruit Industries
 All text above, and the splash screen below must be included in
 any redistribution
*********************************************************************/

/* This sketch is enumerated as USB MIDI device.
 * Required Library:
 * - MIDI Library by Forty Seven Effects
 *   https://github.com/FortySevenEffects/arduino_midi_library
 */

#include <Arduino.h>
#include <Adafruit_TinyUSB.h>
#include <MIDI.h>

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
}

void loop() {
  // Call the TinyUSB task to handle MIDI
  TinyUSBDevice.task();

  // Read incoming MIDI messages
  MIDI.read();
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

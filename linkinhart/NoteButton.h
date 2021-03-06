/*
 * Docstring
 */

#ifndef NoteButton_h
#define NoteButton_h

#include "Arduino.h"

class NoteButton {

  public:
    NoteButton(int inputPin);
    void processButton(int note, int velocity);
    void lastNoteOff(byte velocity);

   private:
    void _sendNoteOn(byte note, byte velocity);
    void _sendNoteOff(byte note, byte velocity);
    void _sendMidi(byte command, byte data1, byte data2);
   
    int _inputPin;
    int _state;
    int _lastNote;
};

NoteButton::NoteButton(int inputPin) {
  
  _inputPin = inputPin;
  _state = 0;
}

void NoteButton::processButton(int note, int velocity) {

  if (_state == HIGH && digitalRead(_inputPin) == LOW) {
    _state = LOW;
    _sendNoteOn(note, velocity);
    if (note != 0)
    _lastNote = note;
  }

  if (_state == LOW && digitalRead(_inputPin) == HIGH) {
    _state = HIGH;
    _sendNoteOff(_lastNote, velocity);
  }

}

void NoteButton::lastNoteOff(byte velocity) {
  _sendNoteOff(_lastNote, velocity);
  _lastNote = 0;
}

void NoteButton::_sendNoteOn(byte note, byte velocity) {
  if (note != 0)
  _sendMidi(144, note, velocity);
}

void NoteButton::_sendNoteOff(byte note, byte velocity) {
  if (note != 0)
  _sendMidi(128, note, velocity);
}

void NoteButton::_sendMidi(byte command, byte data1, byte data2) //pass values out through standard Midi Command
{
   Serial.write(command);  // control
   Serial.write(data1);  // channel
   Serial.write(data2);  // power
}

#endif



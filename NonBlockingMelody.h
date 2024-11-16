// https://github.com/median-dispersion/Non-Blocking-Melody

#ifndef _NON_BLOCKING_MELODY_H
#define _NON_BLOCKING_MELODY_H

#include "Arduino.h"
#include <span>

class NonBlockingMelody {

  // ----------------------------------------------------------------------------------------------
  // Public

  public:

    // Note structure
    struct Note {

      uint16_t frequencyHertz;       // Frequency of the note in Hertz
      uint16_t durationMilliseconds; // Duration of the note in milliseconds

    };

    NonBlockingMelody(uint8_t speakerPin);                  // Constructor

    void begin();                                           // Initialize everything
    void update();                                          // Update the melody
    void play(std::span<Note> notes, uint16_t repeats = 1); // Play a melody
    void pause();                                           // Pause the melody
    void resume();                                          // Resume the melody
    void stop();                                            // Stop the melody
    bool playing(std::span<Note> notes = {});               // Returns the playback status

  //-----------------------------------------------------------------------------------------------
  // Private

  private:

    uint8_t         _speakerPin;        // The pin the speaker is connected to
    bool            _playing;           // Playback status flag
    std::span<Note> _notes;             // Reference to array of notes
    uint16_t        _repeats;           // How often the melody repeats
    uint16_t        _note;              // Current note
    bool            _forever;           // Flag for playing forever
    uint64_t        _timerMilliseconds; // Timer for measuring the update interval

};

#endif
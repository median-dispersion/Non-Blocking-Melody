// https://github.com/median-dispersion/Non-Blocking-Melody

#include "NonBlockingMelody.h"

// ------------------------------------------------------------------------------------------------
// Public

// ================================================================================================
// Constructor
// ================================================================================================
NonBlockingMelody::NonBlockingMelody(uint8_t speakerPin):

  // Initialize members
  _speakerPin(speakerPin),
  _playing(false),
  _notes(nullptr),
  _length(0),
  _repeats(0),
  _note(0),
  _forever(false),
  _timerMilliseconds(0)

{}

// ================================================================================================
// Initialize everything
// ================================================================================================
void NonBlockingMelody::begin() {

  // Set pin mode of speaker pin to OUTPUT
  pinMode(_speakerPin, OUTPUT);

}

// ================================================================================================
// Update the melody
// ================================================================================================
void NonBlockingMelody::update() {

  // If playing a melody
  if (_playing) {

    // If the melody repeats
    if (_repeats) {

      // Set the previous note to the current note
      uint16_t previousNote = _note;

      // If not the first note, decrease to the previous note
      if (previousNote) { previousNote--; }

      // Calculate the time difference since the last update
      // If last update time is greater or equal to the last notes duration
      // Then the last note has finished playing
      if (millis() - _timerMilliseconds >= _notes[previousNote].durationMilliseconds) {
        
        // If the current note has not reached the length of the array of notes
        // The last note has not been played -> continue
        if (_note < _length) {
          
          // Store current time in milliseconds
          _timerMilliseconds = millis();

          // If the note has a frequency, i.e., it's not silent
          if (_notes[_note].frequencyHertz) {
            
            // Use tone to play on pin, with frequency, for duration
            tone(_speakerPin, _notes[_note].frequencyHertz, _notes[_note].durationMilliseconds);

          }

          // Increase note to the next note
          _note++;

        // When the end of the melody has been reached
        } else {
          
          // Stop playback of current note
          noTone(_speakerPin);

          // Reset to the first note
          _note = 0;

          // If it's not repeating forever
          if (!_forever) {
            
            // Decrease the repeat count
            _repeats--;

          }

        }

      }

    // If no more repeats
    } else {
      
      // Stop playing
      stop();

    }

  }

}

// ================================================================================================
// Play a melody
// ================================================================================================
void NonBlockingMelody::play(Note *notes, uint16_t length, uint16_t repeats) {

  _playing = true;   // Set the playback status
  _notes   = notes;  // Set the array of notes
  _length  = length; // Set the length of the melody
  _note    = 0;      // Reset to the first note

  // If a number of repeats was provided
  if (repeats) {

    _repeats = repeats; // Set the repeats to the repeat value provided
    _forever = false;   // Set the forever flag to false

  // If repeat forever
  } else {

    _repeats = UINT16_MAX; // Set the repeats to the max value
    _forever = true;       // Set the forever flag to true

  }

}

// ================================================================================================
// Pause the melody
// ================================================================================================
void NonBlockingMelody::pause() {

  // Set the playback status to false
  _playing = false;

}

// ================================================================================================
// Resume the melody
// ================================================================================================
void NonBlockingMelody::resume() {

  // Set the playback status to true
  _playing = true;

}

// ================================================================================================
// Stop playing the melody
// ================================================================================================
void NonBlockingMelody::stop() {

  // Stop playback of current note
  noTone(_speakerPin);

  _playing = false;   // Set playback status to false
  _notes   = nullptr; // Unset the notes
  _length  = 0;       // Reset the melody length
  _repeats = 0;       // Reset the melody repeats
  _note    = 0;       // Reset the current note
  _forever = false;   // Reset the forever flag

}

// ================================================================================================
// Returns the playback status
// ================================================================================================
bool NonBlockingMelody::playing(Note *notes) {

  // Check if playback is set to true
  if (_playing) {

    // Check if no specific melody was provided
    if (!notes) {

      // If no specific melody was provided and playback is set to true, something is playing
      // Return playback status: true
      return true;

    // If a specific melody was provided
    } else {

      // Check if the provided melody is the melody that is currently playing
      if (notes == _notes) {

        // The melody provided is currently playing
        // Return playback status: true
        return true;

      }

    }

  }
  
  // If none of the previous criteria were met, no playback is occurring
  // Return playback status: false
  return false;

}
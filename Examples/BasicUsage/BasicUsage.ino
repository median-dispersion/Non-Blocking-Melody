/*

  This is an example of how to create a short 8 note melody and play it using the Non-Blocking Melody library.

  Median Dispersion 2024
  https://github.com/median-dispersion/Non-Blocking-Melody

*/

#include "NonBlockingMelody.h"

//-------------------------------------------------------------------------------------------------
// User configuration

// Define the pin the speaker is connected to
#define SPEAKER_PIN 47 

//-------------------------------------------------------------------------------------------------
// Global variables

// Create the melody object using the defined speaker pin
NonBlockingMelody melody(SPEAKER_PIN);

// An array of notes that make up the melody with a frequency in Hertz and duration in milliseconds
// (For a pause in between notes, use a frequency of 0 Hertz)
NonBlockingMelody::Note notes[8] = {

  {523,  65}, // 523Hz,  65ms
  {0,    65}, // 0Hz,    65ms
  {523,  65}, // 523Hz,  65ms
  {0,    65}, // 0Hz,    65ms
  {659,  65}, // 659Hz,  65ms
  {0,    65}, // 0Hz,    65ms
  {698, 130}, // 698Hz, 130ms
  {0,    65}  // 0Hz,    65ms

};

// ================================================================================================
// Setup
// ================================================================================================
void setup() {

  // Initialize melody object
  melody.begin();

  // Play the melody
  // (array of notes, repeats: default = 1)
  melody.play(notes);

}

// ================================================================================================
// Main loop
// ================================================================================================
void loop() {

  // Update the melody in a non-blocking manner
  // This is required to continue the playback of the melody
  // Keep in mind that if the update interval i.e., the total loop time of your program is longer than the note that is being played the melody might start to lag
  // To prevent this, keep the main loop as fast as possible by avoiding delays and other blocking code
  melody.update();

}
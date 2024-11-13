/*

  This is an example of how to create a short melody with predefined notes that repeats 10 times.
  The melody can be controlled (pause, resume, stop) with 3 buttons.
  It also prints the playback status of the melody to the serial console.

  Median Dispersion 2024
  https://github.com/median-dispersion/Non-Blocking-Melody

*/

#include "NonBlockingMelody.h"        // Include the main library
#include "NonBlockingMelody/Notes.h"  // Include a list of notes

//-------------------------------------------------------------------------------------------------
// User configuration

// Define pin assignments
#define SPEAKER_PIN       47 
#define PAUSE_BUTTON_PIN  10
#define RESUME_BUTTON_PIN 11
#define STOP_BUTTON_PIN   12

//-------------------------------------------------------------------------------------------------
// Global variables

// Create the melody object
NonBlockingMelody melody(SPEAKER_PIN);

// An array of notes that make up the melody with a frequency in Hertz and duration in milliseconds
// The note frequencies are defined in "NonBlockingMelody/Notes.h"
NonBlockingMelody::Note notes[8] = {

  {NOTE_E6,      50},
  {NOTE_SILENT,  50},
  {NOTE_F6,      50},
  {NOTE_SILENT,  50},
  {NOTE_E6,      50},
  {NOTE_SILENT,  50},
  {NOTE_F6,      50},
  {NOTE_SILENT, 500}

};

// Length of the melody, i.e., the number of notes
const uint16_t length = sizeof(notes) / sizeof(notes[0]);

// Loop timer
uint64_t loopTimer = 0;

// ================================================================================================
// Setup
// ================================================================================================
void setup() {

  // Initialize serial communication
  Serial.begin(115200);

  // Set pin modes
  pinMode(PAUSE_BUTTON_PIN,  INPUT);
  pinMode(RESUME_BUTTON_PIN, INPUT);
  pinMode(STOP_BUTTON_PIN,   INPUT);

  // Initialize
  melody.begin();

  // Play the melody with 10 repeats
  // For infinite playback, set repeats to 0
  melody.play(notes, length, 10);

}

// ================================================================================================
// Main loop
// ================================================================================================
void loop() {

 // Update the melody in a non-blocking manner
  // This is required to continue the playback of the melody
  // Keep in mind that if the update interval i.e., the time it takes to call this function is longer than the note that is being played the melody might start to lag
  // To prevent this, keep the main program as fast as possible by avoiding delays and other blocking code
  melody.update();

  // If the pause button is pressed, pause the melody playback
  if (digitalRead(PAUSE_BUTTON_PIN) == HIGH) {
    melody.pause();
  }

  // If the resume button is pressed, resume the playback
  if (digitalRead(RESUME_BUTTON_PIN) == HIGH) {
    melody.resume();
  }

  // If the stop button is pressed, stop the melody
  if (digitalRead(STOP_BUTTON_PIN) == HIGH) {
    melody.stop();
  }

  // Update every second
  if (millis() - loopTimer >= 1000) {

    // Check playback status
    if (melody.playing()) {

      // If playing, print this
      Serial.println("Melody is playing...");

    } else {

      // If paused or stopped, print this
      Serial.println("Melody is not playing!");

    }

    // Update loop timer
    loopTimer = millis();

  }

}
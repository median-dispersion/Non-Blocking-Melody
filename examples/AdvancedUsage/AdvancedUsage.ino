/*

  This is an example of how to create a short melody with predefined notes that repeats forever.
  The melody can be controlled (pause, resume, stop) via the Serial Monitor.
  It also prints the playback status of the melody via the Serial Monitor.

  Median Dispersion 2024
  https://github.com/median-dispersion/Non-Blocking-Melody

*/

#include "Arduino.h"
#include "NonBlockingMelody.h"        // Include the main library
#include "NonBlockingMelody/Notes.h"  // Include a list of notes

//-------------------------------------------------------------------------------------------------
// User configuration

// Define pin assignments
#define SPEAKER_PIN 9

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

// Loop timer
uint64_t loopTimer = 0;

// ================================================================================================
// Setup
// ================================================================================================
void setup() {

  // Initialize serial communication
  Serial.begin(115200);

  // Initialize melody object
  melody.begin();

  // Play the melody forever by setting the repeats to 0
  melody.play(notes, 0);

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

  // Check if data was sent via the Serial Monitor
  if (Serial.available()) {

    // Read the data as a string
    String command = Serial.readString();

    // Remove any trailing newlines or spaces
    command.trim();

    // Check the string and either pause, resume or stop the melody
    if (command == "pause" ) { melody.pause();  }
    if (command == "resume") { melody.resume(); }
    if (command == "stop"  ) { melody.stop();   }

  }

  // Update every 0.25 seconds
  if (millis() - loopTimer >= 250) {

    // Check playback status
    if (melody.playing()) {

      // If playing, print this
      Serial.println("Melody is playing...");

    } else {

      // If paused or stopped, print this
      Serial.println("Melody is not playing!");

    }

    // The playback of a specific melody can be checked by using
    // melody.playing(arrayOfNotes)
    // Where the arrayOfNotes are the notes you would pass to the play function to initiate the melody

    // Update loop timer
    loopTimer = millis();

  }

}
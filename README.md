# Non-Blocking Melody

<p align="center"><img src="./Assets/Banner.svg" style="width:100%" alt="Banner"></p>

<p>
  <img alt="GitHub Release" src="https://img.shields.io/github/v/release/median-dispersion/Non-Blocking-Melody">
  <img alt="GitHub License" src="https://img.shields.io/github/license/median-dispersion/Non-Blocking-Melody">
</p>

An Arduino library for non-blocking melody playback. This library can be used for non-blocking melody playback, allowing concurrent tasks on a microcontroller to be executed while playing music through a buzzer or speaker. It takes an array of notes as input with a frequency in Hertz and a duration in milliseconds. It uses the built-in `Tone` functionality for PWM signal generation.

> [!NOTE]
> This library is **not** using a parallel / asynchronous / multithreading approach and will take time to process, though during note playback will be non-blocking and allow concurrent tasks to be executed.

## ✨ Examples

### Example Sketch

This is a basic example illustrating a simple implementation of this library. For more detailed explanations, look at the included examples in `examples/`.

```c++
// Include the library & a list of note definitions
#include "NonBlockingMelody.h"
#include "NonBlockingMelody/Notes.h"

// Configuration
#define SPEAKER_PIN 9

// Create the melody object
NonBlockingMelody melody(SPEAKER_PIN);

// Create an array of notes
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

void setup() {

  // Initialize melody object
  melody.begin();

  // Play the melody forever by setting the repeats to 0
  melody.play(notes, 0);

}

void loop() {

    // Update the melody in a non-blocking manner
    melody.update();

}
```

### Basic Usage

The most basic example of this library can be found in the `examples/BasicUsage/BasicUsage.ino` sketch file. It shows how to create a short 8 note melody and play it using the Non-Blocking Melody library.

### Advanced Usage

A more complex example of this library can be found in the `examples/AdvancedUsage/AdvancedUsage.ino` sketch file. This example demonstrates how to create a short melody with predefined notes that repeats forever. The melody can be controlled (pause, resume, stop) via the Serial Monitor. It also prints the playback status of the melody via the Serial Monitor.

## 🛠️ Library Functions

These are the functions this library provides. For more detailed examples on how to use these functions, look at the [Examples](#-examples) section.

Create a melody object.
```c++
NonBlockingMelody melody(SPEAKER_PIN);
```

Initialize the object.
```c++
melody.begin();
```

Create an array of Notes. The `Note` struct that comes with this library consists of two `uint16_t`, one for the frequency of the note in Hertz and one for the duration in milliseconds. A note with a 0 Hz frequency will be a silent pause.
```c++
NonBlockingMelody::Note notes[/*length*/] = {/*{frequency, duration}*/};
```

Play a melody. Takes in the previously defined array of notes and a number of repeats. For infinite playback, the number of repeats can be set to `0` (default number of repeats = 1).
```c++
melody.play(notes, 2);
```

Pause melody playback (optional).
```c++
melody.pause();
```

Resume melody playback (optional). This will only resume playback if the melody was previously paused.
```c++
melody.pause();
```

Stop melody playback (optional). This will stop the melody playback and unset the array of notes. After stopping, the melody can not be resumed.
```c++
melody.pause();
```

Check melody playback status (optional). Returns if a melody is being played. Checking if a specific melody is being played can be done by passing an array of notes to this function. (default = any melody, return = true / false)
```c++
melody.playing();
```
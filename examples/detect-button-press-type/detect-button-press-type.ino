// Copyright (C) 2024 Morgritech
//
// Licensed under GNU General Public License v3.0 (GPLv3) License.
// See the LICENSE file in the project root for full license details.

/// @file detect-button-press-type.ino
/// @brief Example showing how to detect short or long (press and hold) button presses using the MT-arduino-momentary-button library.

#include <momentary_button.h>

/// @brief The serial communication speed for the Arduino board.
const int kBaudRate = 9600;

/// @brief The main application entry point for initialisation tasks.
void setup() {
  // Initialise the Serial Port.
  Serial.begin(kBaudRate);



  Serial.println("\n...Setup complete...\n");
}

/// @brief The continuously running function for repetitive tasks.
void loop() {

}

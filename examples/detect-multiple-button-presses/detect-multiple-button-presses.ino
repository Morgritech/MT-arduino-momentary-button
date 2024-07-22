// Copyright (C) 2024 Morgritech
//
// Licensed under GNU General Public License v3.0 (GPLv3) License.
// See the LICENSE file in the project root for full license details.

/// @file detect-multiple-button-presses.ino
/// @brief Example showing how to detect multiple (short) button presses using the MT-arduino-momentary-button library.

#include <momentary_button.h>

/// @brief Button pin.
const uint8_t kButtonPin = 2;
/// @brief The pin state when the button is not pressed.
const mt::MomentaryButton::PinState kUnpressedPinState = mt::MomentaryButton::PinState::kLow;
/// @brief The Period of time in milliseconds (ms) for debouncing the button pin.
const uint16_t kButtonDebouncePeriod = 20;
/// @brief The Period in of time milliseconds (ms) allowed between multiple (short) button presses.
const uint16_t kMultiplePressPeriod = 600;

/// @brief The Momentary Button instance for the button.
mt::MomentaryButton push_button(kButtonPin, kUnpressedPinState, kButtonDebouncePeriod, kMultiplePressPeriod);
//mt::MomentaryButton push_button(kButtonPin, kUnpressedPinState, kButtonDebouncePeriod); // Default value of 500 ms is used for the multiple press period.

/// @brief The serial communication speed.
const int kBaudRate = 9600;

/// @brief The main application entry point for initialisation tasks.
void setup() {
  // Initialise the Serial Port.
  Serial.begin(kBaudRate);

  // Initialise the button pin as an input.
  pinMode(kButtonPin, INPUT);

  Serial.println("\n...Setup complete...\n");
}

/// @brief The continuously running function for repetitive tasks.
void loop() {
  uint8_t button_press_count = push_button.CountPresses(); // This must be called periodically.

  if (button_press_count > 0) {
    Serial.print("Button pressed ");
    Serial.print(button_press_count);
    Serial.println(" times");
  }
}
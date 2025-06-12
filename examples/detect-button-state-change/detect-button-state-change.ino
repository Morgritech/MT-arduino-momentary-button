// Copyright (C) 2024 Morgritech
//
// Licensed under GNU General Public License v3.0 (GPLv3) License.
// See the LICENSE file in the project root for full license details.

/// @file detect-button-state-change.ino
/// @brief Example showing how to detect button state change (press and release) using the MT-arduino-momentary-button library.

#include <momentary_button.h>

/// @brief Button pin.
constexpr uint8_t kButtonPin = 2;
/// @brief The pin state when the button is not pressed.
constexpr auto kUnpressedPinState = mt::MomentaryButton::PinState::kLow;
/// @brief The Period of time in milliseconds (ms) for debouncing the button pin.
constexpr uint16_t kButtonDebouncePeriod_ms = 20;

/// @brief The Momentary Button instance for the button.
mt::MomentaryButton push_button{kButtonPin, kUnpressedPinState, kButtonDebouncePeriod_ms};
//mt::MomentaryButton push_button{kButtonPin, kUnpressedPinState}; // Default values: debounce period = 70 ms.

/// @brief The serial communication speed.
constexpr int kBaudRate = 9600;

/// @brief The main application entry point for initialisation tasks.
void setup() {
  // Initialise the Serial Port.
  Serial.begin(kBaudRate);

  // Initialise the button pin as an input.
  pinMode(kButtonPin, INPUT);

  Serial.println(F("\n...Setup complete...\n"));
}

/// @brief The continuously running function for repetitive tasks.
void loop() {
  // Counter to keep track of each unique state change (pressed-released).
  static int counter = 0;

  // Detect state change on the button pin.
  mt::MomentaryButton::ButtonState button_state = push_button.DetectStateChange(); // This must be called repeatedly.

  if (button_state == mt::MomentaryButton::ButtonState::kPressed) {
    counter++;
    Serial.print(F("Button pressed "));
    Serial.println(counter);
  }

  if (button_state == mt::MomentaryButton::ButtonState::kReleased) {
    Serial.print(F("Button released "));
    Serial.println(counter);
  }
}
// Copyright (C) 2024 Morgritech
//
// Licensed under GNU General Public License v3.0 (GPLv3) License.
// See the LICENSE file in the project root for full license details.

/// @file detect-multiple-button-presses.ino
/// @brief Example showing how to detect multiple (short) button presses using the MT-arduino-momentary-button library.

#include <momentary_button.h>

/// @brief Button pin.
constexpr uint8_t kButtonPin = 2;
/// @brief The pin state when the button is not pressed.
constexpr auto kUnpressedPinState = mt::MomentaryButton::PinState::kLow;
/// @brief The Period of time in milliseconds (ms) for debouncing the button pin.
constexpr uint16_t kButtonDebouncePeriod_ms = 20;
/// @brief The Period in of time milliseconds (ms) allowed between multiple (short) button presses.
constexpr uint16_t kMultiplePressPeriod_ms = 600;

/// @brief The Momentary Button instance for the button.
auto push_button = mt::MomentaryButton(kButtonPin, kUnpressedPinState, kButtonDebouncePeriod_ms, kMultiplePressPeriod_ms);
//auto push_button = mt::MomentaryButton(kButtonPin, kUnpressedPinState, kButtonDebouncePeriod_ms); // Default values: multiple press period = 500 ms.

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
  // Count (short) presses on the button.
  uint8_t button_press_count = push_button.CountPresses(); // This must be called repeatedly.

  if (button_press_count > 0) {
    Serial.print(F("Button pressed "));
    Serial.print(button_press_count);
    Serial.println(F(" times"));
  }
}
// Copyright (C) 2024 Morgritech
//
// Licensed under GNU General Public License v3.0 (GPLv3) License.
// See the LICENSE file in the project root for full license details.

/// @file detect-button-press-type.ino
/// @brief Example showing how to detect short or long (press and hold) button presses using the MT-arduino-momentary-button library.

#include <momentary_button.h>

/// @brief Button pin.
constexpr uint8_t kButtonPin = 2;
/// @brief The pin state when the button is not pressed.
constexpr auto kUnpressedPinState = mt::MomentaryButton::PinState::kLow;
/// @brief The Period of time in milliseconds (ms) for debouncing the button pin.
constexpr uint16_t kButtonDebouncePeriod_ms = 20;
/// @brief The Period in of time milliseconds (ms) allowed between multiple button presses.
constexpr uint16_t kMultiplePressPeriod_ms = 600;
/// @brief The Period in of time milliseconds (ms) required for a long button press (press and hold).
constexpr uint16_t kLongPressPeriod_ms = 1200;
/// @brief The option for detecting a long press.
constexpr auto kLongPressOption = mt::MomentaryButton::LongPressOption::kDetectWhileHolding;

/// @brief The Momentary Button instance for the button.
mt::MomentaryButton push_button{kButtonPin, kUnpressedPinState, kButtonDebouncePeriod_ms, kMultiplePressPeriod_ms, kLongPressPeriod_ms};
//mt::MomentaryButton push_button{kButtonPin, kUnpressedPinState, kButtonDebouncePeriod_ms}; // Default values: multiple press period = 500 ms, long press period = 1000 ms.

/// @brief The serial communication speed.
constexpr int kBaudRate = 9600;

/// @brief The main application entry point for initialisation tasks.
void setup() {
  // Initialise the Serial Port.
  Serial.begin(kBaudRate);

  // Initialise the button pin as an input.
  pinMode(kButtonPin, INPUT);

  // Set the long press option.
  // If this is not set, the default behaviour is to detect a long press after the button is released.
  push_button.set_long_press_option(kLongPressOption);

  Serial.println(F("\n...Setup complete...\n"));
}

/// @brief The continuously running function for repetitive tasks.
void loop() {
  // Detect button press type.
  mt::MomentaryButton::PressType button_press_type = push_button.DetectPressType(); // This must be called repeatedly.

  if (button_press_type == mt::MomentaryButton::PressType::kShortPress) {
    Serial.println(F("Short press"));
  }

  if (button_press_type == mt::MomentaryButton::PressType::kLongPress) {
    Serial.println(F("Long press"));
  }
}
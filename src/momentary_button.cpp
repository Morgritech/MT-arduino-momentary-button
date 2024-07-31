// Copyright (C) 2024 Morgritech
//
// Licensed under GNU General Public License v3.0 (GPLv3) License.
// See the LICENSE file in the project root for full license details.

/// @file momentary_button.cpp
/// @brief Class to handle momentary push button actions.

#include "momentary_button.h"

#include <Arduino.h>

#include <pin_debouncer.h>

namespace mt {

MomentaryButton::MomentaryButton(uint8_t gpio_pin, PinState unpressed_pin_state, uint16_t debounce_period_ms,
                                 uint16_t multiple_press_period_ms, uint16_t long_press_period_ms)
    : button_debouncer_(gpio_pin, debounce_period_ms) {
  gpio_pin_ = gpio_pin;
  unpressed_pin_state_ = unpressed_pin_state;
  multiple_press_period_ms_ = multiple_press_period_ms; // (ms).
  long_press_period_ms_ = long_press_period_ms; // (ms).
}

MomentaryButton::~MomentaryButton() {}

MomentaryButton::ButtonState MomentaryButton::DetectStateChange() const {
  static PinDebouncer::Status debounce_status = PinDebouncer::Status::kNotStarted;
  static bool debouncing_a_press = false;

  ButtonState button_state = ButtonState::kNoChange;

  if (debounce_status == PinDebouncer::Status::kNotStarted && debouncing_a_press == false) {
    // No button press yet and/or finished debouncing button release.
    PinState pin_state = static_cast<PinState>(digitalRead(gpio_pin_));
    if (pin_state != unpressed_pin_state_) {
      // Button has been pressed.
      button_state = ButtonState::kPressed;
      debouncing_a_press = true;
      debounce_status = PinDebouncer::Status::kOngoing;
    }
  }
  else if (debounce_status == PinDebouncer::Status::kNotStarted && debouncing_a_press == true) {
    // Finished debouncing a button press.
    PinState pin_state = static_cast<PinState>(digitalRead(gpio_pin_));
    if (pin_state == unpressed_pin_state_) {
      // Button has been released.
      button_state = ButtonState::kReleased;
      debouncing_a_press = false;
      debounce_status = PinDebouncer::Status::kOngoing;
    }
  }
  
  if (debounce_status == PinDebouncer::Status::kOngoing) {
    debounce_status = button_debouncer_.DebouncePin();
  }

  return button_state;
}

MomentaryButton::PressType MomentaryButton::DetectPressType() const {
  static uint64_t reference_button_press_time_ms = millis(); // (ms).

  PressType press_type = PressType::kNotApplicable;
  ButtonState button_state = DetectStateChange();

  if (button_state == ButtonState::kPressed) {
    reference_button_press_time_ms = millis();
  }

  if (button_state == ButtonState::kReleased) {

    if ((millis() - reference_button_press_time_ms) >= long_press_period_ms_) {
      press_type = PressType::kLongPress;
    }
    else {
      press_type = PressType::kShortPress;
    }
    
    reference_button_press_time_ms = millis();
  }
  
  return press_type;
}

uint8_t MomentaryButton::CountPresses() const {
  static uint64_t reference_button_press_time_ms = millis(); // (ms).
  static uint8_t press_counter = 0;

  uint8_t press_count = 0;

  PressType press_type = DetectPressType();

  if (press_type == PressType::kShortPress) {
    
    if (press_counter == 0 || (millis() - reference_button_press_time_ms) <= multiple_press_period_ms_) {
      press_counter++;
      press_count = press_counter;
      reference_button_press_time_ms = millis();
    }
    else {
      press_counter = 0;
    }

  }
  else if ((millis() - reference_button_press_time_ms) > multiple_press_period_ms_) {
    press_counter = 0;
  }
  
  return press_count;
}

} // namespace mt

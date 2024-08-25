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

MomentaryButton::ButtonState MomentaryButton::DetectStateChange() {
  ButtonState button_state = ButtonState::kNoChange;

  if (debounce_status_ == PinDebouncer::Status::kNotStarted && debouncing_a_press_ == false) {
    // No button press yet and/or finished debouncing button release.
    PinState pin_state = static_cast<PinState>(digitalRead(gpio_pin_));
    if (pin_state != unpressed_pin_state_) {
      // Button has been pressed.
      button_state = ButtonState::kPressed;
      debouncing_a_press_ = true;
      debounce_status_ = PinDebouncer::Status::kOngoing;
    }
  }
  else if (debounce_status_ == PinDebouncer::Status::kNotStarted && debouncing_a_press_ == true) {
    // Finished debouncing a button press.
    PinState pin_state = static_cast<PinState>(digitalRead(gpio_pin_));
    if (pin_state == unpressed_pin_state_) {
      // Button has been released.
      button_state = ButtonState::kReleased;
      debouncing_a_press_ = false;
      debounce_status_ = PinDebouncer::Status::kOngoing;
    }
  }
  
  if (debounce_status_ == PinDebouncer::Status::kOngoing) {
    debounce_status_ = button_debouncer_.DebouncePin();
  }

  return button_state;
}

MomentaryButton::PressType MomentaryButton::DetectPressType() {
  PressType press_type = PressType::kNotApplicable;
  ButtonState button_state = DetectStateChange();

  if (button_state == ButtonState::kPressed) {
    reference_press_type_time_ms_ = millis();
    waiting_for_release_ = true;
  }

  if (button_state == ButtonState::kReleased) {
    if ((millis() - reference_press_type_time_ms_) >= long_press_period_ms_) {
      // Long press.
      if (long_press_option_ == LongPressOption::kDetectAfterRelease) {
        press_type = PressType::kLongPress;
      }
    }
    else {
      press_type = PressType::kShortPress;
    }
    
    waiting_for_release_ = false;
  }

  if ((waiting_for_release_ == true) && (long_press_option_ == LongPressOption::kDetectWhileHolding)) {
    if ((millis() - reference_press_type_time_ms_) >= long_press_period_ms_) {
      press_type = PressType::kLongPress;
      waiting_for_release_ = false;
    }
  }

  return press_type;
}

uint8_t MomentaryButton::CountPresses() {
  uint8_t press_count = 0;

  PressType press_type = DetectPressType();

  if (press_type == PressType::kShortPress) {
    if (press_counter_ == 0 || (millis() - reference_multiple_press_time_ms_) <= multiple_press_period_ms_) {
      press_counter_++;
      press_count = press_counter_;
      reference_multiple_press_time_ms_ = millis();
    }
    else {
      press_counter_ = 0;
    }

  }
  else if ((millis() - reference_multiple_press_time_ms_) > multiple_press_period_ms_) {
    press_counter_ = 0;
  }
  
  return press_count;
}

void MomentaryButton::set_long_press_option(LongPressOption long_press_option) {
  long_press_option_ = long_press_option;
}

} // namespace mt

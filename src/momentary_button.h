// Copyright (C) 2024 Morgritech
//
// Licensed under GNU General Public License v3.0 (GPLv3) License.
// See the LICENSE file in the project root for full license details.

/// @file momentary_button.h
/// @brief Class to handle momentary push button actions.

#ifndef MOMENTARY_BUTTON_H_
#define MOMENTARY_BUTTON_H_

#include <Arduino.h>

#include <pin_debouncer.h>

namespace mt {

/// @brief The Momentary Button class.
class MomentaryButton {
 public:

  /// @brief Enum of button press types.
  enum class PressType {
    kNotApplicable = 0,
    kShortPress,
    kLongPress,
  };

  /// @brief Enum of GPIO pin states.
  enum class PinState {
    kLow = 0,
    kHigh,
  };

  /// @brief Enum of button states.
  enum class ButtonState {
    kReleased = 0,
    kPressed,
    kNoChange,
  };

  /// @brief Construct a Button object.
  /// @param gpio_pin The GPIO input pin assigned to the button.
  /// @param unpressed_pin_state The pin state when the button is not pressed.
  /// @param debounce_period The period of time (ms) allowed for pin debouncing.
  /// @param multiple_press_period The period of time (ms) allowed between multiple button presses.
  /// @param long_press_period The period of time (ms) required for a long button press (press and hold).
  MomentaryButton(uint8_t gpio_pin, PinState unpressed_pin_state = PinState::kLow, uint16_t debounce_period = 70,
                  uint16_t multiple_press_period = 500, uint16_t long_press_period = 1000);

  /// @brief Destroy the Button object.
  ~MomentaryButton();

  /// @brief Check if the button has changed state, and what state it has changed to.
  /// @return The button state at the time of checking (released, pressed, or no change).
  ButtonState DetectStateChange() const;

  /// @brief Check if a button has been pressed, and what type of press occurred.
  /// @return The type of button press at the time of checking.
  PressType DetectPressType() const;

  /// @brief Count the number of (short) button presses.
  /// @return The number of (short) button presses.
  uint8_t CountPresses() const;

 private:

  /// @brief The GPIO input pin assigned to the button.
  uint8_t gpio_pin_;
  /// @brief The pin state when the button is not pressed.
  PinState unpressed_pin_state_;
  /// @brief The period of time (ms) allowed between multiple button presses.
  uint16_t multiple_press_period_;
  /// @brief The period of time (ms) required for a long button press (press and hold).
  uint16_t long_press_period_;
  /// @brief A pin debouncer object to handle button debouncing.
  PinDebouncer button_debouncer_;
};

} // namespace mt

#endif // MOMENTARY_BUTTON_H_
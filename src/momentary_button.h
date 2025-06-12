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

  /// @brief Enum of GPIO pin states.
  enum class PinState : uint8_t {
    kLow = 0,
    kHigh,
  };

  /// @brief Enum of button states.
  enum class ButtonState : uint8_t {
    kReleased = 0,
    kPressed,
    kNoChange,
  };

  /// @brief Enum of button press types.
  enum class PressType : uint8_t {
    kNotApplicable = 0,
    kShortPress,
    kLongPress,
  };

  /// @brief Enum of long press options.
  enum class LongPressOption : uint8_t {
    kDetectWhileHolding = 1,
    kDetectAfterRelease,
  };

  /// @brief Construct a Button object.
  /// @param gpio_pin The GPIO input pin assigned to the button.
  /// @param unpressed_pin_state The pin state when the button is not pressed.
  /// @param debounce_period_ms The period of time (ms) allowed for pin debouncing.
  /// @param multiple_press_period_ms The period of time (ms) allowed between multiple button presses.
  /// @param long_press_period_ms The period of time (ms) required for a long button press (press and hold).
  MomentaryButton(uint16_t gpio_pin, PinState unpressed_pin_state = PinState::kLow, uint16_t debounce_period_ms = 70,
                  uint16_t multiple_press_period_ms = 500, uint16_t long_press_period_ms = 1000);

  /// @brief Destroy the Button object.
  ~MomentaryButton();

  /// @brief Check if the button has changed state, and what state it has changed to.
  /// @return The button state at the time of checking.
  ButtonState DetectStateChange(); ///< This must be called repeatedly.

  /// @brief Check if a button has been pressed, and what type of press occurred.
  /// @return The type of button press at the time of checking.
  PressType DetectPressType(); ///< This must be called repeatedly.

  /// @brief Count the number of (short) button presses.
  /// @return The number of (short) button presses.
  uint8_t CountPresses(); ///< This must be called repeatedly.

  /// @brief Set the option for detecting a long press.
  /// @param long_press_option The long press option.
  void set_long_press_option(LongPressOption long_press_option);

 private:

  /// @brief The GPIO input pin assigned to the button.
  uint16_t gpio_pin_;
  /// @brief The pin state when the button is not pressed.
  PinState unpressed_pin_state_;
  /// @brief The period of time (ms) allowed between multiple button presses.
  uint16_t multiple_press_period_ms_;
  /// @brief The period of time (ms) required for a long button press (press and hold).
  uint16_t long_press_period_ms_;
  /// @brief The option for long press detection.
  LongPressOption long_press_option_ = LongPressOption::kDetectAfterRelease;
  /// @brief A pin debouncer object to handle button debouncing.
  PinDebouncer button_debouncer_;
  /// @brief The status of the debounce operation during state change detection.
  PinDebouncer::Status debounce_status_ = PinDebouncer::Status::kNotStarted;
  /// @brief Flag to keep track of when the debounce of a button press is ongoing during state change detection.
  bool debouncing_a_press_ = false;
  /// @brief Flag to keep track of when a button has been pressed during press type detection.
  bool waiting_for_release_ = false;
  /// @brief Reference time (ms) for detecting a button press type.
  uint64_t reference_press_type_time_ms_ = 0;
  /// @brief Reference time (ms) for detecting multiple button presses.
  uint64_t reference_multiple_press_time_ms_ = 0;
  /// @brief Counter to keep track of multiple button presses.
  uint8_t press_counter_ = 0;
};

} // namespace mt

#endif // MOMENTARY_BUTTON_H_
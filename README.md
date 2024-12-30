# MT-arduino-momentary-button

[![Static check](https://github.com/Morgritech/MT-arduino-momentary-button/actions/workflows/static-check.yaml/badge.svg)](https://github.com/Morgritech/MT-arduino-momentary-button/actions/workflows/static-check.yaml) [![Build examples](https://github.com/Morgritech/MT-arduino-momentary-button/actions/workflows/build-examples.yaml/badge.svg)](https://github.com/Morgritech/MT-arduino-momentary-button/actions/workflows/build-examples.yaml)

Momentary button library for the Arduino platform, to detect button state change (press/release), short/long presses and multiple presses.

This library implements non-blocking functions to detect button actions, ensuring each action is debounced to filter out input noise on the button pin. The library can handle multiple buttons.

Button actions that can be detected include:

- State change i.e., button press and release.
- Short press and long press (press and hold).
- Multiple (short) presses; obtained via a press counter. This will count each short press that occurs within an allowed period of time (set using the library).

Other features:

- Long presses can be detected either upon release of the button, or, while the button is being held and the set period has elapsed.

See the [examples](examples) folder for how to get started on using the library.

The library requires the [MT-arduino-pin-debouncer](https://github.com/Morgritech/MT-arduino-pin-debouncer) library.

This library can be installed via the Arduino Library Manager.

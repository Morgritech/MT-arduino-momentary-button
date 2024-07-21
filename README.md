# MT-arduino-momentary-button

Momentary button library for the Arduino platform, to detect button state change (press/release), short/long presses and to count the number of presses.

This library implements non-blocking functions to detect button actions. The library can handle multiple buttons.

Button actions that can be detected include:

- State change i.e., button press and release.
- Short press and long press (press and hold).
- Multiple (short) presses; obtained via a press counter.

See the "examples" folder for how to get started on using the library.

The library requires the [MT-arduino-pin-debouncer](https://github.com/Morgritech/MT-arduino-pin-debouncer) library.

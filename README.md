# stepper-motor

Arduino library to accurately control a stepper motor using angles in degree.

## Example

```cpp
using Stepper = StepperMotor::Driver;

Stepper motor({2, 3, 4, 5});

void loop() {
    motor.turn(-90);
    delay(1000);
    motor.turnTo(0);
    delay(3000);
}
```

## Documentation

The [api documentation] can be generated using `doxygen`.

## Licence

This library by Klemens Schölhorn is licenced under the terms of the GPLv3.

[api documentation]: https://hwpl.github.io/stepper-motor/

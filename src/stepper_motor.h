#ifndef _STEPPER_MOTOR
#define _STEPPER_MOTOR

#include "std/initializer_list.h"

namespace StepperMotor {

/// %Driver for an 8-step stepper motor
///
/// ## Example
///
/// ```
/// using Stepper = StepperMotor::Driver;
///
/// Stepper motor({2, 3, 4, 5});
///
/// void loop() {
///     motor.turn(-90);
///     delay(1000);
///     motor.turnTo(0);
///     delay(3000);
/// }
/// ```
class Driver {
    public:
        /// Create a new driver instance using the given pins.
        ///
        /// \param pins **Exactly** 4 pins.
        Driver(std::initializer_list<uint8_t> pins);

        /// Relative turn
        ///
        /// This turns the motor the given number of degrees in the direction
        /// given by the sign (positive = turn right). Supports turns larger
        /// than one complete turn (360°).
        ///
        /// \param degree The number of degree to turn the motor.
        void turn(int16_t degree);

        /// Absolute turn
        ///
        /// Turn the motor to the given angle. Always uses the shortest path to
        /// the requested angle and even works after relative turns.
        ///
        /// \param target_angle The target angle in degree.
        void turnTo(uint16_t target_angle);

        /// Set the steps needed for one complete rotation.
        ///
        /// This defaults to 510, which is a common value for stepper motors
        /// found in arduino starter kits.
        ///
        /// \param steps The steps per rotation.
        void setStepsPerRotation(uint16_t steps);

    private:
        uint8_t pins[4] = {-1, -1, -1, -1};
        uint16_t steps_per_rotation = 510;
        uint16_t current_step_position = 0;
        uint16_t current_degree_position = 0;

        /// Turn the motor one step forward (right).
        void stepForward();
        /// Turn the motor one step backward (left).
        void stepBackward();

        /// Set the pins to the given sub-step (first pin = LSB).
        void executeStep(uint8_t step);
        /// Set all pins to low.
        ///
        /// This *must* be called after the rotation is finished, because
        /// otherwise some pins stay active and might cause an overheating.
        void resetPins();
};

} // namespace StepMotor

#endif // _STEPPER_MOTOR

#ifndef _STEPPER_MOTOR
#define _STEPPER_MOTOR

#include "std/initializer_list.h"

namespace StepperMotor {

class Driver {
    public:
        Driver(std::initializer_list<uint8_t> pins);

        void turn(int16_t degree);
        void turnTo(uint16_t targetDegree);

        void setStepsPerRotation(uint16_t steps);

    private:
        uint8_t pins[4];
        uint16_t steps_per_rotation = 510;
        uint16_t current_step_position = 0;
        uint16_t current_degree_position = 0;

        void stepForward();
        void stepBackward();

        void executeStep(uint8_t step);
        void resetPins();
};

} // namespace StepMotor

#endif // _STEPPER_MOTOR

#ifndef _STEPPER_MOTOR
#define _STEPPER_MOTOR

#include "std/initializer_list.h"

namespace HWP {
namespace StepperMotor {

const static uint16_t STEPS_PER_ROTATION = 510;

class Driver {
    public:
        Driver(std::initializer_list<uint8_t> pins);

        void turn(int16_t degree);
        void turnTo(uint16_t targetDegree);

    private:
        uint8_t pins[4];
        uint16_t current_step_position = 0;
        uint16_t current_degree_position = 0;

        void stepForward();
        void stepBackward();

        void executeStep(uint8_t step);
        void resetPins();
};

} // namespace StepMotor
} // namespace HWP

#endif // _STEPPER_MOTOR

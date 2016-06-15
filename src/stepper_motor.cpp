#include "stepper_motor.h"

// Sequence used to turn the stepper motor one step
const PROGMEM uint8_t STEP_SEQUENCE[] = {
    0b00000001,
    0b00000011,
    0b00000010,
    0b00000110,
    0b00000100,
    0b00001100,
    0b00001000,
    0b00001001,
};

StepperMotor::Driver::Driver(std::initializer_list<uint8_t> pins) {
    size_t i = 0;
    for(uint8_t pin : pins) {
        if(i >= 4) break;
        this->pins[i++] = pin;
        pinMode(pin, OUTPUT);
    }
}

void StepperMotor::Driver::turn(int16_t degree) {
    if(degree < 0) {
        uint8_t rotations = -degree / 360;
        degree = -degree % 360;

        for(uint16_t steps = 0; steps < rotations * STEPS_PER_ROTATION; ++steps) {
            stepBackward();
        }
        turnTo(((int16_t)current_degree_position - degree + 360) % 360);
    } else {
        uint8_t rotations = degree / 360;
        degree = degree % 360;

        for(uint16_t steps = 0; steps < rotations * STEPS_PER_ROTATION; ++steps) {
            stepForward();
        }
        turnTo(((int16_t)current_degree_position + degree) % 360);
    }
}

void StepperMotor::Driver::turnTo(uint16_t targetDegree) {
    targetDegree = targetDegree % 360;
    uint16_t target_step_position = ((uint32_t)targetDegree * STEPS_PER_ROTATION / 360) % STEPS_PER_ROTATION;

    while(target_step_position != current_step_position) {
        if(current_step_position > target_step_position && current_step_position - target_step_position < STEPS_PER_ROTATION / 2 ||
           current_step_position < target_step_position && target_step_position - current_step_position > STEPS_PER_ROTATION / 2) {
            stepBackward();
        } else {
            stepForward();
        }
    }

    current_degree_position = targetDegree;
    resetPins();
}

void StepperMotor::Driver::stepForward() {
    current_step_position = (current_step_position + 1) % STEPS_PER_ROTATION;
    for(size_t i = 0; i < 8; ++i) {
        executeStep(pgm_read_byte_near(STEP_SEQUENCE + i));
        delayMicroseconds(800);
    }
}

void StepperMotor::Driver::stepBackward() {
    current_step_position = (current_step_position + STEPS_PER_ROTATION - 1) % STEPS_PER_ROTATION;
    for(size_t i = 0; i < 8; ++i) {
        executeStep(pgm_read_byte_near(STEP_SEQUENCE + (7 - i)));
        delayMicroseconds(800);
    }
}

void StepperMotor::Driver::executeStep(uint8_t step) {
    size_t j = 0;
    for(uint8_t pin : pins) {
        digitalWrite(pin, (step & 1 << j++) != 0);
    }
}

void StepperMotor::Driver::resetPins() {
    for(uint8_t pin : pins) {
        digitalWrite(pin, false);
    }
}

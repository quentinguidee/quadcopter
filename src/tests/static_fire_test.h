#ifndef STATIC_FIRE_TEST_H
#define STATIC_FIRE_TEST_H

#include "../drone.h"

class StaticFireTest
{
private:
    enum State
    {
        running,
        stopped
    };

    Drone &drone;

    unsigned long currentTimer;
    unsigned long startTimer;
    unsigned long period;

    int8_t currentMotor;
    State currentState;

public:
    StaticFireTest(Drone &drone);
    ~StaticFireTest() {}

    void tick();

    void startup(int8_t currentMotor);
    void shutdown(int8_t currentMotor);
};

#endif /* STATIC_FIRE_TEST_H */

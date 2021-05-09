#ifndef TIMER_H
#define TIMER_H

class Timer
{
private:
    unsigned long startTime;

public:
    Timer() {}
    ~Timer() {}

    void start();

    bool exceeded(int delay);
};

#endif /* TIMER_H */

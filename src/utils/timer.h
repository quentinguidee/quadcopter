#ifndef TIMER_H
#define TIMER_H

class Timer
{
private:
    unsigned long resetTime;

public:
    Timer() {}
    ~Timer() {}

    void reset();

    bool exceeded(int delay);
};

#endif /* TIMER_H */

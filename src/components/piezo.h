#ifndef PIEZO_H
#define PIEZO_H

class Piezo
{
private:
    uint8_t pin;

public:
    Piezo(uint8_t pin);
    ~Piezo() {}
};

#endif /* PIEZO_H */

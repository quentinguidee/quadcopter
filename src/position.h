#ifndef POSITION_H
#define POSITION_H

class Position
{
private:
public:
    Position() {}
    ~Position() {}

    float getX();
    float getY();
    float getZ();

    float getAngleX();
    float getAngleY();
    float getAngleZ();

    float getAccelerationX();
    float getAccelerationY();
    float getAccelerationZ();

    float getAngleAccelerationX();
    float getAngleAccelerationY();
    float getAngleAccelerationZ();
};

#endif /* POSITION_H */

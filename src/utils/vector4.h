#ifndef VECTOR4_H
#define VECTOR4_H

template <typename T>
struct Vector4
{
    T a, b, c, d;

    Vector4(T a, T b, T c, T d) :
        a(a), b(b), c(c), d(d) {}
};

#endif /* VECTOR4_H */

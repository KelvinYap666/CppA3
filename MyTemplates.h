#ifndef MYTEMPLATES_H
#define MYTEMPLATES_H

#include <cmath>

template <typename T>
double scalar_difference(T arg1, T arg2){
    return abs(arg1.getScalarValue() - arg2.getScalarValue());
}

template <typename T>
bool equals(T arg1, T arg2){
    return arg1 == arg2;
}



#endif
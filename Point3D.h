#ifndef POINT3D_H
#define POINT3D_H

#include <cmath>
#include <iostream>
#include <sstream>

#include "Point2D.h"

using namespace std;

class Point3D : public Point2D {
protected:
    int z;  // Z coordinate for 3D points

public:
    // Constructor to initialize x, y from Point2D, and z from Point3D
    Point3D(int x, int y, int z);

    // Getter and setter for Z coordinate
    int getZ() const;
    void setZ(int z);

    //void setDistFrOrigin to calculate the distance for 3D points
    void setDistFrOrigin();
    friend ostream& operator<<(ostream&os, const Point3D& p);
};

#endif

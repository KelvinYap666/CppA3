#ifndef POINT2D_H
#define POINT2D_H

#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

class Point2D {
    protected:
        int x, y;
        double distFrOrigin;
        void setDistFrOrigin();
    public:
        Point2D(int x, int y);
        int getX() const;
        int getY() const;
        double getScalarValue() const;
        
        void setX(int newX);
        void setY(int newY);
        bool operator<(const Point2D& other) const;
        bool operator>(const Point2D& other) const;
        bool operator==(const Point2D& other) const;

        friend ostream& operator<<(ostream&os, const Point2D& p);
};

#endif
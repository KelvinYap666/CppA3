#ifndef LINE2D_H
#define LINE2D_H

#include "Point2D.h"
#include <cmath>

class Line2D {
private:
    Point2D pt1, pt2;

protected:
    double length;
    virtual void setLength();

public:
    Line2D(Point2D pt1, Point2D pt2);
    Point2D getPt1() const;
    Point2D getPt2() const;
    virtual double getScalarValue() const;
    void setPt1(Point2D);
    void setPt2(Point2D);
    bool operator==(const Line2D &) const;
    bool operator<(const Line2D&) const;

    //friend
    friend ostream& operator<<(ostream&os, const Line2D& line);

};

#endif

#ifndef LINE3D_H
#define LINE3D_H

#include "Line2D.h"
#include "Point3D.h"
#include <cmath>

class Line3D : public Line2D {
protected:
    void setLength() override;  // Override setLength from Line2D
private:
    Point3D pt1, pt2;           // 3D points for the line
public:
    Line3D(const Point3D& pt1, const Point3D& pt2);  // Use const ref
    Point3D getPt1() const;      // Const-correct getter
    Point3D getPt2() const;      // Const-correct getter
    void setPt1(const Point3D& pt1);  // Use const ref
    void setPt2(const Point3D& pt2);  // Use const ref
    double getScalarValue() const override;  // Override to return length correctly

    friend ostream& operator<<(ostream&os, const Line3D& line);

};

#endif

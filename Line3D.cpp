#include "Line3D.h"

// Constructor to initialize Line3D with two 3D points
Line3D::Line3D(const Point3D& pt1, const Point3D& pt2)
    : Line2D(pt1, pt2), pt1(pt1), pt2(pt2) {  // Use Point3D directly
    setLength();
}

// Getter for pt1 (const-correct)
Point3D Line3D::getPt1() const {
    return pt1;
}

// Getter for pt2 (const-correct)
Point3D Line3D::getPt2() const {
    return pt2;
}

// Setter for pt1
void Line3D::setPt1(const Point3D& pt1) {
    this->pt1 = pt1;
    Line2D::setPt1(pt1);  // Use pt1 directly
    setLength();
}

// Setter for pt2
void Line3D::setPt2(const Point3D& pt2) {
    this->pt2 = pt2;
    Line2D::setPt2(pt2);  // Use pt2 directly
    setLength();
}

// Override getScalarValue() to return 3D length
double Line3D::getScalarValue() const {
    return length;
}

//set length
void Line3D::setLength() {
    // Get the differences in x, y, and z
    double x_diff = static_cast<double>(pt1.getX()) - static_cast<double>(pt2.getX());
    double y_diff = static_cast<double>(pt1.getY()) - static_cast<double>(pt2.getY());
    double z_diff = static_cast<double>(pt1.getZ()) - static_cast<double>(pt2.getZ());
    
    // Calculate the 3D distance using the distance formula
    length = sqrt((x_diff * x_diff) + (y_diff * y_diff) + (z_diff * z_diff));
}

//output
ostream& operator<<(ostream& os, const Line3D& line) {
    os << " ["  << setw(4) << line.getPt1().getX() << ", "
       << setw(4) << line.getPt1().getY() << ", "
       << setw(4) << line.getPt1().getZ() << "]   "
       << "[" << setw(4) << line.getPt2().getX() << ", "
       << setw(4) << line.getPt2().getY() << ", "
       << setw(4) << line.getPt2().getZ() << "]"
       << "   " << fixed << setprecision(3) << line.getScalarValue();
    return os;
}
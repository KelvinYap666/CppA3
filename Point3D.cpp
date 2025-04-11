#include "Point3D.h"

// Constructor to initialize x, y from Point2D, and z from Point3D
Point3D::Point3D(int x, int y, int z) : Point2D(x, y), z(z) {
    setDistFrOrigin();  // Call to set the distance from the origin
}

// Override the method to set the distance from origin for 3D points
void Point3D::setDistFrOrigin() {
    distFrOrigin = sqrt((x * x) + (y * y) + (z * z));  // Use the 3D distance formula
}

// Getter for z-coordinate
int Point3D::getZ() const {
    return z;
}

// Setter for z-coordinate
void Point3D::setZ(int z) {
    this->z = z;
    setDistFrOrigin();  // Recalculate the distance from the origin when z changes
}

//output
ostream& operator<<(ostream& os, const Point3D& p) {
    os << "  [" << setw(4) << p.getX() << ", "
                << setw(4) << p.getY() << ", "
                << setw(4) << p.getZ() << "]   "
                << fixed << setprecision(3) << p.getScalarValue();
    return os;
}

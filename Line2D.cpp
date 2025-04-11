#include "Line2D.h"

// Constructor
Line2D::Line2D(Point2D pt1, Point2D pt2) : pt1(pt1), pt2(pt2) {
    setLength();
}

Point2D Line2D::getPt1() const{
    return pt1;
}

Point2D Line2D::getPt2() const {
    return pt2;
}

double Line2D::getScalarValue() const{
    return length;
}

void Line2D::setPt1(Point2D pt1) {
    this->pt1 = pt1;
    setLength();
}

void Line2D::setPt2(Point2D pt2) {
    this->pt2 = pt2;
    setLength();
}

void Line2D::setLength() {
    int x_diff = pt1.getX() - pt2.getX();
    int y_diff = pt1.getY() - pt2.getY();
    length = sqrt((x_diff * x_diff) + (y_diff * y_diff));
}

// Equality operator
bool Line2D::operator==(const Line2D& line) const{
    return (pt1 == line.pt1) && (pt2 == line.pt2);
}

// Less-than operator for sorting
bool Line2D::operator<(const Line2D& other) const {
    // Compare based on the X-coordinate of pt1 first
    if (pt1.getX() != other.pt1.getX()) {
        return pt1.getX() < other.pt1.getX();
    }
    // If X coordinates are the same, compare based on the Y-coordinate of pt1
    if (pt1.getY() != other.pt1.getY()) {
        return pt1.getY() < other.pt1.getY();
    }
    // If both X and Y of pt1 are the same, compare pt2 (secondary comparison, optional)
    if (pt2.getX() != other.pt2.getX()) {
        return pt2.getX() < other.pt2.getX();
    }
    return pt2.getY() < other.pt2.getY();
}

//output
ostream& operator<<(ostream& os, const Line2D& line) {
    os << "  ["<< setw(4) << line.getPt1().getX() << ", "
                 << setw(4) << line.getPt1().getY() << "]   "
                 << "["<< setw(4) << line.getPt2().getX() << ", "
                 << setw(4) << line.getPt2().getY() << "]"
                 << "   " << fixed << setprecision(3) << line.getScalarValue();
    return os;
}


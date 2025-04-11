#include "Point2D.h"

void Point2D::setDistFrOrigin() {
    distFrOrigin = sqrt((x * x) + (y * y));
}

Point2D::Point2D(int x, int y) : x(x), y(y) {
    setDistFrOrigin(); // Ensure the distance from origin is set
}

int Point2D::getX() const {
    return x;
}

int Point2D::getY() const {
    return y;
}

double Point2D::getScalarValue() const {
    return distFrOrigin;
}
void Point2D::setX(int newX) {
    x = newX;
    setDistFrOrigin(); 
}

void Point2D::setY(int newY) {
    y = newY;
    setDistFrOrigin();
}
bool Point2D::operator<(const Point2D& other) const{
    if (x == other.x) {
        return y < other.y;
    }
    return x < other.x;
}

bool Point2D::operator>(const Point2D& other) const{
    if (x == other.x) {
        return y > other.y;
    }
    return x > other.x;
}

bool Point2D::operator==(const Point2D& other) const{
    return x == other.x && y == other.y;
}

//output
ostream& operator<<(ostream& os, const Point2D& p) {
    os << "  ["<< setw(4) << p.getX() << ", " 
       << setw(4) << p.getY() << "]   " 
       << fixed << setprecision(3) << p.getScalarValue();
    return os;
}

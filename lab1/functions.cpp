#include "functions.h"
#include <cmath>
#include <stdexcept>

Square::Square(double s) {
    setSide(s);
}

void Square::setSide(double s) {
    if (s <= 0) {
        throw std::invalid_argument("Square side must be greater than zero!");
    }
    side = s;
}

double Square::getSide() const {
    return side;
}

double Square::calculateArea() const {
    return side * side;
}

double Square::calculatePerimeter() const {
    return 4 * side;
}

double Square::calculateDiagonal() const {
    return side * std::sqrt(2.0);
}

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

class Square {
private:
    double side;

public:
    Square(double s);
    void setSide(double s);
    double getSide() const;

    double calculateArea() const;
    double calculatePerimeter() const;
    double calculateDiagonal() const;
};

#endif // FUNCTIONS_H

#ifndef SHAPE_H
#define SHAPE_H

#include <string>
#include <vector>
#include <cmath>

class Shape {
protected:
    float area_ = 0.0f;
    float perimeter_ = 0.0f;

public:
    virtual ~Shape() {}
    virtual void area() = 0;
    virtual void perimeter() = 0;
    virtual std::string name() const = 0;
    virtual std::vector<float> get_par() const = 0;

    float get_area() const { return area_; }
    float get_perimeter() const { return perimeter_; }
};

class Rectangle : public Shape {
private:
    float length_;
    float width_;

public:
    Rectangle(float l, float w) : length_(l), width_(w) {}

    void area() override {
        area_ = length_ * width_;
    }

    void perimeter() override {
        perimeter_ = 2.0f * (length_ + width_);
    }

    std::string name() const override {
        return "Прямоугольник";
    }

    std::vector<float> get_par() const override {
        return {length_, width_};
    }
};

class Triangle : public Shape {
private:
    float a_;
    float b_;
    float c_;

public:
    Triangle(float a, float b, float c) : a_(a), b_(b), c_(c) {}

    void area() override {
        float p = (a_ + b_ + c_) / 2.0f;
        area_ = std::sqrt(p * (p - a_) * (p - b_) * (p - c_));
    }

    void perimeter() override {
        perimeter_ = a_ + b_ + c_;
    }

    std::string name() const override {
        return "Треугольник";
    }

    std::vector<float> get_par() const override {
        return {a_, b_, c_};
    }
};

class Circle : public Shape {
private:
    float radius_;

public:
    Circle(float r) : radius_(r) {}

    void area() override {
        area_ = 3.14159265f * radius_ * radius_;
    }

    void perimeter() override {
        perimeter_ = 2.0f * 3.14159265f * radius_;
    }

    std::string name() const override {
        return "Окружность";
    }

    std::vector<float> get_par() const override {
        return {radius_};
    }
};

#endif // SHAPE_H

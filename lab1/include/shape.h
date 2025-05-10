#ifndef SHAPE_H
#define SHAPE_H


class Shape {
public:
    virtual ~Shape() {}

};

class Circle : public Shape {};

class Parallelogram : public Shape {};

class Rectangle : public Shape {};

class Rhombus : public Shape {};

class Sector : public Shape {};

class Square : public Shape {};

class Trapezoid : public Shape {};

class Triangle : public Shape {};

#endif // SHAPE_H

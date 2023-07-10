//
// Created by 이철용 on 2022/07/04.
//

#ifndef PRACTICE053_RECTANGLE_H
#define PRACTICE053_RECTANGLE_H

#include "Point.h"

class Rectangle {
public:
    //implements the constructor
    Rectangle(double x1, double y1, double x2, double y2)
    : leftTop(x1, y1), rightBottom(x2, y2) {}
    double area() {
        double width = abs(rightBottom.getX() - leftTop.getX());
        double height = abs(rightBottom.getY() - leftTop.getY());
        return width * height;
    };
private:
    Point leftTop, rightBottom;
};

/*class Point {
public:
    Point(double x=0, double y=0) : x(x), y(y) {}
    double norm() const {return sqrt(x*x + y*y);};
    double getX() const {return x;}
    double getY() const {return y;}
private:
    const double x, y;
};*/

#endif //PRACTICE053_RECTANGLE_H

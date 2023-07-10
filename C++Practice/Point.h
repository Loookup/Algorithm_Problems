//
// Created by 이철용 on 2022/07/04.
//

#ifndef PRACTICE053_POINT_H
#define PRACTICE053_POINT_H

#include <cmath>


class Point {
public:
    Point(double x=0, double y=0) : x(x), y(y) {}
    double norm() const {return sqrt(x*x + y*y);};
    double getX() const {return x;}
    double getY() const {return y;}
private:
    const double x, y;
};

#endif //PRACTICE053_POINT_H

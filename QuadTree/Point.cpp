#include "Point.h"

Point::Point(){
}

Point::Point(double x, double y) : x(x), y(y){
}

bool Point::operator==(const Point& point){
    if (this->x == point.x && this->y == point.y){
        return true;
    } else {
        return false;
    }
}


/* 
 * File:   Polygon.cpp
 * Author: marcin
 * 
 * Created on November 29, 2012, 1:25 PM
 */

#include <cmath>
#include <climits>
#include <limits>
#include <list>

#include "Polygon.h"
#include "Visualization.h"
#include "geometry.h"
#include <vector>

Polygon::Polygon(int size) : index(0), len(size) {
    points = new Point*[size];
}

Polygon::Polygon(std::list<Point*>* points_list) : index(0), len(points_list->size()){
    points = new Point*[len];
    for (std::list<Point*>::iterator it = points_list->begin(); it != points_list->end(); ++it){
        *this += *it;
    }
}

Point* Polygon::operator[](int index) const {
    if (index > len) {
        std::cout << "Error! Polygon index out of range!\n";
        throw len;
    }
    return points[index];
}

void Polygon::operator+=(Point*& p) {
    points[index] = p;
    ++index;
    if (index > len) {
        std::cout << "Error! Polygon overflow!\n";
        throw len;
    }
}

std::ostream& operator<<(std::ostream& out, const Polygon& polygon) {
    if (polygon.size() < 3) {
        return out;
    }
    for (int it = 0; it < polygon.size(); ++it){
        drawline(out, polygon[it], polygon[(it+1)%polygon.size()], black);
    }
    return out;
}

int Polygon::size() const {
    return len;
}

Polygon::~Polygon() {
    delete points;
}

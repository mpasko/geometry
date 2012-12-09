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
    if (polygon.length() < 3) {
        return out;
    }
    for (int it = 0; it < polygon.length(); ++it){
        drawline(out, polygon[it], polygon[(it+1)%polygon.length()], black);
    }
    return out;
}

int Polygon::length() const {
    return len;
}

Polygon::~Polygon() {
    delete points;
}

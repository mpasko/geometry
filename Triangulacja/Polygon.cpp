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
#include "General_exception.h"
#include <vector>

Polygon::Polygon(int size) : index(0), vertices_number(size) {
    points = new Point*[vertices_number];
}

Polygon::Polygon(std::list<Point*>* points_list) : index(0), vertices_number(points_list->size()){
    points = new Point*[vertices_number];
    for (std::list<Point*>::iterator it = points_list->begin(); it != points_list->end(); ++it){
        *this += *it;
    }
}

Point* Polygon::operator[](int index) const {
    if (index > vertices_number) {
        throw General_exception("Error! Polygon index out of range!\n");
    }
    return points[index];
}

void Polygon::operator+=(Point*& p) {
    points[index] = p;
    ++index;
    if (index > vertices_number) {
        throw General_exception("Error! Polygon overflow!\n");
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
    return vertices_number;
}

Polygon::~Polygon() {
    delete points;
}

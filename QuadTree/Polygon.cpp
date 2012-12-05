/* 
 * File:   Polygon.cpp
 * Author: marcin
 * 
 * Created on November 29, 2012, 1:25 PM
 */

#include <cmath>
#include <climits>
#include <limits>

#include "Polygon.h"
#include "Visualization.h"
#include "geometry.h"
#include <vector>

Polygon::Polygon(int size) : index(0), len(size) {
//    coord_x = new double[size];
//    coord_y = new double[size];
//    flushtable = new FlushTable<Point > ((size+1) * 10);
    points = new Point*[size];
}

Point* Polygon::operator[](int index) const {
    if (index > len) {
        std::cout << "Error! Polygon index out of range!\n";
        throw len;
    }
    return points[index];
//    Point* p = new Point(coord_x[index], coord_y[index]);
//    (*flushtable) += p;
//    return p;
}

void Polygon::operator+=(Point* p) {
    points[index] = p;
    ++index;
    if (index > len) {
        std::cout << "Error! Polygon overflow!\n";
        throw len;
    }
//    std::vector<Point*>::iterator it = points->end();
//    coord_x[index] = p->x;
//    coord_y[index] = p->y;
//    ++index;
    
}

std::ostream& operator<<(std::ostream& out, const Polygon& polygon) {
    if (polygon.length() < 3) {
        return out;
    }
    for (int it = 0; it < polygon.len; ++it){
        drawline(out, polygon[it], polygon[it%polygon.len], black);
    }
    return out;
}

int Polygon::length() const {
    return len;
}

double Polygon::get_nearest_vertex_distance(Point* vertex){
    double min_distance = std::numeric_limits<double>::max();
    double distance;
    Point* plot_vertex;
    for (int i = 0; i < length(); ++i) {
        plot_vertex = (*this)[i];
        if (plot_vertex != vertex){
            distance = pitagoras(*plot_vertex, *vertex);
            if (distance < min_distance){
                min_distance = distance;
            }
        }
    }
    return min_distance;
}

Polygon::~Polygon() {
    delete points;
}

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

Polygon::Polygon(int size) : index(0), len(size) {
    coord_x = new double[size];
    coord_y = new double[size];
    flushtable = new FlushTable<Point > ((size+1) * 10);
}

Point* Polygon::operator[](int index) const {
    Point* p = new Point(coord_x[index], coord_y[index]);
    (*flushtable) += p;
    return p;
}

void Polygon::operator+=(Point* p) {
    coord_x[index] = p->x;
    coord_y[index] = p->y;
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
    for (int i = 0; i < polygon.length() - 1; ++i) {
        drawline(out, polygon[i]->x, polygon[i]->y, polygon[i + 1]->x, polygon[i + 1]->y, black);
    }
    drawline(out, polygon[polygon.length() - 1]->x, polygon[polygon.length() - 1]->y, polygon[0]->x, polygon[0]->y, black);
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
    delete coord_x;
    delete coord_y;
    delete flushtable;
}

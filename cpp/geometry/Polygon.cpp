/* 
 * File:   Polygon.cpp
 * Author: marcin
 * 
 * Created on November 29, 2012, 1:25 PM
 */

#include "Polygon.h"

Polygon::Polygon(int size){
    coord_x = new float[size];
    coord_y = new float[size];
    flushtable = new FlushTable<Point>(size*10);
}
    
Point* Polygon::operator[](int index){
    Point* p = new Point(coord_x[index],coord_y[index]);
    (*flushtable) += p;
    return p;
}
    
Polygon::~Polygon(){
    delete coord_x;
    delete coord_y;
    delete flushtable;
}

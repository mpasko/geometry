/* 
 * File:   Polygon.h
 * Author: marcin
 *
 * Created on November 29, 2012, 1:25 PM
 */

#ifndef POLYGON_H
#define	POLYGON_H

#include "Point.h"
#include "FlushTable.h"
#include <vector>
#include <iostream>
#include <fstream>

class Polygon{   
    Point** points;
    int index;
    int len;
public:
    Polygon(int size);
    
    Point* operator[](int index) const;
    
    void operator+=(Point*& p);
    
    friend std::ostream& operator<<(std::ostream& out, const Polygon& tree);
    
    int length() const;
    
    virtual ~Polygon();
};

#endif	/* POLYGON_H */


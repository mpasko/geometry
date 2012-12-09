/* 
 * File:   MergeTable.h
 * Author: marcin
 *
 * Created on December 4, 2012, 11:32 AM
 */

#ifndef MERGETABLE_H
#define	MERGETABLE_H

#include "Point.h"

class MergeTable{
public:
    Point ** reference;
    double * x;
    double * y;
    int max;
    
    MergeTable(int sz);
    
    Point* get(double x, double y);
    
    void merge(Point ** p, Point ** d);
    
    Point* set(Point* p);
    
    ~MergeTable();
};

#define eps 0.000001

#endif	/* MERGETABLE_H */


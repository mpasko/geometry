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
#include <list>
#include <iostream>
#include <fstream>

/** \brief Klasa reprezentująca wielokąt */
class Polygon{   
    Point** points;
    int index;
    int len;
public:
    Polygon(int size);
    Polygon(std::list<Point*>* points_list);
    
    /**
    * Zwraca punkt należący do wielokąta.
    */
    Point* operator[](int index) const;
    
    /**
    * Dodaje punkt do wielokąta.
    */
    void operator+=(Point*& p);
    
    /**
    * Wypisuje sformatowaną reprezentację do strumienia.
    */
    friend std::ostream& operator<<(std::ostream& out, const Polygon& tree);
    
    /** Zwraca rozmiar wielokąta jako liczbę punktów */
    int length() const;
    
    virtual ~Polygon();
};

#endif	/* POLYGON_H */


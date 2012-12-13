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
    /** Wierzchołki*/
    Point** points;
    int index;
    int len;
public:
    /**
     * Kostruktor wielokąta
     * @param size liczba wierzchołków
     */
    Polygon(int size);
    /**
     * Kostruktor wielokąta nad zbiorem wierzchołków
     * @param points_list wierzchołki
     */
    Polygon(std::list<Point*>* points_list);
    
    /**
    * Zwraca wierzchołek  wielokąta.
    */
    Point* operator[](int index) const;
    
    /**
    * Dodaje wierzchołek do wielokąta.
    */
    void operator+=(Point*& p);
    
    /**
    * Wypisuje sformatowaną reprezentację do strumienia. Wielokąt jest wypisywany
    * w formacie obsługiwanym przez graficzny symulator.
    */
    friend std::ostream& operator<<(std::ostream& out, const Polygon& tree);
    
    /** Zwraca liczbę wierzchołków wielokąta */
    int size() const;
    
    virtual ~Polygon();
};

#endif	/* POLYGON_H */


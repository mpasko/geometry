/* 
 * File:   MergeTable.h
 * Author: marcin
 *
 * Created on December 4, 2012, 11:32 AM
 */

#ifndef MERGETABLE_H
#define	MERGETABLE_H

#include "Point.h"

/** \brief Klasa służąca do indeksowania wierzchołków do scalania */
class MergeTable{
public:
    Point ** reference;
    double * x;
    double * y;
    int max;
    
    /** Konstruktor
    * @param sz rozmiar
    */
    MergeTable(int sz);
    
    /** Zwraca wskaźnik na punkt o podanych współrzędnych
    * @param x odcięta
    * @param y rzędna
    */
    Point* get(double x, double y);
    
    /** Scala dwa wskaźniki na punkty 
    * @param p referencja na pierwszy wskaźnik
    * @param q referencja na drugi wskaźnik
    */
    void merge(Point ** p, Point ** d);
    
    /** Wstawia punkt do indeksu */
    Point* set(Point* p);
    
    ~MergeTable();
};

#define eps 0.000001

#endif	/* MERGETABLE_H */


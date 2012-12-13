/*
 * \brief metody do triangulacji siatki QUadTree
 */

/* 
 * File:   triangulation.h
 * Author: marcin
 *
 * Created on December 3, 2012, 11:38 AM
 */

#ifndef TRIANGULATION_H
#define	TRIANGULATION_H

#include "QuadTree.h"
#include "Polygon.h"
#include <iostream>
#include <fstream>

#define METHOD_1

/** \brief Dokonuje triangulacji siatki QuadTree
* @param out strumień wyjściowy
* @param qt struktura QuadTree do triangulacji
*/
void triangulate(std::ostream&out, QuadTree*qt);
/** \brief Dokonuje triangulacji siatki QuadTree
* @param out strumień wyjściowy
* @param qt struktura QuadTree do triangulacji
* @param color kolor w którym zostaną narysowane krawędzie triangulacji
*/
void triangulate(std::ostream&out, QuadTree*qt, const char* color);

#endif	/* TRIANGULATION_H */


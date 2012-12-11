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

void triangulate(std::ostream&out, QuadTree*qt);
void triangulate(std::ostream&out, QuadTree*qt, const char* color);

#endif	/* TRIANGULATION_H */


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

void triangulate(std::ostream&out, Polygon* p, QuadTree*qt);

#endif	/* TRIANGULATION_H */


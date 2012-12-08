/* 
 * File:   Visualization.h
 * Author: marcin
 *
 * Created on November 29, 2012, 12:18 PM
 */

#ifndef VISUALIZATION_H
#define	VISUALIZATION_H

#define PASKO

#include "Point.h"
#include <iostream>
#include <fstream>

#define red "ff0000"
#define green "00ff00"
#define blue "0000ff"
#define black "000000"

void drawpoint(std::ostream& out, const float x1, const float y1, const char*color);

void drawline(std::ostream& out, const float x1, const float y1, const float x2, const float y2, const char*color);

void drawline(std::ostream& out, const Point*p1, const char*color);

void drawline(std::ostream& out, const Point*p1, const Point*p2, const char*color);

void step(std::ostream& out);

#endif	/* VISUALIZATION_H */


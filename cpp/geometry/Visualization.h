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

int seq = 0;

#ifdef PASKO

char* red = "ff0000";
char* green = "00ff00";
char* blue = "0000ff";

void drawpoint(std::ostream& out, float x1, float y1, char*color){
    out << x1 <<", "<< y1 <<", "<< color << ", " << seq << ", " << seq << std::endl;
    ++seq;
}

void drawline(std::ostream& out, float x1, float y1, float x2, float y2, char*color){
    out << x1 <<", "<< y1 <<", "<< color << ", " << seq << ", " << seq << std::endl;
    out << x2 <<", "<< y2 <<", "<< color << ", " << seq << ", " << seq << std::endl;
    ++seq;
}

#else

char* red = "RED";
char* green = "GREEN";
char* blue = "BLUE";

void drawline(std::ostream& out, float x1,float y1, float x2, float y2, char*color){
    
}

void drawpoint(std::ostream& out, float x1, float y1, char*color){
    
}

#endif

void drawline(std::ostream& out, Point*p1, char*color){
    drawpoint(out,p1->x,p1->y,color);
}

void drawline(std::ostream& out, Point*p1, Point*p2, char*color){
    drawline(out,p1->x,p1->y,p2->x,p2->y,color);
}

#endif	/* VISUALIZATION_H */


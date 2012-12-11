/* 
 * File:   Segment.h
 * Author: W3a?ciciel
 *
 * Created on 21 listopad 2012, 01:37
 */

#ifndef SEGMENT_H
#define	SEGMENT_H

#include "Point.h"

class Segment {
public:
    Point a;
    Point b;

    Segment();
    Segment(Point a, Point b);
    Segment(double x1, double y1, double x2, double y2);

    bool operator==(const Segment& segment);
private:

};

#endif	/* SEGMENT_H */


#ifndef GPOINT_H
#define	GPOINT_H

#include "GFigure.h"
#include "Point.h"

#include <stdio.h>

using namespace std;

class GPoint : public GFigure, public Point {
public:
    GPoint();
    GPoint(double x, double y);

    GPoint(Point&);
    bool operator==(const GPoint& g_point);

    string to_sim_format();
};

#endif	/* GPOINT_H */


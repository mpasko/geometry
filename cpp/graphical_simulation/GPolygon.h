#include <vector>

#include "GPoint.h"
#include "GFigure.h"

#ifndef POLYGON_H
#define	POLYGON_H

using namespace std;

class GPolygon : public GFigure {
public:
    vector<GPoint> vertices;
//    pair<GPoint, GPoint> getNeighbours(vector<GPoint>::iterator point_it);
    bool isMonotonic();
    string to_sim_format();
private:
};

#endif	/* POLYGON_H */


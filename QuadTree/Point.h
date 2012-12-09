#ifndef POINT_H
#define	POINT_H

//#include "QuadTree.h"


class Point {
public:
    double x;
    double y;
    class QuadTree* node;

    Point();
    Point(double x, double y);
    bool operator==(const Point& point);

private:

};

#endif	/* POINT_H */


#ifndef POINT_H
#define	POINT_H

class Point {
public:
    double x;
    double y;

    Point();
    Point(double x, double y);
    bool operator==(const Point& point);

private:

};

#endif	/* POINT_H */


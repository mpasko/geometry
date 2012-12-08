#ifndef MATHEMATICS_H
#define	MATHEMATICS_H

#include "Point.h"
#include <exception>
#include <list>
#include <limits>

#define EPSILON 0.000000000001

double pitagoras(Point point1, Point point2);
double pitagoras(double x1, double y1, double x2, double y2);

double orientation2d(Point pointA, Point pointB, Point pointC);
double orientation2D(Point pointA, Point pointB, Point pointC);

bool are_points_equal(const Point& a, const Point& b);

double get_nearest_point_distance(Point* vertex, std::list<Point*> points);

#endif	/* MATHEMATICS_H */


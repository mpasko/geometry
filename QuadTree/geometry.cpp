#include <cmath>
#include <malloc.h>
#include "geometry.h"

double pitagoras(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

double pitagoras(Point point1, Point point2) {
    return pitagoras(point1.x, point1.y, point2.x, point2.y);
}

double distance_from_segment(const Point& a, const Point&  b, const Point& p){
    return fabs((b.x - a.x)*(a.y - p.y) -  (a.x - p.x)*(b.y - a.y))/pitagoras(a, b);
}

double orientation2d(Point pointA, Point pointB, Point pointC) {
    return (pointA.x - pointC.x) * (pointB.y - pointC.y) - (pointA.y - pointC.y) * (pointB.x - pointC.x);
}

double orientation2D(Point pointA, Point pointB, Point pointC){
    return (pointA.x * pointB.y + pointA.y * pointC.x + pointB.x * pointC.y
            - pointA.x * pointC.y - pointA.y * pointB.x - pointB.y * pointC.x);
}

double get_aspect_ratio(const Point& a, const Point& b, const Point& c){
    double dist_ab = pitagoras(a, b);
    double dist_ac = pitagoras(a, c);
    double dist_bc = pitagoras(b ,c);
    
    if (dist_ab > dist_ac){
        if (dist_ab > dist_bc){
            return dist_ab/distance_from_segment(a, b, c);
        } else {
            return dist_bc/distance_from_segment(b, c, a);
        }
    } else {
        if (dist_ac > dist_bc){
            return dist_ac/distance_from_segment(a, c, b);
        } else {
            return dist_bc/distance_from_segment(b, c, a);
        }
    }
}

bool are_points_equal(const Point& a, const Point& b){
    return fabs(a.x - b.x) < EPSILON && fabs(a.y - b.y) < EPSILON;
}

double get_nearest_point_distance(Point* vertex, std::list<Point*> points){
    double min_distance = std::numeric_limits<double>::max();
    double distance;
    Point* some_point;
    for (std::list<Point*>::iterator it = points.begin(); it != points.end(); ++it){
        some_point = *it;
        if (fabs(some_point->x - vertex->x) > EPSILON || fabs(some_point->y - vertex->y) > EPSILON) {
            distance = pitagoras(*some_point, *vertex);
            if (distance < min_distance){
                min_distance = distance;
            }
        }
    }
    return min_distance;
}

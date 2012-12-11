#include <cmath>
#include <cstdlib>

#include "random_generation.h"

using namespace std;


list<Point* > generate_points_inside_rectangle(double xrange, double yrange, int points_number) {
    double x, y;
    double x0 = - xrange / 2.0, y0 = - yrange / 2.0;

    list<Point* > points_list;

    srand(44);
    for (int i = 0; i < points_number; ++i) {
        x = x0 + rand() / (double) RAND_MAX * xrange;
        y = y0 + rand() / (double) RAND_MAX * yrange;
        Point* point = new Point(x, y);
        points_list.push_back(point);
    }

    return points_list;
}

list<Point* > generate_points_inside_circle(double r, int points_number) {
    list<Point* > points_vector;

    srand(44);
    double r_rand;
    double angle_rand;
    double m2pi = M_PI * 2;
    for (int i = 0; i < points_number; ++i) {
        r_rand = rand() / (double) RAND_MAX * r;
        angle_rand = (double) ((double) rand() / (double) RAND_MAX) * m2pi;
        Point* point = new Point(r_rand * cos(angle_rand), r_rand * sin(angle_rand));
        points_vector.push_back(point);
    }

    return points_vector;
}
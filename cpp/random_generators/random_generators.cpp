#include <math.h>
#include <list>
#include <stdlib.h>

#include <list>
#include <iostream>
#include <string>
#include <string.h>
#include "GPoint.h"
#include "Figures_factory.h"
#include "geometry.h"
#include "random_generators.h"

using namespace std;

void place_point_on_segment(double x2, double y2, double x1, double y1, double segment_length, double distance, GPoint& point) {
    point.x = x1 + distance * (x2 - x1) / segment_length;
    point.y = y1 + distance * (y2 - y1) / segment_length;
}

list<GPoint > generate_points_inside_rectangle(double x0, double x1, double y0, double y1, int n, Figures_factory& factory) {
    double xrange = x1 - x0;
    double yrange = y1 - y0;
    double x, y;

    list<GPoint > points_vector;

    srand(44);
    for (int i = 0; i < n; ++i) {
        x = x0 + rand() / (double) RAND_MAX * xrange;
        y = y0 + rand() / (double) RAND_MAX * yrange;
        GPoint point = factory.create_point(x, y);
        points_vector.push_back(point);
    }

    return points_vector;
}

list<GPoint > generate_points_on_circle(double x, double y, double r, int n, Figures_factory& factory) {
    list<GPoint > points_vector;

    srand(44);
    double angle_rand;
    double m2pi = M_PI * 2;
    for (int i = 0; i < n; ++i) {
        angle_rand = (double) ((double) rand() / (double) RAND_MAX) * m2pi;
        GPoint point = factory.create_point(x + r * cos(angle_rand), y + r * sin(angle_rand));
        points_vector.push_back(point);
    }

    return points_vector;
}

list<GPoint > generate_points_inside_circle(double x, double y, double r, int n, Figures_factory& factory) {
    list<GPoint > points_vector;

    srand(44);
    double r_rand;
    double angle_rand;
    double m2pi = M_PI * 2;
    for (int i = 0; i < n; ++i) {
        r_rand = rand() / (double) RAND_MAX * r;
        angle_rand = (double) ((double) rand() / (double) RAND_MAX) * m2pi;
        GPoint point = factory.create_point(x + r_rand * cos(angle_rand), y + r_rand * sin(angle_rand));
        points_vector.push_back(point);
    }

    return points_vector;
}

list<GPoint > generate_points_in_polar_coordinates(double x, double y, double r0, double r1, double fi0, double fi1, int n, Figures_factory& factory) {
    list<GPoint > points_vector;

    srand(44);
    double r_rand;
    double angle_rand;
    double r_range = r1 - r0;
    double fi_range = fi1 - fi0;
    double m2pi = M_PI * 2;
    for (int i = 0; i < n; ++i) {
        r_rand = r0 + rand() / (double) RAND_MAX * r_range;
        angle_rand = fi0 + rand() / (double) RAND_MAX * fi_range;
        GPoint point = factory.create_point(x + r_rand * cos(angle_rand), y + r_rand * sin(angle_rand));
        points_vector.push_back(point);
    }

    return points_vector;
}

list<GPoint > generate_points_on_polygonal(double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3, int n, Figures_factory& factory) {
    list<GPoint > points_vector;

    double a = pitagoras(x0, y0, x1, y1);
    double b = pitagoras(x1, y1, x2, y2);
    double c = pitagoras(x2, y2, x3, y3);
    double d = pitagoras(x3, y3, x0, y0);

    double perimeter = a + b + c + d;

    srand(44);
    double distance;
    for (int i = 0; i < n - 4; ++i) {
        distance = rand() / (double) RAND_MAX * perimeter;
        GPoint point = factory.create_point();
        if (distance <= a) {
            place_point_on_segment(x1, y1, x0, y0, a, distance, point);
        } else {
            if (distance <= a + b) {
                place_point_on_segment(x2, y2, x1, y1, b, distance - b, point);
            } else {
                if (distance <= a + b + c) {
                    place_point_on_segment(x3, y3, x2, y2, c, distance - b - a, point);
                } else {
                    place_point_on_segment(x0, y0, x3, y3, d, distance - c - b - a, point);
                }
            }
        }
        points_vector.push_back(point);
    }

    points_vector.push_back(factory.create_point(x0, y0));
    points_vector.push_back(factory.create_point(x1, y1));
    points_vector.push_back(factory.create_point(x2, y2));
    points_vector.push_back(factory.create_point(x3, y3));

    return points_vector;
}

list<GPoint > generate_points_on_square_diagonals_and_2_sides(double a, int n1, int n2, int n3, int n4, Figures_factory& factory) {
    list<GPoint > points_vector;
    srand(44);

    double x, y;
    for (int i = 0; i < n1; ++i) {
        x = rand() / (double) RAND_MAX * a;
        GPoint point = factory.create_point(x, 0);
        points_vector.push_back(point);
    }
    for (int i = 0; i < n2; ++i) {
        y = rand() / (double) RAND_MAX * a;
        GPoint point = factory.create_point(0, y);
        points_vector.push_back(point);
    }

    for (int i = 0; i < n3; ++i) {
        x = rand() / (double) RAND_MAX * a;
        y = x;
        GPoint point = factory.create_point(x, y);
        points_vector.push_back(point);
    }

    for (int i = 0; i < n4; ++i) {
        x = rand() / (double) RAND_MAX * a;
        y = a - x;
        GPoint point = factory.create_point(x, y);
        points_vector.push_back(point);
    }

    points_vector.push_back(factory.create_point(a, a));
    points_vector.push_back(factory.create_point(0, a));
    points_vector.push_back(factory.create_point(0, 0));
    points_vector.push_back(factory.create_point(a, 0));

    return points_vector;
}

list<GPoint> generate_points_on_line(double a, double b, double x0, double xn, int n, Figures_factory& factory) {
    double range = xn - x0;
    double x, y;

    list<GPoint > points_vector;

    srand(44);
    for (int i = 0; i < n; ++i) {
        x = x0 + rand()/(double)RAND_MAX * range;
        y = a * x + b;
        GPoint point = factory.create_point(x, y);
        points_vector.push_back(point);
    }

    return points_vector;
}

list<GSegment> generate_segments_inside_rectangle(double x0, double y0, double width, double height, int n, Figures_factory& factory) {
    double x1, y1, x2, y2;

    list<GSegment > segments_vector;

    srand(44);
    for (int i = 0; i < n; ++i) {
        x1 = x0 + rand() / (double) RAND_MAX * width;
        y1 = y0 + rand() / (double) RAND_MAX * height;
        x2 = x0 + rand() / (double) RAND_MAX * width;
        y2 = y0 + rand() / (double) RAND_MAX * height;
        GSegment segment = factory.create_segment(x1, y1, x2, y2);
        segments_vector.push_back(segment);
    }

    return segments_vector;
}
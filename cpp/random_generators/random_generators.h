#ifndef CONVEX_HULL_RANDOM_H
#define	CONVEX_HULL_RANDOM_H

#include "Figures_factory.h"
#include <list>

    list<GPoint > generate_points_inside_rectangle(double x0, double x1, double y0, double y1, int n, Figures_factory& factory);
    list<GPoint > generate_points_on_circle(double x, double y, double r, int n, Figures_factory& factory);
    list<GPoint > generate_points_inside_circle(double x, double y, double r, int n, Figures_factory& factory);
    list<GPoint > generate_points_in_polar_coordinates(double x, double y, double r0, double r1, double fi0, double fi1, int n, Figures_factory& factory);
    list<GPoint > generate_points_on_polygonal(double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3, int n, Figures_factory& factory);
    list<GPoint > generate_points_on_square_diagonals_and_2_sides(double a, int n1, int n2, int n3, int n4, Figures_factory& factory);
    list<GPoint > generate_points_on_line(double a, double b, double x0, double xn, int n, Figures_factory& factory);
    list<GSegment> generate_segments_inside_rectangle(double x0, double y0, double width, double height, int n, Figures_factory& factory);

#endif	/* CONVEX_HULL_RANDOM_H */


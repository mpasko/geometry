/*
 * \brief metody do operacji geometrycznych
 */

#ifndef MATHEMATICS_H
#define	MATHEMATICS_H

#include "Point.h"
#include <exception>
#include <list>
#include <limits>

#define EPSILON 0.000000000001

/**
 * Liczy odległosć euklidesową miedzy dwoma punktami
 * @param point1 pierwszy punkt
 * @param point2 drugi punkt
 * @return odległosć w metryce euklidesowej
 */
double pitagoras(Point point1, Point point2);

/**
 * Liczy odległosć euklidesową miedzy dwoma punktami
 * @param x1 współrzędna x pierwszego punktu
 * @param y1 współrzędna y pierwszego punktu
 * @param x2 współrzędna x drugiego punktu
 * @param y2 współrzędna y drugiego punktu
 * @return odległosć w metryce euklidesowej
 */
double pitagoras(double x1, double y1, double x2, double y2);

double orientation2d(Point pointA, Point pointB, Point pointC);
double orientation2D(Point pointA, Point pointB, Point pointC);

bool are_points_equal(const Point& a, const Point& b);

/**
 * Zwraca odległość między danym punktem a najbliżesz do niego punktem ze zbioru
 * punktów. Czas działania : O(n), n - lczba punktów w zbiorze.
 * @param vertex punkt dla którego szukamy odległosći
 * @param points zbiór punktów
 * @return najbliższa odległość
 */
double get_nearest_point_distance(Point* vertex, std::list<Point*> points);

#endif	/* MATHEMATICS_H */


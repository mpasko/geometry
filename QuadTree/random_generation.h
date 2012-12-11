#include <list>
#include "Point.h"

/**
 * Tworzy losowe punkty na obszarze prostokąta o środu w punkcie (0,0)
 * @param xrange dłogość poziomej krawędzi
 * @param yrange długość pionowej krawedzi
 * @param points_number liczba punktów do wylosowania
 * @return wylosowane punkty
 */
std::list<Point* > generate_points_inside_rectangle(double xrange, double yrange, int points_number);

/**
 * Tworzy losowe punkty na obszarze koła o środu w punkcie (0,0)
 * @param r promień koła
 * @param points_number liczba punktów do wylosowania
 * @return wylosowane punkty
 */
std::list<Point* > generate_points_inside_circle(double r, int points_number);


#ifndef POINT_H
#define	POINT_H

//#include "QuadTree.h"

/** \brief Klasa reprezentująca punkt */
class Point {
public:
    /** x-owa współrzędna punktu*/
    double x;
    /** y-owa współrzędna punktu*/
    double y;
    /**
     * Wskazanie na węzeł drzewa quadtree w którym znajduje się węzeł.
     * Wskaźnik zawsze odnosi się do kwadratu znajdującego się najniżej w hierarchii
     * quadtree, zatem zawsze wskazuje na liść drzewa przechowywujący aktualnie punkt
     */
    class QuadTree* node;

    /**
     * Konstruktor domyślny
     */
    Point();
    
    /**
     * Konstruktor punktu o zadanych współrzędnych
     * @param x x-owa współrzędna punktu
     * @param y y-owa współrzędna punktu
     */
    Point(double x, double y);

    /**
     * Porównanie punktów po wartościach współrzędnych
     * @param point punkt do porównania
     * @return <i>true</i> wtedy i tylko wtedy, gdy wszyskie współrzędne punktów
     * są równe
     */
    bool operator==(const Point& point);
};

#endif	/* POINT_H */


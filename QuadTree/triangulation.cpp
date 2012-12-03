
#include "triangulation.h"
#include "QuadTree.h"
#include "Visualization.h"

Point* QuadTree::getCrossing(Point*a, Point* b){
    //TODO
    return NULL;
}

QuadTree* getNeighbour(int direction){
    //TODO
    return NULL;
}

#ifdef METHOD_1

/* 
 * Tutaj sobie odfiltrujemy zbedne punkty rzeby oszczedzic CPU
 * Narazie niech zostanie -Avoid premature optimisation!
 */

Polygon* filter(Polygon* p, QuadTree *qt){
    return p;
}

void triangulate(std::ostream&out, Polygon* p, QuadTree*qt){
    if(qt->isLeaf()){
        float hw = qt->half;
        if(qt->chunk == NULL){
            drawline(out, qt->center->x, qt->center->y, qt->center->x+hw, qt->center->y+hw, red);
            drawline(out, qt->center->x, qt->center->y, qt->center->x-hw, qt->center->y+hw, red);
            drawline(out, qt->center->x, qt->center->y, qt->center->x+hw, qt->center->y-hw, red);
            drawline(out, qt->center->x, qt->center->y, qt->center->x-hw, qt->center->y-hw, red);
        }else{
            //TODO
        }
    }else{
        Polygon * p2 = filter(p,qt);
        triangulate(out, p2, qt->NE);
        triangulate(out, p2, qt->NW);
        triangulate(out, p2, qt->SE);
        triangulate(out, p2, qt->SW);
    }
}

#else

#endif


#include "triangulation.h"
#include "QuadTree.h"
#include "Visualization.h"

Point* QuadTree::getCrossing(Point*a, Point* b){
    //TODO
    return NULL;
}

QuadTree* QuadTree::getNeighbour(int direction){
    //TODO
    if(parent == NULL){
        return NULL;
    }
    switch(direction){
        case DIRECTION_N:
            
            break;
        case DIRECTION_W:
            
            break;
        case DIRECTION_S:
            
            break;
        case DIRECTION_E:
            
            break;
        case DIRECTION_NW:
            
            break;
        case DIRECTION_NE:
            
            break;
        case DIRECTION_SW:
            
            break;
        case DIRECTION_SE:
            
            break;
            
    }
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
 //       float hw = qt->half;
 //       if(qt->chunk == NULL){
            drawline(out, qt->getSteiner(), qt->getNECorner(), red);
            drawline(out, qt->getSteiner(), qt->getNWCorner(), red);
            drawline(out, qt->getSteiner(), qt->getSECorner(), red);
            drawline(out, qt->getSteiner(), qt->getSWCorner(), red);
 //       }else{
 //           //TODO
 //       }
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

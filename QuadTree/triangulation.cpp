
#include "triangulation.h"
#include "QuadTree.h"
#include "Visualization.h"

Point* QuadTree::getCrossing(Point*a, Point* b){
    //TODO
    return NULL;
}


QuadTree* QuadTree::getNeighbour(Direction direction){
    //TODO
    if(parent == NULL){
        return NULL;
    }
    switch(direction){
        case Dir_N:
            
            break;
        case Dir_W:
            
            break;
        case Dir_S:
            
            break;
        case Dir_E:
            
            break;
        case Dir_NW:
            
            break;
        case Dir_NE:
            
            break;
        case Dir_SW:
            
            break;
        case Dir_SE:
            
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
        triangulate(out, p2, qt->NEChild);
        triangulate(out, p2, qt->NWChild);
        triangulate(out, p2, qt->SEChild);
        triangulate(out, p2, qt->SWChild);
    }
}

#else

#endif

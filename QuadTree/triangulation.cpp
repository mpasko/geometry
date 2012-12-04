
#include "QuadTree.h"
#include "Visualization.h"
#include "Point.h"
#include "triangulation.h"

Point* QuadTree::getCrossing(Point*a, Point* b) {
    //TODO
    return NULL;
}

/* To jest zle! *x/
QuadTree* QuadTree::slideDown(Direction direction, QuadTree* source) {
    if ((depth == source->depth) || (isLeaf())) {
        return this;
    } else {
        QuadTree * new_res = NULL;
        switch (direction) {
            case Dir_NW:
                if (source->parent_region == Diag_NW) {
                    new_res = SEChild;
                } else if (source->parent_region == Diag_SW) {
                    new_res = NEChild;
                } else if (source->parent_region == Diag_NE) {
                    new_res = SWChild;
                }
                break;
            case Dir_NE:
                if (source->parent_region == Diag_NE) {
                    new_res = SWChild;
                } else if (source->parent_region == Diag_SE) {
                    new_res = NWChild;
                } else if (source->parent_region == Diag_NW) {
                    new_res = SEChild;
                }
                break;
            case Dir_SW:
                if (source->parent_region == Diag_SW) {
                    new_res = NEChild;
                } else if (source->parent_region == Diag_NW) {
                    new_res = SEChild;
                } else if (source->parent_region == Diag_SE) {
                    new_res = NWChild;
                }
                break;
            case Dir_SE:
                if (source->parent_region == Diag_SE) {
                    new_res = NWChild;
                } else if (source->parent_region == Diag_SW) {
                    new_res = NEChild;
                } else if (source->parent_region == Diag_NE) {
                    new_res = SWChild;
                }
                break;
            case Dir_N:
                if (source->parent_region == Diag_NW) {
                    new_res = SWChild;
                } else if (source->parent_region == Diag_NE) {
                    new_res = SEChild;
                }
                break;
            case Dir_S:
                if (source->parent_region == Diag_SW) {
                    new_res = NWChild;
                } else if (source->parent_region == Diag_SE) {
                    new_res = NEChild;
                }
                break;
            case Dir_E:
                if (source->parent_region == Diag_NE) {
                    new_res = NWChild;
                } else if (source->parent_region == Diag_SE) {
                    new_res = SWChild;
                }
                break;
            case Dir_W:
                if (source->parent_region == Diag_NW) {
                    new_res = NEChild;
                } else if (source->parent_region == Diag_SW) {
                    new_res = SEChild;
                }
                break;
        }
        return new_res->slideDown(direction, source);
    }
}
/x* x */ 
 
/* header *x/
QuadTree* QuadTree::getChildContainingCoord(PerpendicularDir side, double value) {
/x* header */

QuadTree* QuadTree::slideDown(Direction direction, QuadTree* source) {
    if ((depth == source->depth) || (isLeaf())) {
        return this;
    } else {
        QuadTree * new_res = NULL;
        //double minx = center->x-half;
        //double maxx = center->x+half;
        double miny = center->y-half;
        double maxy = center->y+half;
        double src_h = source->half;
        double src_y = source->center->y;
        double src_x = source->center->x;
        switch (direction) {
            case Dir_NW:
                if(src_y > miny){
                    new_res = getChildContainingCoord(Per_E,src_y+src_h);
                }else{
                    new_res = getChildContainingCoord(Per_S,src_x-src_h);
                }
                break;
            case Dir_NE:
                if(src_y > miny){
                    new_res = getChildContainingCoord(Per_W,src_y+src_h);
                }else{
                    new_res = getChildContainingCoord(Per_S,src_x+src_h);
                }
                break;
            case Dir_SW:
                if(src_y < maxy){
                    new_res = getChildContainingCoord(Per_E,src_y-src_h);
                }else{
                    new_res = getChildContainingCoord(Per_N,src_x-src_h);
                }
                break;
            case Dir_SE:
                if(src_y < maxy){
                    new_res = getChildContainingCoord(Per_W,src_y-src_h);
                }else{
                    new_res = getChildContainingCoord(Per_N,src_x+src_h);
                }
                break;
            case Dir_N:
                new_res = getChildContainingCoord(Per_S,src_x);
                break;
            case Dir_S:
                new_res = getChildContainingCoord(Per_N,src_x);
                break;
            case Dir_E:
                new_res = getChildContainingCoord(Per_W,src_y);
                break;
            case Dir_W:
                new_res = getChildContainingCoord(Per_E,src_y);
                break;
        }
        if(new_res == NULL){
            return this;
        }else{
            return new_res->slideDown(direction, source);
        }
    }
}
  
QuadTree* QuadTree::getNeighbour(Direction direction, QuadTree* source) {
    if (parent == NULL) {
        return NULL;
    }
    QuadTree* parent_neigh;
    switch (direction) {
        case Dir_N:
            if (parent_region == Diag_SE) {
                parent_neigh = parent->NEChild;
            } else if (parent_region == Diag_SW) {
                parent_neigh = parent->NWChild;
            } else {
                parent_neigh = parent->getNeighbour(direction, source);
            }
            break;
        case Dir_W:
            if (parent_region == Diag_SE) {
                parent_neigh = parent->SWChild;
            } else if (parent_region == Diag_NE) {
                parent_neigh = parent->NWChild;
            } else {
                parent_neigh = parent->getNeighbour(direction, source);
            }
            break;
        case Dir_S:
            if (parent_region == Diag_NE) {
                parent_neigh = parent->SEChild;
            } else if (parent_region == Diag_NW) {
                parent_neigh = parent->SWChild;
            } else {
                parent_neigh = parent->getNeighbour(direction, source);
            }
            break;
        case Dir_E:
            if (parent_region == Diag_SW) {
                parent_neigh = parent->SEChild;
            } else if (parent_region == Diag_NW) {
                parent_neigh = parent->NEChild;
            } else {
                parent_neigh = parent->getNeighbour(direction, source);
            }
            break;
        case Dir_NW:
            if (parent_region == Diag_SE) {
                parent_neigh = parent->NWChild;
            } else if (parent_region == Diag_SW) {
                parent_neigh = parent->getNeighbour(Dir_W, source);
            } else if (parent_region == Diag_NE) {
                parent_neigh = parent->getNeighbour(Dir_N, source);
            } else {
                parent_neigh = parent->getNeighbour(direction, source);
            }
            break;
        case Dir_NE:
            if (parent_region == Diag_SW) {
                parent_neigh = parent->NEChild;
            } else if (parent_region == Diag_NW) {
                parent_neigh = parent->getNeighbour(Dir_N, source);
            } else if (parent_region == Diag_SE) {
                parent_neigh = parent->getNeighbour(Dir_E, source);
            } else {
                parent_neigh = parent->getNeighbour(direction, source);
            }
            break;
        case Dir_SW:
            if (parent_region == Diag_NE) {
                parent_neigh = parent->SWChild;
            } else if (parent_region == Diag_NW) {
                parent_neigh = parent->getNeighbour(Dir_W, source);
            } else if (parent_region == Diag_SE) {
                parent_neigh = parent->getNeighbour(Dir_S, source);
            } else {
                parent_neigh = parent->getNeighbour(direction, source);
            }
            break;
        case Dir_SE:
            if (parent_region == Diag_NW) {
                parent_neigh = parent->SEChild;
            } else if (parent_region == Diag_SW) {
                parent_neigh = parent->getNeighbour(Dir_S, source);
            } else if (parent_region == Diag_NE) {
                parent_neigh = parent->getNeighbour(Dir_E, source);
            } else {
                parent_neigh = parent->getNeighbour(direction, source);
            }
            break;
    }
    if (parent_neigh == NULL) {
        return NULL;
    } else {
        return parent_neigh->slideDown(direction, source);
    }
}

QuadTree* QuadTree::getNeighbour(Direction direction) {
    return getNeighbour(direction, this);
}


#ifdef METHOD_1

/* 
 * Tutaj sobie odfiltrujemy zbedne punkty rzeby oszczedzic CPU
 * Narazie niech zostanie -Avoid premature optimisation!
 */

Polygon* filter(Polygon* p, QuadTree *qt) {
    return p;
}

void triangulate(std::ostream&out, Polygon* p, QuadTree*qt) {
    if (qt->isLeaf()) {
        //       float hw = qt->half;
        //       if(qt->chunk == NULL){

        Point * c;
        QuadTree* ENeigh = qt->getNeighbour(Dir_E);
        QuadTree* WNeigh = qt->getNeighbour(Dir_W);
        QuadTree* SNeigh = qt->getNeighbour(Dir_S);
        QuadTree* NNeigh = qt->getNeighbour(Dir_N);

        int count = 0;

        bool is_e = (ENeigh != NULL) && (!ENeigh->isLeaf());
        bool is_w = (WNeigh != NULL) && (!WNeigh->isLeaf());
        bool is_s = (SNeigh != NULL) && (!SNeigh->isLeaf());
        bool is_n = (NNeigh != NULL) && (!NNeigh->isLeaf());

        if (is_e) {
            ++count;
        }
        if (is_w) {
            ++count;
        }
        if (is_s) {
            ++count;
        }
        if (is_n) {
            ++count;
        }

        if (count == 1) {
            if (is_e) {
                c = qt->ECorner;
                drawline(out, qt->getNWCorner(), c, green);
                drawline(out, qt->getSWCorner(), c, green);
            } else if (is_w) {
                c = qt->WCorner;
                drawline(out, qt->getNECorner(), c, green);
                drawline(out, qt->getSECorner(), c, green);
            } else if (is_s) {
                c = qt->SCorner;
                drawline(out, qt->getNWCorner(), c, green);
                drawline(out, qt->getNECorner(), c, green);
            } else if (is_n) {
                c = qt->NCorner;
                drawline(out, qt->getSWCorner(), c, green);
                drawline(out, qt->getSECorner(), c, green);
            }
        } else if (count == 0) {
            
            drawline(out, qt->getNWCorner(), qt->getSECorner(), green);
            
        } else {

            if (is_e) {
                c = qt->ECorner;
                drawline(out, qt->getSteiner(), c, green);
                delete c;
            }
            if (is_w) {
                c = qt->WCorner;
                drawline(out, qt->getSteiner(), c, green);
                delete c;
            }
            if (is_s) {
                c = qt->SCorner;
                drawline(out, qt->getSteiner(), c, green);
                delete c;
            }
            if (is_n) {
                c = qt->NCorner;
                drawline(out, qt->getSteiner(), c, green);
                delete c;
            }

            drawline(out, qt->getSteiner(), qt->getNECorner(), green);
            drawline(out, qt->getSteiner(), qt->getNWCorner(), green);
            drawline(out, qt->getSteiner(), qt->getSECorner(), green);
            drawline(out, qt->getSteiner(), qt->getSWCorner(), green);
        }
        //       }else{
        //           //TODO
        //       }
    } else {
        Polygon * p2 = filter(p, qt);
        triangulate(out, p2, qt->NEChild);
        triangulate(out, p2, qt->NWChild);
        triangulate(out, p2, qt->SEChild);
        triangulate(out, p2, qt->SWChild);
    }
}

#else

#endif

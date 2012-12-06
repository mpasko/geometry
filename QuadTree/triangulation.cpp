
#include "QuadTree.h"
#include "Visualization.h"
#include "Point.h"
#include "triangulation.h"
#include "General_exception.h"

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
        double miny = center->y - half;
        double maxy = center->y + half;
        double src_h = source->half;
        double src_y = source->center->y;
        double src_x = source->center->x;
        switch (direction) {
            case Dir_NW:
                if (src_y > miny) {
                    new_res = getChildContainingCoord(Per_E, src_y + src_h);
                } else {
                    new_res = getChildContainingCoord(Per_S, src_x - src_h);
                }
                break;
            case Dir_NE:
                if (src_y > miny) {
                    new_res = getChildContainingCoord(Per_W, src_y + src_h);
                } else {
                    new_res = getChildContainingCoord(Per_S, src_x + src_h);
                }
                break;
            case Dir_SW:
                if (src_y < maxy) {
                    new_res = getChildContainingCoord(Per_E, src_y - src_h);
                } else {
                    new_res = getChildContainingCoord(Per_N, src_x - src_h);
                }
                break;
            case Dir_SE:
                if (src_y < maxy) {
                    new_res = getChildContainingCoord(Per_W, src_y - src_h);
                } else {
                    new_res = getChildContainingCoord(Per_N, src_x + src_h);
                }
                break;
            case Dir_N:
                new_res = getChildContainingCoord(Per_S, src_x);
                break;
            case Dir_S:
                new_res = getChildContainingCoord(Per_N, src_x);
                break;
            case Dir_E:
                new_res = getChildContainingCoord(Per_W, src_y);
                break;
            case Dir_W:
                new_res = getChildContainingCoord(Per_E, src_y);
                break;
        }
        if (new_res == NULL) {
            return this;
        } else {
            return new_res->slideDown(direction, source);
        }
    }
}

//QuadTree* QuadTree::getSamllestCornerBox(DiagonalDir dir, QuadTree* parent){
//    if (parent == NULL){
//        throw General_exception("Null");
//    }
//    if (parent.isLeaf()){
//
//    }
//}

//QuadTree* QuadTree::getNeighbourTopDown(Direction direction, QuadTree* parent_neigh, QuadTree* source) {
//    if (parent_neigh == NULL) {
//        return NULL;
//    } else {
//        switch (direction) {
//            case Dir_N:
//            case Dir_E:
//            case Dir_S:
//            case Dir_W:
//                return parent_neigh->slideDown(direction, source);
//                break;
//            case Dir_NE:
//
//                break;
//            case Dir_NW:
//
//                break;
//            case Dir_SE:
//
//                break;
//            case Dir_SW:
//
//                break;
//        }
//    }
//}

QuadTree* QuadTree::getNeighbour(Direction direction, Direction source_dir, QuadTree* source) {
    if (parent == NULL) {
        return NULL;
    }
    QuadTree* parent_neigh;
    switch (direction) {
        case Dir_N:
            switch (parent_region) {
                case Diag_SE:
                    parent_neigh = parent->NEChild;
                    break;
                case Diag_SW:
                    parent_neigh = parent->NWChild;
                    break;
                default:
                    parent_neigh = parent->getNeighbour(direction, source_dir, source);
                    break;
            }
            break;
        case Dir_W:
            switch (parent_region) {
                case Diag_SE:
                    parent_neigh = parent->SWChild;
                    break;
                case Diag_NE:
                    parent_neigh = parent->NWChild;
                    break;
                default:
                    parent_neigh = parent->getNeighbour(direction, source_dir, source);
                    break;
            }
            break;
        case Dir_S:
            switch (parent_region) {
                case Diag_NE:
                    parent_neigh = parent->SEChild;
                    break;
                case Diag_NW:
                    parent_neigh = parent->SWChild;
                    break;
                default:
                    parent_neigh = parent->getNeighbour(direction, source_dir, source);
                    break;
            }
            break;
        case Dir_E:
            switch (parent_region) {
                case Diag_SW:
                    parent_neigh = parent->SEChild;
                    break;
                case Diag_NW:
                    parent_neigh = parent->NEChild;
                    break;
                default:
                    parent_neigh = parent->getNeighbour(direction, source_dir, source);
                    break;
            }
            break;
        case Dir_NW:
            switch (parent_region) {
                case Diag_SE:
                    parent_neigh = parent->NWChild;
                    break;
                case Diag_SW:
                    parent_neigh = parent->getNeighbour(Dir_W, source_dir, source);
                    break;
                case Diag_NE:
                    parent_neigh = parent->getNeighbour(Dir_N, source_dir, source);
                    break;
                case Diag_NW:
                    parent_neigh = parent->getNeighbour(direction, source_dir, source);
                    break;
            }
            break;
        case Dir_NE:
            switch (parent_region) {
                case Diag_SW:
                    parent_neigh = parent->NEChild;
                    break;
                case Diag_NW:
                    parent_neigh = parent->getNeighbour(Dir_N, source_dir, source);
                    break;
                case Diag_SE:
                    parent_neigh = parent->getNeighbour(Dir_E, source_dir, source);
                    break;
                case Diag_NE:
                    parent_neigh = parent->getNeighbour(direction, source_dir, source);
                    break;
            }
            break;
        case Dir_SW:
            switch (parent_region) {
                case Diag_NE:
                    parent_neigh = parent->SWChild;
                    break;
                case Diag_NW:
                    parent_neigh = parent->getNeighbour(Dir_W, source_dir, source);
                    break;
                case Diag_SE:
                    parent_neigh = parent->getNeighbour(Dir_S, source_dir, source);
                    break;
                case Diag_SW:
                    parent_neigh = parent->getNeighbour(direction, source_dir, source);
                    break;
            }
            break;
        case Dir_SE:
            switch (parent_region) {
                case Diag_NW:
                    parent_neigh = parent->SEChild;
                    break;
                case Diag_SW:
                    parent_neigh = parent->getNeighbour(Dir_S, source_dir, source);
                    break;
                case Diag_NE:
                    parent_neigh = parent->getNeighbour(Dir_E, source_dir, source);
                    break;
                case Diag_SE:
                    parent_neigh = parent->getNeighbour(direction, source_dir, source);
                    break;
            }
            break;
    }
    if (parent_neigh == NULL) {
        return NULL;
    } else {
        return parent_neigh->slideDown(source_dir, source);
    }
}

QuadTree* QuadTree::getNeighbour(Direction direction) {
    return getNeighbour(direction, direction, this);
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

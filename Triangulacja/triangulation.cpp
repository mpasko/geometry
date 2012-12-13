
#include "QuadTree.h"
#include "Visualization.h"
#include "Point.h"
#include "triangulation.h"
#include "General_exception.h"

Point* QuadTree::getCrossing(Point*a, Point* b) {
    //TODO
    return NULL;
}

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
        double src_h = source->side;
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

void triangulate(std::ostream&out, QuadTree* qt){
    triangulate(out, qt, green);
}

void triangulate(std::ostream&out, QuadTree*qt, const char* color) {
    if (qt->isLeaf()) {
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
                c = qt->ESplit;
                drawline(out, qt->getNWCorner(), c, color);
                drawline(out, qt->getSWCorner(), c, color);
            } else if (is_w) {
                c = qt->WSplit;
                drawline(out, qt->getNECorner(), c, color);
                drawline(out, qt->getSECorner(), c, color);
            } else if (is_s) {
                c = qt->SSplit;
                drawline(out, qt->getNWCorner(), c, color);
                drawline(out, qt->getNECorner(), c, color);
            } else if (is_n) {
                c = qt->NSplit;
                drawline(out, qt->getSWCorner(), c, color);
                drawline(out, qt->getSECorner(), c, color);
            }
        } else if (count == 0) {

            drawline(out, qt->getNWCorner(), qt->getSECorner(), color);

        } else {

            if (is_e) {
                c = qt->ESplit;
                drawline(out, qt->getSteiner(), c, color);
                delete c;
            }
            if (is_w) {
                c = qt->WSplit;
                drawline(out, qt->getSteiner(), c, color);
                delete c;
            }
            if (is_s) {
                c = qt->SSplit;
                drawline(out, qt->getSteiner(), c, color);
                delete c;
            }
            if (is_n) {
                c = qt->NSplit;
                drawline(out, qt->getSteiner(), c, color);
                delete c;
            }

            drawline(out, qt->getSteiner(), qt->getNECorner(), color);
            drawline(out, qt->getSteiner(), qt->getNWCorner(), color);
            drawline(out, qt->getSteiner(), qt->getSECorner(), color);
            drawline(out, qt->getSteiner(), qt->getSWCorner(), color);
        }
        //       }else{
        //           //TODO
        //       }
    } else {
        triangulate(out, qt->NEChild, color);
        triangulate(out, qt->NWChild, color);
        triangulate(out, qt->SEChild, color);
        triangulate(out, qt->SWChild, color);
    }
}

#else

#endif


#include "triangulation.h"
#include "QuadTree.h"
#include "Visualization.h"

Point* QuadTree::getCrossing(Point*a, Point* b){
    //TODO
    return NULL;
}

QuadTree* QuadTree::slideDown(Direction direction, QuadTree* source){
    if((depth==source->depth) || (isLeaf())){
        return this;
    }else{
        QuadTree * new_res = NULL;
        switch(direction){
            case Dir_NW:
                if(source->parent_region == Diag_NW){
                    new_res = SEChild;
                }else if(source->parent_region == Diag_SW){
                    new_res = NEChild;
                }else if(source->parent_region == Diag_NE){
                    new_res = SWChild;
                }
                break;
            case Dir_NE:
                if(source->parent_region == Diag_NE){
                    new_res = SWChild;
                }else if(source->parent_region == Diag_SE){
                    new_res = NWChild;
                }else if(source->parent_region == Diag_NW){
                    new_res = SEChild;
                }
                break;
            case Dir_SW:
                if(source->parent_region == Diag_SW){
                    new_res = NEChild;
                }else if(source->parent_region == Diag_NW){
                    new_res = SEChild;
                }else if(source->parent_region == Diag_SE){
                    new_res = NWChild;
                }
                break;
            case Dir_SE:
                if(source->parent_region == Diag_SE){
                    new_res = NWChild;
                }else if(source->parent_region == Diag_SW){
                    new_res = NEChild;
                }else if(source->parent_region == Diag_NE){
                    new_res = SWChild;
                }
                break;
            case Dir_N:
                if(source->parent_region == Diag_NW){
                    new_res = SWChild;
                }else if(source->parent_region == Diag_NE){
                    new_res = SEChild;
                }
                break;
            case Dir_S:
                if(source->parent_region == Diag_SW){
                    new_res = NWChild;
                }else if(source->parent_region == Diag_SE){
                    new_res = NEChild;
                }
                break;
            case Dir_E:
                if(source->parent_region == Diag_NE){
                    new_res = NWChild;
                }else if(source->parent_region == Diag_SE){
                    new_res = SWChild;
                }
                break;
            case Dir_W:
                if(source->parent_region == Diag_NW){
                    new_res = NEChild;
                }else if(source->parent_region == Diag_SW){
                    new_res = SEChild;
                }
                break;
        }
        return new_res->slideDown(direction, source);
    }
}

QuadTree* QuadTree::getNeighbour(Direction direction, QuadTree* source){
    if(parent == NULL){
        return NULL;
    }
    QuadTree* parent_neigh;
    switch(direction){
        case Dir_N:
            if(parent_region==Diag_SE){
                parent_neigh = parent->NEChild;
            }else if(parent_region==Diag_SW){
                parent_neigh = parent->NWChild;
            }else{
                parent_neigh = parent->getNeighbour(direction,source);
            }
            break;
        case Dir_W:
            if(parent_region==Diag_SE){
                parent_neigh = parent->SWChild;
            }else if(parent_region==Diag_NE){
                parent_neigh = parent->NWChild;
            }else{
                parent_neigh = parent->getNeighbour(direction,source);
            }
            break;
        case Dir_S:
            if(parent_region==Diag_NE){
                parent_neigh = parent->SEChild;
            }else if(parent_region==Diag_NW){
                parent_neigh = parent->SWChild;
            }else{
                parent_neigh = parent->getNeighbour(direction,source);
            }
            break;
        case Dir_E:
            if(parent_region==Diag_SE){
                parent_neigh = parent->SEChild;
            }else if(parent_region==Diag_NE){
                parent_neigh = parent->NEChild;
            }else{
                parent_neigh = parent->getNeighbour(direction,source);
            }
            break;
        case Dir_NW:
            if(parent_region==Diag_SE){
                parent_neigh = parent->NWChild;
            }else if(parent_region==Diag_SW){
                parent_neigh = parent->getNeighbour(Dir_W,source);
            }else if(parent_region==Diag_NE){
                parent_neigh = parent->getNeighbour(Dir_N,source);
            }else{
                parent_neigh = parent->getNeighbour(direction,source);
            }
            break;
        case Dir_NE:
            if(parent_region==Diag_SW){
                parent_neigh = parent->NEChild;
            }else if(parent_region==Diag_NW){
                parent_neigh = parent->getNeighbour(Dir_N,source);
            }else if(parent_region==Diag_SE){
                parent_neigh = parent->getNeighbour(Dir_E,source);
            }else{
                parent_neigh = parent->getNeighbour(direction,source);
            }
            break;
        case Dir_SW:
            if(parent_region==Diag_NE){
                parent_neigh = parent->SWChild;
            }else if(parent_region==Diag_NW){
                parent_neigh = parent->getNeighbour(Dir_W,source);
            }else if(parent_region==Diag_SE){
                parent_neigh = parent->getNeighbour(Dir_S,source);
            }else{
                parent_neigh = parent->getNeighbour(direction,source);
            }
            break;
        case Dir_SE:
            if(parent_region==Diag_NW){
                parent_neigh = parent->SEChild;
            }else if(parent_region==Diag_SW){
                parent_neigh = parent->getNeighbour(Dir_S,source);
            }else if(parent_region==Diag_NE){
                parent_neigh = parent->getNeighbour(Dir_E,source);
            }else{
                parent_neigh = parent->getNeighbour(direction,source);
            }
            break;
    }
    return parent_neigh->slideDown(direction,source);
}

QuadTree* QuadTree::getNeighbour(Direction direction){
    return getNeighbour(direction,this);
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

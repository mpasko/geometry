#include "QuadTree.h"

 

void QuadTree::subdivide(DiagonalDir region, int target_depth) {
    if (depth >= target_depth) {
        return;
    }
    QuadTree* child = getChildByRegion(region);
    if (child != NULL){
//        subdivide(child);
    } else {
        subdivide();
//        subdivide(getChildByRegion(region));
    }

}

void QuadTree::create_extended_neighbours(){
    switch (parent_region){
        case Diag_NE:
            create_extended_neighbour(Dir_N);
            create_extended_neighbour(Dir_NE);
            create_extended_neighbour(Dir_E);
            break;
        case Diag_NW:
            create_extended_neighbour(Dir_N);
            create_extended_neighbour(Dir_NW);
            create_extended_neighbour(Dir_W);
            break;
        case Diag_SE:
            create_extended_neighbour(Dir_SE);
            create_extended_neighbour(Dir_S);
            create_extended_neighbour(Dir_SW);
            break;
        case Diag_SW:
            create_extended_neighbour(Dir_SW);
            create_extended_neighbour(Dir_S);
            create_extended_neighbour(Dir_SE);
            break;
    }
}

void QuadTree::create_extended_neighbour(Direction direction){
    QuadTree* node = getNeighbour(direction);
    (void)(node);
}

QuadTree* QuadTree::getChildByRegion(DiagonalDir region) {
    switch (region) {
        case Diag_NE:
            return NEChild;
        case Diag_NW:
            return NWChild;
        case Diag_SE:
            return SEChild;
        case Diag_SW:
            return SWChild;
    }
    return NULL;
}

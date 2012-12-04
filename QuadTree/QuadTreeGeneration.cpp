#include "QuadTree.h"

QuadTree* QuadTree::getChildContainingCoord(PerpendicularDir side, double value) {
    if (isLeaf()) {
        return NULL;
    }
    switch (side) {
        case Per_N:
            if (value > center->x) {
                return getChildByRegion(Diag_NE);
            } else {
                return getChildByRegion(Diag_NW);
            }
        case Per_E:
            if (value > center->y) {
                return getChildByRegion(Diag_NE);
            } else {
                return getChildByRegion(Diag_SE);
            }
        case Per_S:
            if (value > center->x) {
                return getChildByRegion(Diag_SE);
            } else {
                return getChildByRegion(Diag_SW);
            }
        case Per_W:
            if (value > center->y) {
                return getChildByRegion(Diag_NW);
            } else {
                return getChildByRegion(Diag_SW);
            }
    }
}

void QuadTree::subdevide(PerpendicularDir side, int target_depth, double side_middle) {
    if (depth >= target_depth) {
        return;
    }
    QuadTree* child = getChildContainingCoord(side, side_middle);
    if (child != NULL) {
        child->subdevide(side, target_depth, side_middle);
    } else {
        subdivide();
        getChildContainingCoord(side, side_middle)->subdivide(side, target_depth, side_middle);
    }
}

void QuadTree::subdivide(QuadTree::DiagonalDir region, int target_depth) {
    if (depth >= target_depth) {
        return;
    }
    QuadTree* child = getChildByRegion(region);
    if (child != NULL) {
        child->subdevide(region, target_depth);
    } else {
        subdivide();
        getChildByRegion(region)->subdivide(region, target_depth);
    }
}

void QuadTree::create_extended_neighbours() {
    create_extended_neighbour(Dir_N);
    create_extended_neighbour(Dir_NE);
    create_extended_neighbour(Dir_E);
    create_extended_neighbour(Dir_SE);
    create_extended_neighbour(Dir_S);
    create_extended_neighbour(Dir_SW);
    create_extended_neighbour(Dir_W);
    create_extended_neighbour(Dir_NW);
}

void QuadTree::create_extended_neighbour(Direction direction) {
    QuadTree* node = getNeighbour(direction);
    switch (direction) {
        case Dir_N:
            subdevide(Per_S, depth, center);
            break;
        case Dir_S:
            subdevide(Per_N, depth, center);
            break;
        case Dir_E:
            subdevide(Per_W, depth, center);
            break;
        case Dir_W:
            subdevide(Per_E, depth, center);
            break;
        case Dir_NE:
            subdivide(Diag_SW, depth);
            break;
        case Dir_NW:
            subdivide(Diag_SE, depth);
            break;
        case Dir_SE:
            subdivide(Diag_NW, depth);
            break;
        case Dir_SW:
            subdivide(Diag_NE, depth);
            break;

    }
}

void QuadTree::create_extended_neighbour(Direction direction){
    QuadTree* node = getNeighbour(direction);
    (void)(node);
}

QuadTree* QuadTree::getChildByRegion(DiagonalDir region) {
    if (isLeaf()) {
        return NULL;
    }
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

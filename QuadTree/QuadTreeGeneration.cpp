#include "QuadTree.h"

 

QuadTree::subdivide(DiagonalDir region, int target_depth) {
    if (depth >= target_depth) {
        return;
    }
    QuadTree* child = getChildByRegion(region);
    if (child != NULL){
        subdivide(child);
    } else {
        subdivide();
        subdivide(getChildByRegion(region));
    }

}

void QuadTree::create_extended_neighbours(){
    switch (parent_region){
        case DiagonalDir::NE:
            create_extended_neighbour(Direction::N);
            create_extended_neighbour(Direction::NE);
            create_extended_neighbour(Direction::E);
            break;
        case DiagonalDir::NW:
            create_extended_neighbour(Direction::N);
            create_extended_neighbour(Direction::NW);
            create_extended_neighbour(Direction::W);
            break;
        case DiagonalDir::SE:
            create_extended_neighbour(Direction::SE);
            create_extended_neighbour(Direction::S);
            create_extended_neighbour(Direction::SW);
            break;
        case DiagonalDir::SW:
            create_extended_neighbour(Direction::SW);
            create_extended_neighbour(Direction::S);
            create_extended_neighbour(Direction::SE);
            break;
    }
}

void QuadTree::create_extended_neighbour(Direction direction){
    QuadTree* node = getNeighbour(direction);
}

QuadTree::getChildByRegion(DiagonalDir region) {
    switch (region) {
        case DiagonalDir::NE:
            return NE;
        case DiagonalDir::NW:
            return NW;
        case DiagonalDir::SE:
            return SE;
        case DiagonalDir::SW:
            return SW;
    }
}
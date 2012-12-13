#include <cmath>

#include "QuadTree.h"
#include "Unexpected_enum_value_exception.h"
#include "Polygon.h"
#include "geometry.h"

void QuadTree::init_mesh(const list<Point*>* points_set) {
    for (list<Point*>::const_iterator it = points_set->begin(); it != points_set->end(); ++it) {
        points.push_back(*it);
    }
    for (list<Point*>::iterator it = this->points.begin(); it != this->points.end(); ++it) {
        putNextPoint(*it);
    }
}

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
        default:
            throw Unexpected_enum_value_exception();
    }
}

void QuadTree::split_until_size(double target_size) {
    if (this->width < target_size) {
        return;
    }
    Point* p = new Point;
    *p = *chunk;
    subdivide();
    match(p)->split_until_size(target_size);
}

void QuadTree::split_to_maximize_distance(double accepted_distance) throw(EmptyNodeException) {
    if (chunk == NULL) {
        throw EmptyNodeException("Trying to split empty node while spliting by point distance.");
    }
    split_until_size(accepted_distance);
}

void QuadTree::split_too_close_boxes() {
    for (list<Point*>::iterator it = points.begin(); it != points.end(); ++it) {
        if ((*it)->node->chunk == NULL) {
            throw EmptyNodeException("Trying to split empty node while spliting by point distance.");
        }
        (*it)->node->split_to_maximize_distance(get_nearest_point_distance((*it)->node->chunk, points) / (2 * M_SQRT2));
    }
    return;
}

void QuadTree::subdivideOrthogonal(PerpendicularDir side, int target_depth, double side_middle) {
    if (depth >= target_depth) {
        return;
    }
    QuadTree* child = getChildContainingCoord(side, side_middle);
    if (child != NULL) {
        child->subdivideOrthogonal(side, target_depth, side_middle);
    } else {
        subdivide();
        (getChildContainingCoord(side, side_middle))->subdivideOrthogonal(side, target_depth, side_middle);
    }
}

void QuadTree::subdivideDiagonal(DiagonalDir region, QuadTree* source, int target_depth) {
    if (depth >= target_depth) {
        return;
    }
    Direction slide_direction;
    switch (region) {
        case Diag_NE:
            slide_direction = Dir_SW;
            break;
        case Diag_NW:
            slide_direction = Dir_SE;
            break;
        case Diag_SE:
            slide_direction = Dir_NW;
            break;
        case Diag_SW:
            slide_direction = Dir_NE;
            break;
    }

    if (!isLeaf()) {
        slideDown(slide_direction, source)->subdivideDiagonal(region, source, target_depth);
    } else {
        subdivide();
        slideDown(slide_direction, source)->subdivideDiagonal(region, source, target_depth);
    }
}

void QuadTree::surround_with_neighbours_ascending() {
    list<QuadTree*> pointed_nodes(points.size());
    for (list<Point*>::iterator it = points.begin(); it != points.end(); ++it) {
        QuadTree* node = (*it)->node;
        while (node->parent != NULL) {
            node->create_extended_neighbours();
            node = node->parent;
        }
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
    if (node == NULL) {
        return;
    }
    switch (direction) {
        case Dir_N:
            node->subdivideOrthogonal(Per_S, depth, center->x);
            break;
        case Dir_S:
            node->subdivideOrthogonal(Per_N, depth, center->x);
            break;
        case Dir_E:
            node->subdivideOrthogonal(Per_W, depth, center->y);
            break;
        case Dir_W:
            node->subdivideOrthogonal(Per_E, depth, center->y);
            break;
        case Dir_NE:
            node->subdivideDiagonal(Diag_SW, this, depth);
            break;
        case Dir_NW:
            node->subdivideDiagonal(Diag_SE, this, depth);
            break;
        case Dir_SE:
            node->subdivideDiagonal(Diag_NW, this, depth);
            break;
        case Dir_SW:
            node->subdivideDiagonal(Diag_NE, this, depth);
            break;
    }
    (void) (node);
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

bool QuadTree::is_unbalanced() {
    QuadTree* neighbour;

    neighbour = getNeighbour(Dir_N);
    if (neighbour != NULL && neighbour->depth == depth && !neighbour->isLeaf()) {
        if (!neighbour->getChildByRegion(Diag_SE)->isLeaf() || !neighbour->getChildByRegion(Diag_SW)->isLeaf()) {
            return true;
        }
    }

    neighbour = getNeighbour(Dir_S);
    if (neighbour != NULL && neighbour->depth == depth && !neighbour->isLeaf()) {
        if (!neighbour->getChildByRegion(Diag_NE)->isLeaf() || !neighbour->getChildByRegion(Diag_NW)->isLeaf()) {
            return true;
        }
    }

    neighbour = getNeighbour(Dir_E);
    if (neighbour != NULL && neighbour->depth == depth && !neighbour->isLeaf()) {
        if (!neighbour->getChildByRegion(Diag_SW)->isLeaf() || !neighbour->getChildByRegion(Diag_NW)->isLeaf()) {
            return true;
        }
    }

    neighbour = getNeighbour(Dir_W);
    if (neighbour != NULL && neighbour->depth == depth && !neighbour->isLeaf()) {
        if (!neighbour->getChildByRegion(Diag_SE)->isLeaf() || !neighbour->getChildByRegion(Diag_NE)->isLeaf()) {
            return true;
        }
    }

    return false;
}

bool QuadTree::balance_children() {
    return NWChild->balance() || NEChild->balance() ||
            SEChild->balance() || SWChild->balance();
}

bool QuadTree::balance() {
    if (isLeaf()) {
        if (is_unbalanced()) {
            subdivide();
            return true;
        } else {
            return false;
        }
    }
    return balance_children();
}

void QuadTree::balance_tree(){
    while (balance());
}
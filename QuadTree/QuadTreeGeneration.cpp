#include <cmath>

#include "QuadTree.h"
#include "Unexpected_enum_value_exception.h"
#include "EmptyNodeException.h"
#include "Polygon.h"

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

void QuadTree::split_to_maximize_distance(double accepted_distance) {
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
        (*it)->node->split_to_maximize_distance(polygon->get_nearest_vertex_distance((*it)->node->chunk) / (2 * M_SQRT2));
    }
    return;
}

void QuadTree::subdivide(PerpendicularDir side, int target_depth, double side_middle) {
    if (depth >= target_depth) {
        return;
    }
    QuadTree* child = getChildContainingCoord(side, side_middle);
    if (child != NULL) {
        child->subdivide(side, target_depth, side_middle);
    } else {
        subdivide();
        (getChildContainingCoord(side, side_middle))->subdivide(side, target_depth, side_middle);
    }
}

void QuadTree::subdivide(DiagonalDir region, int target_depth) {
    if (depth >= target_depth) {
        return;
    }
    QuadTree* child = getChildByRegion(region);
    if (child != NULL) {
        child->subdivide(region, target_depth);
    } else {
        subdivide();
        getChildByRegion(region)->subdivide(region, target_depth);
    }
}

void QuadTree::preproccess() {
    for (list<Point*>::iterator it = points.begin(); it != points.end(); ++it) {
        (*it)->node->create_extended_neighbours();
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
            node->subdivide(Per_S, depth, center->x);
            break;
        case Dir_S:
            node->subdivide(Per_N, depth, center->x);
            break;
        case Dir_E:
            node->subdivide(Per_W, depth, center->y);
            break;
        case Dir_W:
            node->subdivide(Per_E, depth, center->y);
            break;
        case Dir_NE:
            node->subdivide(Diag_SW, depth);
            break;
        case Dir_NW:
            node->subdivide(Diag_SE, depth);
            break;
        case Dir_SE:
            node->subdivide(Diag_NW, depth);
            break;
        case Dir_SW:
            node->subdivide(Diag_NE, depth);
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

void QuadTree::balance_children() {
    NWChild->balance_tree();
    NEChild->balance_tree();
    SEChild->balance_tree();
    SWChild->balance_tree();
}

void QuadTree::balance_tree() {
    if (isLeaf()) {
        if (is_unbalanced()) {
            subdivide();
        } else {
            return;
        }
    }
    balance_children();
}

void QuadTree::print_as_text(int spaces) {
    for (int i = 0; i < spaces; ++i) {
        std::cout << " ";
    }
    switch (parent_region) {
        case Diag_NE:
            std::cout << "NE";
            break;
        case Diag_NW:
            std::cout << "NW";
            break;
        case Diag_SE:
            std::cout << "SE";
            break;
        case Diag_SW:
            std::cout << "SW";
            break;
    }
    std::cout << std::endl;
    if (!isLeaf()) {
        getChildByRegion(Diag_NW)->print_as_text(spaces + 1);
        getChildByRegion(Diag_NE)->print_as_text(spaces + 1);
        getChildByRegion(Diag_SE)->print_as_text(spaces + 1);
        getChildByRegion(Diag_SW)->print_as_text(spaces + 1);
    }
}

void QuadTree::print_as_text() {
    if (!isLeaf()) {
        getChildByRegion(Diag_NW)->print_as_text(0);
        getChildByRegion(Diag_NE)->print_as_text(0);
        getChildByRegion(Diag_SE)->print_as_text(0);
        getChildByRegion(Diag_SW)->print_as_text(0);
    }
}

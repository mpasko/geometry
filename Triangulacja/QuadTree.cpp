/* 
 * File:   QuadTree.cpp
 * Author: marcin
 * 
 * Created on December 2, 2012, 8:17 PM
 */

#include "QuadTree.h"
#include <cstdlib>
#include "Visualization.h"
#include "FlushTable.h"
#include "unexpected_subdivision.h"

#include "FlushTable.cpp" // do konkretyzacji wzorca

using namespace std;

Point* getcenter(Point* a, Point* b) {
    return new Point((a->x + b->x) / 2.0, (a->y + b->y) / 2.0);
}

QuadTree* QuadTree::match(Point* p) {
    QuadTree*dest;
    if (p->x <= center->x) {
        if (p->y <= center->y) {
            dest = SWChild;
        } else {
            dest = NWChild;
        }
    } else {
        if (p->y <= center->y) {
            dest = SEChild;
        } else {
            dest = NEChild;
        }
    }
    return dest;
}

QuadTree::QuadTree(double cx, double cy, double w, QuadTree * par) :
NEChild(NULL), NWChild(NULL), SEChild(NULL), SWChild(NULL), parent(par) {
    center = new Point(cx, cy);
    half = w / 2.0;
    side = w;
    chunk = NULL;
    depth = 0;
    flush = new FlushTable<Point > (20);
    NECorner = new Point(cx + half, cy + half);
    *flush += NECorner;
    SECorner = new Point(cx + half, cy - half);
    *flush += SECorner;
    NWCorner = new Point(cx - half, cy + half);
    *flush += NWCorner;
    SWCorner = new Point(cx - half, cy - half);
    *flush += SWCorner;
    ESplit = getcenter(NECorner, SECorner);
    WSplit = getcenter(NWCorner, SWCorner);
    SSplit = getcenter(SWCorner, SECorner);
    NSplit = getcenter(NECorner, NWCorner);
    *flush += ESplit;
    *flush += WSplit;
    *flush += SSplit;
    *flush += NSplit;
}

bool QuadTree::isLeaf() const {
    return (NEChild == NULL) && (NWChild == NULL) && (SEChild == NULL) && (SWChild == NULL);
}

void QuadTree::subdivide() {
    if (isLeaf()) {
        double cntr = side / 4;
        NEChild = new QuadTree(center->x + cntr, center->y + cntr, half, this);
        NEChild->parent_region = Diag_NE;
        NEChild->depth = depth + 1;
        NWChild = new QuadTree(center->x - cntr, center->y + cntr, half, this);
        NWChild->parent_region = Diag_NW;
        NWChild->depth = depth + 1;
        SEChild = new QuadTree(center->x + cntr, center->y - cntr, half, this);
        SEChild->parent_region = Diag_SE;
        SEChild->depth = depth + 1;
        SWChild = new QuadTree(center->x - cntr, center->y - cntr, half, this);
        SWChild->parent_region = Diag_SW;
        SWChild->depth = depth + 1;
        if (chunk != NULL) {
            QuadTree* child = match(chunk);
            child->chunk = chunk;
            chunk->node = child;
            chunk = NULL;
        }
//        output_manager->print_simulation_step();
    } else {
        throw Unexpected_subdivision("You cannot split leaf");
    }
}

string child_to_str(QuadTree* child) {
    return (child == NULL ? "null" : "exists");
}

void QuadTree::putNextPoint(Point * p) {
    QuadTree* dest;

    if (isLeaf()) {
        if (chunk == NULL) {
            chunk = p;
            p->node = this;
            return;
        } else {
            subdivide();
            dest = match(p);
        }
    } else {
        dest = match(p);
    }
    dest->putNextPoint(p);
}

ostream & operator<<(ostream& out, const QuadTree& tree) {
    if (tree.isLeaf()) {
        Point * a = tree.getNECorner();
        Point * b = tree.getNWCorner();
        Point * c = tree.getSECorner();
        Point * d = tree.getSWCorner();
        double bor = 0.0;
        drawline(out, a->x + bor, a->y + bor, b->x - bor, b->y + bor, red);
        drawline(out, c->x + bor, c->y - bor, d->x - bor, d->y - bor, red);
        drawline(out, a->x + bor, a->y + bor, c->x + bor, c->y - bor, red);
        drawline(out, b->x - bor, b->y + bor, d->x - bor, d->y - bor, red);

    } else {

        out << *(tree.NEChild);
        out << *(tree.NWChild);
        out << *(tree.SEChild);
        out << *(tree.SWChild);

    }
    return out;
}

Point* QuadTree::getNECorner() const {
    return NECorner;
}

Point* QuadTree::getSECorner() const {
    return SECorner;
}

Point* QuadTree::getNWCorner() const {
    return NWCorner;
}

Point* QuadTree::getSWCorner() const {
    return SWCorner;
}

Point* QuadTree::getSteiner() {
    return center;
}

QuadTree::~QuadTree() {
#define DEL(D) if(D!=NULL){\
            delete D;\
        }
    DEL(NEChild)
    DEL(NWChild)
    DEL(SEChild)
    DEL(SWChild)
    NEChild = NWChild = SEChild = SWChild = NULL;
    delete center;
}

void QuadTree::set_output_manager(OutputManager*& output_manager) {
    this->output_manager = output_manager;
}
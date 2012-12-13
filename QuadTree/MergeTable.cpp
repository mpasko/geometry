
#include "MergeTable.h"
#include "Point.h"
#include <cstdlib>

MergeTable::MergeTable(int sz) {
    x = new double[sz];
    y = new double[sz];
    reference = new Point*[sz];
    for (int i = 0; i < sz; ++i) {
        reference[i] = NULL;
    }
    max = 0;
}

bool pointcmp(double x1, double y1, Point * p) {
    return ((x1 + eps > p->x) && (x1 - eps < p->x)) && ((y1 + eps > p->y) && (y1 - eps < p->y));
}

Point* MergeTable::get(double x, double y) {
    for (int i = 0; i < max; ++i) {
        if (reference[i] != NULL) {
            if (pointcmp(x, y, reference[i])) {
                return reference[i];
            }
        } else {
            return NULL;
        }
    }
    return NULL;
}

Point* MergeTable::set(Point* p) {
    int i=0;
    for (i = 0; (i < max) && (reference[i] != NULL); ++i) {
        if (pointcmp(p->x, p->y, reference[i])) {
            return reference[i];
        }
    }
    reference[i] = p;
    ++max;
    return p;
}

void MergeTable::merge(Point ** p, Point ** d){
    Point * r = set(*p);
    *p = r;
    *d = r;
}

MergeTable::~MergeTable() {
    delete x;
    delete y;
    delete reference;
}

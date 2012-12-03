#include "Segment.h"

Segment::Segment() {
}

Segment::Segment(Point a, Point b) : a(a), b(b){
}

Segment::Segment(double x1, double y1, double x2, double y2) : a(x1, y1), b(x2, y2){
}

bool Segment::operator==(const Segment& segment){
    if (this->a == segment.a && this->b == segment.b){
        return true;
    } else {
        return false;
    }
}

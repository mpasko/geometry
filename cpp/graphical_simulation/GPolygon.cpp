#include <ostream>

#include "GPolygon.h"
#include "geometry.h"


using namespace std;

//pair<GPoint, GPoint> GPolygon::getNeighbours(vector<GPoint>::iterator point_it) {
//    pair<GPoint, GPoint> pair = new pair();
//    if (point_it == vertices.begin()) {
//        point_it = vertices.end();
//        --point_it;
//        pair.first = *point_it;
//        point_it = vertices.begin();
//    } else {
//        --point_it;
//        pair.first = *point_it;
//        ++point_it;
//    }
//    ++point_it;
//    if (point_it == vertices.end()) {
//        pair.second = *vertices.begin();
//    } else {
//        pair.second = *point_it;
//    }
//    return pair;
//}

bool is_bad_angle(GPoint& a, GPoint& b, GPoint& c) {
    if (orientation2d(a, b, c) > 0) {
        if (a.y < b.y && c.y < b.y) {
            return true;
        }
        if (a.y > b.y && c.y > b.y) {
            return true;
        }
    }
    return false;
}

bool GPolygon::isMonotonic() {
    unsigned int i = 0;
    GPoint a, b, c;
    vector<GPoint>::iterator point_it;
    for (point_it = vertices.begin(), i = 0; i < vertices.size() - 2; ++i) {
        a = *point_it++;
        b = *point_it++;
        c = *point_it--;
        if (is_bad_angle(a, b, c)) {
            return false;
        }
    }
    a = *point_it++;
    b = *point_it;
    c = *vertices.begin();
    if (is_bad_angle(a, b, c)) {
        return false;
    }
    a = *point_it;
    point_it = vertices.begin();
    b = *point_it++;
    c = *point_it;
    if (is_bad_angle(a, b, c)) {
        return false;
    } else {
        return true;
    }
}

//string GPolygon::to_sim_format() {
//    ostringstream os;
//    for (vector<GPoint>::iterator it = vertices.begin(); it != vertices.end(); ++it) {
//        //os << "(" << it->x << " " << it->y << ") ";
//   // }
//    return os.str();
//}



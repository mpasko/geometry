#include "GPoint.h"
#include "Point.h"

GPoint::GPoint(){
}

GPoint::GPoint(double x, double y) : Point(x, y){
}

GPoint::GPoint(Point& point){
    x = point.x;
    y = point.y;
}

string GPoint::to_sim_format() {
    char bufffer[100];
    string format = symbol + ", %d, " + (hide == true ? "HIDE" : disp_properties.to_sim_format()) + ", %f, %f";
    sprintf(bufffer, format.c_str(), id, x, y);
    return string(bufffer);
}

bool GPoint::operator==(const GPoint& g_point){
    if (this->id == g_point.id){
        return true;
    } else {
        return false;
    }
}
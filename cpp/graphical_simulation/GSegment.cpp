#include <stdlib.h>
#include <string.h>
#include <algorithm>

#include "GSegment.h"

GSegment::GSegment(){
};

GSegment::GSegment(GPoint a, GPoint b) {
    this->a = a;
    this->b = b;
};

void GSegment::swap(){
    std::swap(a, b);
}

double GSegment::get_y(double x) throw(coordinate_out_of_bounds_exception){
    if (a.x > b.x){
        if (x > a.x || x < b.x){
            throw coordinate_out_of_bounds_exception();
        }
    } else {
        if (x < a.x || x > b.x){
            throw coordinate_out_of_bounds_exception();
        }
    }

    return a.y + (((b.y - a.y)*(x - a.x))/((b.x-a.x)));
}

string GSegment::to_sim_format() {
    char buffer[150];
    string format = symbol + ", %d, " + (hide == true ? "HIDE" : disp_properties.to_sim_format()) + ", %f, %f, %f, %f";
    char* format_cstring = (char*)calloc(100, 1);
    strcpy(format_cstring, format.c_str());
    if (sprintf(buffer, format.c_str(), id, a.x, a.y, b.x, b.y) < 0){
        perror("sprintf segment data");
    }
    return string(buffer);
}

bool GSegment::operator==(const GSegment& g_segment) const{
    if (this->id == g_segment.id){
        return true;
    } else {
        return false;
    }
}

bool GSegment::operator<(const GSegment& g_segment){
    return (this->id < g_segment.id ? true : false);
}

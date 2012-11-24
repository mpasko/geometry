
#ifndef GSEGMENT_H
#define	GSEGMENT_H

#include "GFigure.h"
#include "GPoint.h"

using namespace std;

struct coordinate_out_of_bounds_exception : exception{
};

class GSegment : public GFigure {
public:
    GPoint a;
    GPoint b;

    GSegment();
    GSegment(GPoint a, GPoint b);

    void swap();
    double get_y(double x) throw (coordinate_out_of_bounds_exception);
    
    bool operator==(const GSegment& gsegment) const;
    bool operator<(const GSegment& gsegment);

    string to_sim_format();
};

#endif	/* GSEGMENT_H */


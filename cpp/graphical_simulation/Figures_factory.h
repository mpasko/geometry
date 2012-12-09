#ifndef FIGURESFACTORY_H
#define	FIGURESFACTORY_H

#include <vector>

#include "Display_properties.h"
#include "GPoint.h"
#include "GSegment.h"
#include "GPolygon.h"
#include "GFigure.h"

using namespace std;

class Figures_factory{
public:
    static Figures_factory& get_instance();

    Display_properties point_display_properties;
    Display_properties segment_display_properties;
    Display_properties polygon_display_properties;

    GPoint create_point();
    GPoint create_point(double x, double y);
    GPoint create_point(Point point);
    GPoint create_point(Display_properties disp_properties);
    GPoint create_point(Display_properties disp_properties, double x, double y);

    GSegment create_segment(Point a, Point b);
    GSegment create_segment(double x1, double y1, double x2, double y2);

    //GPolygon create_polygon(vector<GPoint> points);
protected:
    static Figures_factory* instance;
    Figures_factory();
    int figure_id;
};

#endif	/* FIGURESFACTORY_H */


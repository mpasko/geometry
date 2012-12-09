#include <algorithm>
#include <iostream>

#include "Figures_factory.h"
#include "Display_properties.h"
#include "GPoint.h"
#include "GSegment.h"

using namespace std;

Figures_factory* Figures_factory::instance = NULL;

Figures_factory::Figures_factory() : figure_id(0) {
}

GPoint Figures_factory::create_point() {
    GPoint point;
    point.disp_properties = point_display_properties;
    point.hide = false;
    point.id = ++figure_id;
    point.symbol = "p";
    return point;
}

GPoint Figures_factory::create_point(double x, double y) {
    GPoint point(x, y);
    point.disp_properties = point_display_properties;
    point.hide = false;
    point.id = ++figure_id;
    point.symbol = "p";
    return point;
}

GPoint Figures_factory::create_point(Point point) {
    return create_point(point.x, point.y);
}

GPoint Figures_factory::create_point(Display_properties disp_properties) {
    GPoint point;
    point.disp_properties = disp_properties;
    point.hide = false;
    point.id = ++figure_id;
    point.symbol = "p";
    return point;
}

GPoint Figures_factory::create_point(Display_properties disp_properties, double x, double y) {
    GPoint point(x, y);
    point.disp_properties = disp_properties;
    point.hide = false;
    point.id = ++figure_id;
    point.symbol = "p";
    return point;
}

GSegment Figures_factory::create_segment(Point a, Point b) {
    GSegment segment(create_point(a), create_point(b));
    segment.disp_properties = segment_display_properties;
    segment.hide = false;
    segment.id = ++figure_id;
    segment.symbol = "s";
    return segment;
}

GSegment Figures_factory::create_segment(double x1, double y1, double x2, double y2) {
    return create_segment(Point(x1, y1), Point(x2, y2));
}

//GPolygon Figures_factory::create_polygon(vector<GPoint> points){
//    GPolygon polygon;
//    polygon.vertices = points;
//    polygon.disp_properties = polygon_display_properties;
//    polygon.hide = false;
//    polygon.id = ++figure_id;
//    polygon.symbol = "poly";
//    return polygon;
//}

Figures_factory& Figures_factory::get_instance() {
    if (instance == NULL) {
        static Figures_factory factory;
        instance = &factory;
    }
    return *instance;
}

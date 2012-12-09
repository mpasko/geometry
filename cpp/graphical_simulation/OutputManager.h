#include <string>
#include <iostream>
#include <fstream>
#include <list>

#include "GFigure.h"
#include "GPoint.h"
#include "GSegment.h"

#ifndef OUTPUTMANAGER_H
#define	OUTPUTMANAGER_H

using namespace std;

class OutputManager {
public:
    OutputManager();
    OutputManager(string file_name);
    virtual ~OutputManager();
    void openFile();
    void closeFile();
    void printf_new_step();
    void printf_figure(GFigure& figure);
    void printf_figure(GFigure& figure, string color);
    void printf_points_vector(vector<GPoint>& figures_vector);
    void printf_segments_vector(vector<GSegment>& segments_vector);
    void printf_points_list(list<GPoint>& points_list);
    void printf_segments_list(list<GSegment>& segments_list);
    void hide_figure(GFigure& figure);
    void set_file(string file_name);
private:
    int step;
    string file_name;
    ofstream out_stream;
};

#endif	/* OUPUTMANAGER_H */


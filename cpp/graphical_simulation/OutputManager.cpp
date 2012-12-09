#include <string>
#include <vector>
#include <fstream>
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include "OutputManager.h"
#include "GPoint.h"

OutputManager::OutputManager() : step(0), file_name(""){
};

OutputManager::OutputManager(string file_name) : step(0){
    this->file_name = file_name;
};

OutputManager::~OutputManager(){
    if (out_stream.is_open()){
        out_stream.close();
    }
};

void OutputManager::openFile() {
    closeFile();
    out_stream.open(file_name.c_str(), ios::out);
};

void OutputManager::closeFile() {
    if (out_stream.is_open()){
        out_stream.close();
    }
};

void OutputManager::printf_new_step() {
    out_stream << "step, " << step++ << endl;
};

void OutputManager::printf_figure(GFigure& figure) {
    out_stream << figure.to_sim_format() << endl;
};

void OutputManager::printf_figure(GFigure& figure, string color) {
    figure.disp_properties.color = color;
    printf_figure(figure);
};

void OutputManager::printf_points_vector(vector<GPoint>& figures_vector) {
    vector<GPoint>::iterator it;
    for (it = figures_vector.begin(); it != figures_vector.end(); ++it) {
        out_stream << it->to_sim_format() << endl;
    }
};

void OutputManager::printf_segments_vector(vector<GSegment>& segments_vector) {
    vector<GSegment>::iterator it;
    for (it = segments_vector.begin(); it != segments_vector.end(); ++it) {
        out_stream << it->to_sim_format() << endl;
    }
};

void OutputManager::printf_points_list(list<GPoint>& figures_list) {
    list<GPoint>::iterator it;
    for (it = figures_list.begin(); it != figures_list.end(); ++it) {
        out_stream << it->to_sim_format() << endl;
    }
};

void OutputManager::printf_segments_list(list<GSegment>& segments_list) {
    list<GSegment>::iterator it;
    for (it = segments_list.begin(); it != segments_list.end(); ++it) {
        out_stream << it->to_sim_format() << endl;
    }
};

void OutputManager::hide_figure(GFigure& figure) {
    figure.hide = true;
    printf_figure(figure);
};

void OutputManager::set_file(string file_name) {
    this->file_name = file_name;
};


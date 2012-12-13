/* 
 * File:   OutputManager.cpp
 * Author: Admin
 * 
 * Created on 10 grudzie� 2012, 22:05
 */

#include <list>

#include "OutputManager.h"
#include "Visualization.h"

using namespace std;

OutputManager::OutputManager(Polygon*& polygon, QuadTree*& quadtree, ofstream*& out_stream) : draws_points_set(false) {
    this->polygon = polygon;
    this->points_set = NULL;
    this->quad_tree = quadtree;
    this->output_stream = out_stream;
}

OutputManager::OutputManager(std::list<Point*>*& points_set, QuadTree*& quadtree, ofstream*& out_stream) : draws_points_set(true) {
    this->polygon = NULL;
    this->points_set = points_set;
    this->quad_tree = quadtree;
    this->output_stream = out_stream;
}

void OutputManager::print_simulation_step() {
    if (output_stream == NULL) {
        return;
    }
    step(*output_stream);
    print_points_set();
    if (quad_tree != NULL) {
        *output_stream << *quad_tree;
    }

}

void OutputManager::print_points_set() {
if (draws_points_set) {
        if (points_set != NULL) {
            for (list<Point*>::iterator it = points_set->begin(); it != points_set->end(); ++it) {
                drawpoint(*output_stream, (*it)->x, (*it)->y, black);
            }
        }
    } else {
        if (points_set != NULL) {
            *output_stream << *polygon;
        }
    }
}

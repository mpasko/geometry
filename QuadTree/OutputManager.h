/* 
 * File:   OutputManager.h
 * Author: Admin
 *
 * Created on 10 grudzieñ 2012, 22:05
 */

#ifndef OUTPUTMANAGER_H
#define	OUTPUTMANAGER_H

#include "QuadTree.h"

#include <list>
#include <ostream>
#include <fstream>

class OutputManager {
public:
    OutputManager(Polygon* polygon,  QuadTree* quadtree, std::ofstream* out_stream);
    OutputManager(std::list<Point*>* points_set,  QuadTree* quadtree, std::ofstream* out_stream);
    void print_simulation_step();
private:
    bool draws_points_set;
    std::ofstream* output_stream;
    QuadTree* quad_tree;
    Polygon* polygon;
    std::list<Point*>* points_set;
};

#endif	/* OUTPUTMANAGER_H */


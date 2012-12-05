/* 
 * File:   main.cpp
 * Author: marcin
 *
 * Created on November 29, 2012, 1:18 PM
 */

#include <cstdlib>
#include "Point.h"
#include <exception>
#include <iostream>
#include <ostream>
#include "Polygon.h"
#include <fstream>
#include "trimmer.h"
#include "QuadTree.h"
#include "Visualization.h"
#include "triangulation.h"

using namespace std;

/*Zalozenie: os y biegnie do gory*/

Polygon* load_data(int size, char* filename){
    Polygon * p = new Polygon(size);
    ifstream file(filename);
    Point * prev = NULL;
    Point * first = NULL;
    FlushTable<Point> flush(size+1);
    for (int i=0; i<size; ++i){
        float x,y;
        string sx, sy, empty;
        getline(file, sx, ',');
        sx = trim(sx);
        x = atof(sx.c_str());
        getline(file, sy, ',');
        sx = trim(sy);
        y = atof(sy.c_str());
        getline(file, empty, ',');
        getline(file, empty, ',');
        getline(file, empty, '\n');
        
        Point * current = new Point(x,y);
        flush += current;
        *p += current;
        if (prev != NULL){
//            drawline(cout,prev,current,blue);
        }else{
            first = current;
        }
        prev = current;
    }
//    drawline(cout,prev,first,blue);
    file.close();
    return p;
}

QuadTree* init_mesh(ostream&out_stream, Polygon* p){
    QuadTree* qt = new QuadTree(0.0,0.0,3000.0,NULL);
    
//    for(int j=0; j<p->length(); ++j){
//        qt->putNextPoint((*p)[j]); 
//    } 
    for(int j=0; j<p->length(); ++j){
        qt->points.push_back((*p)[j]); 
    } 
    
    for (list<Point*>::iterator it = qt->points.begin(); it != qt->points.end(); ++it){
        qt->putNextPoint(*it);
    }
    
    return qt;
}

//void triangulate(std::ostream&out, Polygon* p, QuadTree*qt);

/*
 * 
 */
int main(int argc, char** argv) {
    int size;
    char* filen;
//    ofstream fl("input.in");
//    fl << "no-hello!";
//    fl.close();
    if(argc >= 3){
            size = atoi(argv[1]);
            filen = argv[2];
    }else{
        size = 23;
        filen = (char*)"input.in";
    }
    ofstream out_stream("sim_out.txt");
    Polygon* p = load_data(size,filen);
    for (int i = 0; i < p->length(); ++i){
        cout << (*p)[i]->x << " " << (*p)[i]->y << endl;
    }
    QuadTree* qt = init_mesh(out_stream,p);
    qt->polygon = p;
    MergeTable merge(size*size*100);
//    qt->preproccess();
//    qt->split_to_maximize_distance();
    qt->mergeCorners(&merge);
    qt->transform();
    out_stream << *p;
    out_stream << *qt;
    triangulate(out_stream,p,qt);
    delete p;
    //delete qt;
//    QuadTree quadTree(0.0, 0.0, 100, NULL);
//    quadTree.subdivide();
//    quadTree.NWChild->subdivide();
//    quadTree.SWChild->subdivide();
//    quadTree.SEChild->subdivide();
//    quadTree.NEChild->subdivide();
//    quadTree.NEChild->NWChild->subdivide();
//    quadTree.NEChild->SWChild->subdivide();
//    quadTree.NEChild->SWChild->NWChild->subdivide();
//    quadTree.NEChild->SWChild->NEChild->subdivide();
//    quadTree.balance_tree();
//    quadTree.print_as_text();
//    ofstream out_stream("C:\\Users\\Admin\\Documents\\test_input.txt");
//    out_stream << quadTree;
    return 0;
}


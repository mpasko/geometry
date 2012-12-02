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
#include "Visualization.h"
#include "Polygon.h"
#include <fstream>
#include "trimmer.h"
#include "QuadTree.h"

using namespace std;

/*Zalozenie: os y biegnie do gory*/

Polygon* load_data(int size, char* filename){
    Polygon * p = new Polygon(size+1);
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
            drawline(cout,prev,current,blue);
        }else{
            first = current;
        }
        prev = current;
    }
    drawline(cout,prev,first,blue);
    file.close();
    return p;
}

QuadTree* init_mesh(Polygon* p){
    QuadTree* qt = new QuadTree(0.0,0.0,1600.0);
    
    for(int j=0; j<p->length(); ++j){
        qt->putNextPoint((*p)[j]);
    }
    ofstream out_stream("output.txt");
    out_stream << *qt;
    return qt;
}

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
    Polygon* p = load_data(size,filen);
    QuadTree* qt = init_mesh(p);
    delete p;
    delete qt;
    return 0;
}


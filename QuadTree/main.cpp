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

using namespace std;

/*Zalozenie: os y biegnie do gory*/
class QuadTree{
    
    void match(Point* p){
        class QuadTree*dest = NULL;
        if(p->x <= center->x){
            if(p->y <= center->y){
                dest = SW;
            }else{
                dest = NW;
            }
        }else{
            if(p->y <= center->y){
                dest = SE;
            }else{
                dest = NE;
            }
        }
        dest->putNextPoint(p);
    }

public:
    class QuadTree* NE;
    class QuadTree* NW;
    class QuadTree* SE;
    class QuadTree* SW;
    
    Point* center;
    float width;
    float half;
    Point* chunk;
    
    QuadTree(float cx, float cy, float w): NE(NULL),NW(NULL),SE(NULL),SW(NULL){   
        center = new Point(cx,cy);
        half = w/2;
        width = w;
        chunk = NULL;
    }
    
    bool isLeaf() const {
        return (NE==NULL)&&(NW==NULL)&&(SE==NULL)&&(SW==NULL);
    }
    
    void subdivide(){
        if(isLeaf()){
            float cntr = width/4;
            NE = new QuadTree(center->x+cntr,center->y+cntr,half);
            NW = new QuadTree(center->x-cntr,center->y+cntr,half);
            SE = new QuadTree(center->x+cntr,center->y-cntr,half);
            SW = new QuadTree(center->x-cntr,center->y-cntr,half);
        }
    }
    
    void putNextPoint(Point * p){
        if(isLeaf()){
            if(chunk == NULL){
                chunk = p;
                return;
            }else{
                subdivide();
                match(chunk);
                match(p);
                chunk = NULL;
            }
            return;
        }else{
            match(p);
        }
    }
    
    friend ostream& operator<<(ostream& out, const QuadTree& tree){
        if(tree.isLeaf()){
            float x = tree.center->x;
            float y = tree.center->y;
            float half = tree.half;
            drawline(out,x-half,y-half,x-half,y+half,green);
            drawline(out,x+half,y+half,x-half,y+half,green);
            drawline(out,x+half,y-half,x-half,y-half,green);
            drawline(out,x+half,y-half,x+half,y+half,green);
        }else{
            out<<*(tree.NE);
            out<<*(tree.NW);
            out<<*(tree.SE);
            out<<*(tree.SW);
        }
        return out;
    }
    
    ~QuadTree(){
#define DEL(D) if(D!=NULL){\
            delete D;\
        }
        DEL(NE)
        DEL(NW)
        DEL(SE)
        DEL(SW)
        NE = NW = SE = SW = NULL;
        delete center;
    }
};

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
 /* *x/
    qt->subdivide();
 /* *x/
    Point a(206.0,205.5);
    Point b(206.0,204.5);
    Point c(204.0,205.5);
    Point d(204.0,204.5);
    qt->putNextPoint(&a);
    qt->putNextPoint(&b);
    qt->putNextPoint(&c);
    qt->putNextPoint(&d);
 /* */
    for(int j=0; j<p->length(); ++j){
        qt->putNextPoint((*p)[j]);
    }
    cout << *qt;
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
        filen = "input.in";
    }
    Polygon* p = load_data(size,filen);
    QuadTree* qt = init_mesh(p);
    delete p;
    delete qt;
    return 0;
}


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

using namespace std;


class QuadTree{
public:
    class QuadTree* NE;
    class QuadTree* NW;
    class QuadTree* SE;
    class QuadTree* SW;
    
    Point* center;
    float width;
    
    QuadTree(float cx, float cy, float w): NE(NULL),NW(NULL),SE(NULL),SW(NULL),width(w){   
        center = new Point(cx,cy);
    }
    
    void subdivide(){
        if((NE==NULL)&&(NW==NULL)&&(SE==NULL)&&(SW==NULL)){
            float nw_wdh = width/2;
            float cntr = width/4;
            NE = new QuadTree(center->x-cntr,center->y-cntr,nw_wdh);
            NW = new QuadTree(center->x+cntr,center->y-cntr,nw_wdh);
            SE = new QuadTree(center->x-cntr,center->y+cntr,nw_wdh);
            SW = new QuadTree(center->x+cntr,center->y+cntr,nw_wdh);
        }
    }
    
    friend ostream& operator<<(ostream& out, const QuadTree& tree){
        if((tree.NE==NULL)&&(tree.NW==NULL)&&(tree.SE==NULL)&&(tree.SW==NULL)){
            float bndr = tree.width/2;
            float x = tree.center->x;
            float y = tree.center->y;
            drawline(out,x-bndr,y-bndr,x-bndr,y+bndr,green);
            drawline(out,x+bndr,y+bndr,x-bndr,y+bndr,green);
            drawline(out,x-bndr,y+bndr,x-bndr,y-bndr,green);
            drawline(out,x-bndr,y+bndr,x+bndr,y+bndr,green);
        }else{
            out<<tree.NE;
            out<<tree.NW;
            out<<tree.SE;
            out<<tree.SW;
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

Polygon* load_data(int size){
    Polygon * p = new Polygon(size);
    
    return p;
}

QuadTree* init_mesh(Polygon* p){
    QuadTree* qt = new QuadTree(0.0,0.0,100.0);
    qt->subdivide();
    cout << qt;
    return qt;
}


/*
 * 
 */
int main(int argc, char** argv) {
    int size;
    if(argc == 2){
            size = atoi(argv[1]);
    }else{
        size = 100;
    }
    Polygon* p = load_data(size);
    QuadTree* qt = init_mesh(p);
    delete p;
    delete qt;
    return 0;
}


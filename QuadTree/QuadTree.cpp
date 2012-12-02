/* 
 * File:   QuadTree.cpp
 * Author: marcin
 * 
 * Created on December 2, 2012, 8:17 PM
 */

#include "QuadTree.h"
#include <cstdlib>
#include "Visualization.h"

void QuadTree::match(Point* p){
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
    
    QuadTree::QuadTree(float cx, float cy, float w): NE(NULL),NW(NULL),SE(NULL),SW(NULL){   
        center = new Point(cx,cy);
        half = w/2;
        width = w;
        chunk = NULL;
    }
    
    bool QuadTree::isLeaf() const {
        return (NE==NULL)&&(NW==NULL)&&(SE==NULL)&&(SW==NULL);
    }
    
    void QuadTree::subdivide(){
        if(isLeaf()){
            float cntr = width/4;
            NE = new QuadTree(center->x+cntr,center->y+cntr,half);
            NW = new QuadTree(center->x-cntr,center->y+cntr,half);
            SE = new QuadTree(center->x+cntr,center->y-cntr,half);
            SW = new QuadTree(center->x-cntr,center->y-cntr,half);
        }
    }
    
    void QuadTree::putNextPoint(Point * p){
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
    
    using namespace std;
    
    friend ostream& QuadTree::operator<<(ostream& out, const QuadTree::QuadTree& tree){
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
    
    QuadTree::~QuadTree(){
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


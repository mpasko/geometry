/* 
 * File:   QuadTree.cpp
 * Author: marcin
 * 
 * Created on December 2, 2012, 8:17 PM
 */

#include "QuadTree.h"
#include <cstdlib>
#include "Visualization.h"
#include "FlushTable.h"

using namespace std;

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
    
    QuadTree::QuadTree(float cx, float cy, float w, QuadTree * par): 
    NE(NULL),NW(NULL),SE(NULL),SW(NULL),parent(par)
    {   
        center = new Point(cx,cy);
        half = w/2;
        width = w;
        chunk = NULL;
        depth = 0;
        flush = new FlushTable<Point>(20);
        NECorner = new Point(cx-half,cy+half);
        *flush += NECorner;
        SECorner = new Point(cx-half,cy-half);
        *flush += SECorner;
        NWCorner = new Point(cx+half,cy+half);
        *flush += NWCorner;
        SWCorner = new Point(cx+half,cy-half);
        *flush += SWCorner;
    }
    
    bool QuadTree::isLeaf() const {
        return (NE==NULL)&&(NW==NULL)&&(SE==NULL)&&(SW==NULL);
    }
    
    void QuadTree::subdivide(){
        ++depth;
        if(isLeaf()){
            float cntr = width/4;
            NE = new QuadTree(center->x+cntr,center->y+cntr,half,this);
            NW = new QuadTree(center->x-cntr,center->y+cntr,half,this);
            SE = new QuadTree(center->x+cntr,center->y-cntr,half,this);
            SW = new QuadTree(center->x-cntr,center->y-cntr,half,this);
        }else{
            NE->subdivide();
            NW->subdivide();
            SE->subdivide();
            SW->subdivide();
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
    
    ostream& operator<<(ostream& out, const QuadTree& tree){
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
    
    Point* QuadTree::getNECorner(){
        return NECorner;
    }
    
    Point* QuadTree::getSECorner(){
        return SECorner;
    }
    
    Point* QuadTree::getNWCorner(){
        return NWCorner;
    }
    
    Point* QuadTree::getSWCorner(){
        return SWCorner;
    }
    
    Point* QuadTree::getSteiner(){
        return center;
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
        delete flush;
    }


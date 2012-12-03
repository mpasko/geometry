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
                dest = SWChild;
            }else{
                dest = NWChild;
            }
        }else{
            if(p->y <= center->y){
                dest = SEChild;
            }else{
                dest = NEChild;
            }
        }
        dest->putNextPoint(p);
    }
    
    QuadTree::QuadTree(float cx, float cy, float w, QuadTree * par): 
    NEChild(NULL),NWChild(NULL),SEChild(NULL),SWChild(NULL),parent(par)
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
        return (NEChild==NULL)&&(NWChild==NULL)&&(SEChild==NULL)&&(SWChild==NULL);
    }
    
    void QuadTree::subdivide(){
        ++depth;
        if(isLeaf()){
            float cntr = width/4;
            NEChild = new QuadTree(center->x+cntr,center->y+cntr,half,this);
            NWChild = new QuadTree(center->x-cntr,center->y+cntr,half,this);
            SEChild = new QuadTree(center->x+cntr,center->y-cntr,half,this);
            SWChild = new QuadTree(center->x-cntr,center->y-cntr,half,this);
        }else{
            NEChild->subdivide();
            NWChild->subdivide();
            SEChild->subdivide();
            SWChild->subdivide();
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
            out<<*(tree.NEChild);
            out<<*(tree.NWChild);
            out<<*(tree.SEChild);
            out<<*(tree.SWChild);
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
        DEL(NEChild)
        DEL(NWChild)
        DEL(SEChild)
        DEL(SWChild)
        NEChild = NWChild = SEChild = SWChild = NULL;
        delete center;
        delete flush;
    }

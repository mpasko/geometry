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
#include "unexpected_subdivision.h"

using namespace std;

Point* getcenter(Point* a, Point* b) {
    return new Point((a->x + b->x)/2.0, (a->y + b->y)/2.0);
}

QuadTree* QuadTree::match(Point* p){
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
        return dest;
    }
    
    QuadTree::QuadTree(double cx, double cy, double w, QuadTree * par): 
    NEChild(NULL),NWChild(NULL),SEChild(NULL),SWChild(NULL),parent(par)
    {   
        center = new Point(cx,cy);
        half = w/2;
        width = w;
        chunk = NULL;
        depth = 0;
        flush = new FlushTable<Point>(20);
        NECorner = new Point(cx+half,cy+half);
        *flush += NECorner;
        SECorner = new Point(cx+half,cy-half);
        *flush += SECorner;
        NWCorner = new Point(cx-half,cy+half);
        *flush += NWCorner;
        SWCorner = new Point(cx-half,cy-half);
        *flush += SWCorner;
        ECorner = getcenter(NECorner,SECorner);
        WCorner = getcenter(NWCorner,SWCorner);
        SCorner = getcenter(SWCorner,SECorner);
        NCorner = getcenter(NECorner,NWCorner);
        *flush += ECorner;
        *flush += WCorner;
        *flush += SCorner;
        *flush += NCorner;
    }
    
    bool QuadTree::isLeaf() const {
        return (NEChild==NULL)&&(NWChild==NULL)&&(SEChild==NULL)&&(SWChild==NULL);
    }
    
    void QuadTree::subdivide(){
        if(isLeaf()){
            double cntr = width/4;
            NEChild = new QuadTree(center->x+cntr,center->y+cntr,half,this);
            NEChild->parent_region = Diag_NE;
            NEChild->depth = depth + 1;
            NWChild = new QuadTree(center->x-cntr,center->y+cntr,half,this);
            NWChild->parent_region = Diag_NW;
            NWChild->depth = depth + 1;
            SEChild = new QuadTree(center->x+cntr,center->y-cntr,half,this);
            SEChild->parent_region = Diag_SE;
            SEChild->depth = depth + 1;
            SWChild = new QuadTree(center->x-cntr,center->y-cntr,half,this);
            SWChild->parent_region = Diag_SW;
            SWChild->depth = depth + 1;
            if (chunk != NULL){
                match(chunk);
                chunk = NULL;
            }
        }else{
            throw Unexpected_subdivision("You cannot split leaf");
       
//            NEChild->subdivide();
//            NWChild->subdivide();
//            SEChild->subdivide();
//            SWChild->subdivide();
            
        }
    }
    
    void QuadTree::putNextPoint(Point * p){
        QuadTree* dest;
        if(isLeaf()){
            if(chunk == NULL){
                chunk = p;
                p->node = this;
                return;
            }else{
                subdivide();
                dest = match(p);             
            }
        }else{
            dest = match(p);
        }
        dest->putNextPoint(p);
    }
    
    ostream& operator<<(ostream& out, const QuadTree& tree){
        if(tree.isLeaf()){
//            double x = tree.center->x;
//            double y = tree.center->y;
//            double half = tree.half;
            drawline(out,tree.getNECorner(),tree.getNWCorner(),red);
            drawline(out,tree.getNECorner(),tree.getSECorner(),red);
            drawline(out,tree.getSWCorner(),tree.getSECorner(),red);
            drawline(out,tree.getSWCorner(),tree.getNWCorner(),red);
        }else{
            out<<*(tree.NEChild);
            out<<*(tree.NWChild);
            out<<*(tree.SEChild);
            out<<*(tree.SWChild);
        }
        return out;
    }
    
    Point* QuadTree::getNECorner() const{
        return NECorner;
    }
    
    Point* QuadTree::getSECorner() const{
        return SECorner;
    }
    
    Point* QuadTree::getNWCorner() const{
        return NWCorner;
    }
    
    Point* QuadTree::getSWCorner() const{
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

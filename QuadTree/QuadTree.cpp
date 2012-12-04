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
    
    QuadTree::QuadTree(double cx, double cy, double w, QuadTree * par): 
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
        }else{
            throw Unexpected_subdivision("You cannot split leaf");
       
//            NEChild->subdivide();
//            NWChild->subdivide();
//            SEChild->subdivide();
//            SWChild->subdivide();
            
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
            double x = tree.center->x;
            double y = tree.center->y;
            double half = tree.half;
            drawline(out,x-half,y-half,x-half,y+half,red);
            drawline(out,x+half,y+half,x-half,y+half,red);
            drawline(out,x+half,y-half,x-half,y-half,red);
            drawline(out,x+half,y-half,x+half,y+half,red);
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

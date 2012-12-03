/* 
 * File:   QuadTree.h
 * Author: marcin
 *
 * Created on December 2, 2012, 8:17 PM
 */

#ifndef QUADTREE_H
#define	QUADTREE_H

#include <iostream>
#include "Point.h"
#include "FlushTable.h"

using namespace std;

#define DIRECTION_N 0
#define DIRECTION_W 1
#define DIRECTION_S 2
#define DIRECTION_E 3
#define DIRECTION_NW 4
#define DIRECTION_NE 5
#define DIRECTION_SW 6
#define DIRECTION_SE 7

class QuadTree{
    
    void match(Point* p);
    FlushTable<Point> * flush;
    
    Point * NECorner;
    Point * NWCorner;
    Point * SECorner;
    Point * SWCorner;

public:
    class QuadTree* NE;
    class QuadTree* NW;
    class QuadTree* SE;
    class QuadTree* SW;
    class QuadTree* parent;
    
    Point* center;
    float width;
    float half;
    Point* chunk;
    
    int depth;
    
    QuadTree(float cx, float cy, float w, QuadTree* parent);
    
    bool isLeaf() const;
    
    void subdivide();
    
    void putNextPoint(Point * p);
    
    friend ostream& operator<<(ostream& out, const QuadTree& tree);
    
    Point* getCrossing(Point*a, Point* b);
    QuadTree* getNeighbour(int direction);
    
    Point* getNECorner();
    Point* getSECorner();
    Point* getNWCorner();
    Point* getSWCorner();
    Point* getSteiner();
    
    
    virtual ~QuadTree();
};



#endif	/* QUADTREE_H */


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

using namespace std;

class QuadTree{
    
    void match(Point* p);

public:
    class QuadTree* NE;
    class QuadTree* NW;
    class QuadTree* SE;
    class QuadTree* SW;
    
    Point* center;
    float width;
    float half;
    Point* chunk;
    
    int depth;
    
    QuadTree(float cx, float cy, float w);
    
    bool isLeaf() const;
    
    void subdivide();
    
    void putNextPoint(Point * p);
    
    friend ostream& operator<<(ostream& out, const QuadTree& tree);
    
    virtual ~QuadTree();
};

#endif	/* QUADTREE_H */


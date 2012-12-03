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



class QuadTree{
    enum Direction { N, NE, E, SE, S, SW, W, NW};
    enum DiagonalDir {NE, NW, SE, SW};
    enum PerpendicularDir {N, E, S, W};
    
    void match(Point* p);
    FlushTable<Point> * flush;
    
    QuadTree* getChildByRegion(DiagonalDir region);
    void create_extended_neighbour(Direction direction);
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
    
    /**w ktorej czesci rodzica znajduje sie dany node.*/
    DiagonalDir parent_region;
    Point* center;
    float width;
    float half;
    Point* chunk;
    
    int depth;
    
    QuadTree(float cx, float cy, float w, QuadTree* parent);
    
    bool isLeaf() const;
    
    void subdivide();
    void subdivide(DiagonalDir region, int target_depth);
    void create_extended_neighbours();
    
    void putNextPoint(Point * p);
    
    friend ostream& operator<<(ostream& out, const QuadTree& tree);
    
    Point* getCrossing(Point*a, Point* b);
    
    QuadTree* getNeighbour(int direction);
    QuadTree* getNeighbour(Direction direction);
    
    Point* getNECorner();
    Point* getSECorner();
    Point* getNWCorner();
    Point* getSWCorner();
    Point* getSteiner();
    
    
    virtual ~QuadTree();
};



#endif	/* QUADTREE_H */


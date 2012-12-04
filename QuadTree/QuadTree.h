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

enum Direction {
    Dir_N, Dir_NE, Dir_E, Dir_SE, Dir_S, Dir_SW, Dir_W, Dir_NW
};

enum DiagonalDir {
    Diag_NE, Diag_NW, Diag_SE, Diag_SW
};

enum PerpendicularDir {
    Per_N, Per_E, Per_S, Per_W
};

class QuadTree {
    void match(Point* p);
    FlushTable<Point> * flush;
    
    QuadTree* getChildByRegion(DiagonalDir region);
    QuadTree* QuadTree::getChildContainingCoord(PerpendicularDir side, double value);
    
    void create_extended_neighbour(Direction direction);
    Point * NECorner;
    Point * NWCorner;
    Point * SECorner;
    Point * SWCorner;

    QuadTree* getNeighbour(Direction direction, QuadTree* source);
    QuadTree* slideDown(Direction direction, QuadTree* source);
    
public:


    class QuadTree* NEChild;
    class QuadTree* NWChild;
    class QuadTree* SEChild;
    class QuadTree* SWChild;
    class QuadTree* parent;

    /**w ktorej czesci rodzica znajduje sie dany node.*/
    DiagonalDir parent_region;
    Point* center;
    double width;
    double half;
    Point* chunk;

    int depth;

    QuadTree(double cx, double cy, double w, QuadTree* parent);
    QuadTree* getChildByRegion(DiagonalDir region);
    void create_extended_neighbour(Direction direction);

    bool isLeaf() const;

    void subdivide();
    void subdevide(PerpendicularDir side, int target_depth, double side_middle);
    void subdivide(DiagonalDir region, int target_depth);
    void create_extended_neighbours();

    void putNextPoint(Point * p);

    friend ostream& operator<<(ostream& out, const QuadTree& tree);

    Point* getCrossing(Point*a, Point* b);

    
    QuadTree* getNeighbour(Direction direction);

    Point* getNECorner();
    Point* getSECorner();
    Point* getNWCorner();
    Point* getSWCorner();
    Point* getSteiner();


    virtual ~QuadTree();
};



#endif	/* QUADTREE_H */


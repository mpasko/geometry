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
#include "Polygon.h"

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
    FlushTable<Point> * flush;
    
    Polygon* polygon;
    Point * NECorner;
    Point * NWCorner;
    Point * SECorner;
    Point * SWCorner;

    QuadTree* getNeighbour(Direction direction, QuadTree* source);
    QuadTree* slideDown(Direction direction, QuadTree* source);
    bool is_unbalanced();
    void balance_children();
    
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
    bool isLeaf() const;
    
    QuadTree* match(Point* p);

    QuadTree* getChildByRegion(DiagonalDir region);
    QuadTree* getChildContainingCoord(PerpendicularDir side, double value);
    void split_too_close_boxes();
    void split_to_maximize_distance();
    void split_until_size(double target_size);
    void create_extended_neighbour(Direction direction);
    
    void subdivide();
    void subdivide(PerpendicularDir side, int target_depth, double side_middle);
    void subdivide(DiagonalDir region, int target_depth);
    void create_extended_neighbours();
    
    void balance_tree();

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


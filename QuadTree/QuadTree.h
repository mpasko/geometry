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
#include "MergeTable.h"
#include "OutputManager.h"
#include <list>

using namespace std;

/** 8 glownych kierunkow swiata*/
enum Direction {
    Dir_N, Dir_NE, Dir_E, Dir_SE, Dir_S, Dir_SW, Dir_W, Dir_NW
};

/** Podzbior typu Direction - kierunki ukosne */
enum DiagonalDir {
    Diag_NE, Diag_NW, Diag_SE, Diag_SW
};

/** Podzbior typu */
enum PerpendicularDir {
    Per_N, Per_E, Per_S, Per_W
};

class QuadTree {
    FlushTable<Point> * flush;
    class OutputManager* output_manager;

    Point * NECorner;
    Point * NWCorner;
    Point * SECorner;
    Point * SWCorner;

    QuadTree* getNeighbour(Direction direction, Direction source_dir, QuadTree* source);
    QuadTree* slideDown(Direction direction, QuadTree* source);

    bool is_unbalanced();
    bool balance_children();
    void print_as_text(int spaces);
    bool balance();

public:
    std::list<Point*> points;


    class QuadTree* NEChild;
    class QuadTree* NWChild;
    class QuadTree* SEChild;
    class QuadTree* SWChild;

    Point * ECorner;
    Point * WCorner;
    Point * SCorner;
    Point * NCorner;

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

    void init_mesh(const list<Point*>* points_set);

    QuadTree* match(Point* p);
    QuadTree* getChildByRegion(DiagonalDir region);
    QuadTree* getChildContainingCoord(PerpendicularDir side, double value);
    void split_too_close_boxes();
    void split_to_maximize_distance(double accepted_distance);
    void split_until_size(double target_size);
    void create_extended_neighbour(Direction direction);

    QuadTree* getDiagonalNode(DiagonalDir region, QuadTree* source);
    void subdivide();
    void subdivideOrthogonal(PerpendicularDir side, int target_depth, double side_middle);
    void subdivideDiagonal(DiagonalDir region, QuadTree* source, int target_depth);
    void surround_with_neighbours_ascending();
    void create_extended_neighbours();

    void balance_tree();

    void putNextPoint(Point * p);
    void print_as_text();

    friend ostream & operator<<(ostream& out, const QuadTree& tree);

    Point* getCrossing(Point*a, Point* b);


    QuadTree* getNeighbour(Direction direction);

    Point* getNECorner() const;
    Point* getSECorner() const;
    Point* getNWCorner() const;
    Point* getSWCorner() const;

    Point* getSteiner();

    void transform();
    void mergeCorners(MergeTable* m);

    virtual ~QuadTree();

    void set_output_manager(OutputManager*& output_manager);
    void fill_points_list(const list<Point*>& points_set);
};


#endif	/* QUADTREE_H */


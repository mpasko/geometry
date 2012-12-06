/* 
 * File:   newsimpletest.cpp
 * Author: marcin
 *
 * Created on Dec 3, 2012, 11:52:04 PM
 */

#include <stdlib.h>
#include <iostream>
#include "QuadTree.h"
#include "unexpected_subdivision.h"
#include "MergeTable.h"
#include "Point.h"

/*
 * Simple C++ Test Suite
 */

void printQT(QuadTree * qt, const char* name) {
    if (qt == NULL) {
        std::cout << name << " -null " << std::endl;
    } else {
        std::cout << name << " content: " << std::endl;
        std::cout << *qt;
        std::cout << name << " finish " << std::endl;
    }
}

void testGetNeighbourSide() {
    Direction direction = Dir_N;
    QuadTree tree(0.0, 0.0, 100, NULL);
    tree.subdivide();
    tree.SEChild->subdivide();
    QuadTree* child = tree.SEChild->NWChild;
    QuadTree* result = child->getNeighbour(direction);
    if (result != tree.NEChild) {
        printQT(result, "result");
        printQT(tree.NWChild, "child");
        std::cout << "%TEST_FAILED% time=0 testname=testGetNeighbour (newsimpletest) message=error message sample" << std::endl;
    }
}

void testGetNeighbourSideSplit() {
    Direction direction = Dir_N;
    QuadTree tree(0.0, 0.0, 100, NULL);
    tree.subdivide();
    tree.NEChild->subdivide();
    tree.SEChild->subdivide();
    QuadTree* child = tree.SEChild->NWChild;
    QuadTree* result = child->getNeighbour(direction);
    if (result != tree.NEChild->SWChild) {
        printQT(result, "result");
        printQT(tree.NWChild->SEChild, "child");
        std::cout << "%TEST_FAILED% time=0 testname=testGetNeighbour (newsimpletest) message=error message sample" << std::endl;
    }
}

void testGetNeighbourCornerSplit() {
    Direction direction = Dir_NW;
    QuadTree tree(0.0, 0.0, 100, NULL);
    tree.subdivide();
    tree.SEChild->subdivide();
    tree.NWChild->subdivide();
    QuadTree* child = tree.SEChild->NWChild;
    QuadTree* result = child->getNeighbour(direction);
    if (result != tree.NWChild->SEChild) {
        printQT(result, "result");
        printQT(tree.NWChild->SEChild, "child");
        std::cout << "%TEST_FAILED% time=0 testname=testGetNeighbour (newsimpletest) message=error message sample" << std::endl;
    }
}

void testGetNeighbourCorner() {
    Direction direction = Dir_NW;
    QuadTree tree(0.0, 0.0, 100, NULL);
    tree.subdivide();
    tree.SEChild->subdivide();
    QuadTree* child = tree.SEChild->NWChild;
    QuadTree* result = child->getNeighbour(direction);
    if (result != tree.NWChild) {
        printQT(result, "result");
        printQT(tree.NWChild, "child");
        std::cout << "%TEST_FAILED% time=0 testname=testGetNeighbour (newsimpletest) message=error message sample" << std::endl;
    }
}

void testGetNeighbourCornerBig() {
    Direction direction = Dir_NE;
    QuadTree tree(0.0, 0.0, 100, NULL);
    tree.subdivide();
    tree.SEChild->subdivide();
    QuadTree* child = tree.SEChild->NWChild;
    QuadTree* result = child->getNeighbour(direction);
    if (result != tree.NEChild) {
        printQT(result, "result");
        printQT(tree.NWChild, "child");
        std::cout << "%TEST_FAILED% time=0 testname=testGetNeighbour (newsimpletest) message=error message sample" << std::endl;
    }
}

void testGetNeighbourSideNoSplit(){
    Direction direction = Dir_NW;
    QuadTree tree(0.0, 0.0, 100, NULL);
    tree.subdivide();
    tree.SEChild->subdivide();
    tree.NWChild->subdivide();
    QuadTree* child = tree.SEChild;
    QuadTree* result = child->getNeighbour(direction);
    if (result != tree.NWChild) {
        printQT(result, "result");
        printQT(tree.NWChild->SEChild, "child");
        std::cout << "%TEST_FAILED% time=0 testname=testGetNeighbour (newsimpletest) message=error message sample" << std::endl;
    }
}

void div_fail(){
    QuadTree tree(0.0, 0.0, 100, NULL);
    try{
        tree.subdivide();
        tree.subdivide();
        std::cout << "%TEST_FAILED% time=0 testname=div_fail (newsimpletest) message=uncaugh" << std::endl;
    }catch(Unexpected_subdivision e){
        std::cout << "testname=div_fail (newsimpletest) message=caugh" << std::endl;
    }
}

void mergetest(){
    MergeTable merge(10);
    Point x(10.0,10.0);
    Point y(10.0,10.0);
    Point z(10.0,10.0);
    Point w(10.0,10.0);
    Point * a = &x;
    Point * b = &y;
    Point * c = &z;
    Point * d = &w;
    merge.merge(&a,&b);
    merge.merge(&c,&d);
    merge.merge(&a,&c);
    if(a==b && a==d && b==d){
        std::cout << "merge success!\n";
    }else{
        std::cout << "%TEST_FAILED% time=0 testname=mergetest (newsimpletest) message=merge failed!" << std::endl;
    }
}

void testSlideDown(){
    Direction direction = Dir_SW;
    QuadTree tree(0.0, 0.0, 100, NULL);
    tree.subdivide();
    tree.SEChild->subdivide();
    tree.SWChild->subdivide();
    QuadTree* child = tree.SEChild->NWChild;
    QuadTree* result = child->getNeighbour(direction);
    if (result != tree.SWChild->SEChild) {
        printQT(result, "result");
        printQT(tree.SWChild->SEChild, "child (SWChild->SEChild)");
        std::cout << "%TEST_FAILED% time=0 testname=testGetNeighbour (newsimpletest) message=error message sample" << std::endl;
    }
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% newsimpletest" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% testGetNeighbour (newsimpletest)" << std::endl;
    cout<< "side\n";
    testGetNeighbourSide();
    cout<< "side split\n";
    testGetNeighbourSideSplit();
    cout<< "corner\n";
    testGetNeighbourCorner();
    cout<< "corner_split\n";
    testGetNeighbourCornerSplit();
    cout<< "corner_big\n";
    testGetNeighbourCornerBig();
    cout << "side_down\n";
    testSlideDown();
    cout << "side_no_split\n";
    testGetNeighbourSideNoSplit();
    cout << "div_fail\n";
    div_fail();
    cout << "merge\n";
    mergetest();
    std::cout << "%TEST_FINISHED% time=0 testGetNeighbour (newsimpletest)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}


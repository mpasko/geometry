/* 
 * File:   newsimpletest.cpp
 * Author: marcin
 *
 * Created on Dec 3, 2012, 11:52:04 PM
 */

#include <stdlib.h>
#include <iostream>
#include "QuadTree.h"

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
    std::cout << "%TEST_FINISHED% time=0 testGetNeighbour (newsimpletest)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

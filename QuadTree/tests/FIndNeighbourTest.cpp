/* 
 * File:   newsimpletest.cpp
 * Author: Admin
 *
 * Created on 2012-12-06, 10:30:46
 */

#include <stdlib.h>
#include <iostream>

#include "QuadTree.h"

/*
 * Simple C++ Test Suite
 */

void test1() {
    std::cout << "newsimpletest test 1" << std::endl;
    QuadTree root(0, 0, 100, NULL);
    root.subdivide();
    root.NEChild->subdivide();
    root.NWChild->subdivide();
    root.NEChild->SWChild->subdivide();
    
    QuadTree* searched = root.NWChild->NEChild;
    QuadTree* found = root.NEChild->SWChild->NWChild->getNeighbour(Dir_NW);
    if (searched != found){
        std::cout << "FAIL" << endl;
        //std::cout << "%TEST_FAILED% time=0 testname=test2 (newsimpletest) message=error message sample" << std::endl;
    } else {
        std::cout << "OK" << endl;
    }
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% newsimpletest" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% test1 (newsimpletest)" << std::endl;
    test1();
    std::cout << "%TEST_FINISHED% time=0 test1 (newsimpletest)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}



#include <stdio.h>
#include "MergeTable.h"
#include "QuadTree.h"



void QuadTree::mergeCorners(MergeTable* m) {
    //QuadTree* neighbour
    if (isLeaf()) {

    } else {
        std::cout << "before ";
        m->merge(&NECorner,&NEChild->NECorner);
        std::cout << "in ";
        m->merge(&NWCorner,&NWChild->NWCorner);
        m->merge(&SECorner,&SEChild->SECorner);
        m->merge(&SWCorner,&SWChild->SWCorner);
        m->merge(&ECorner,&NEChild->SECorner);
        m->merge(&ECorner,&NEChild->SECorner);
        m->merge(&WCorner,&NWChild->SWCorner);
        m->merge(&WCorner,&NWChild->SWCorner);
        m->merge(&NCorner,&NEChild->NWCorner);
        m->merge(&NCorner,&NWChild->NECorner);
        m->merge(&SCorner,&SEChild->SWCorner);
        m->merge(&SCorner,&SWChild->SECorner);
        std::cout << "middle ";
        NEChild->mergeCorners(m);
        NWChild->mergeCorners(m);
        SEChild->mergeCorners(m);
        SWChild->mergeCorners(m);
    }
}

void QuadTree::transform() {
    if (isLeaf()) {
        if (chunk != NULL) {
            if (chunk->x > center->x) {
                if (chunk->y > center->y) {
                    //NE
                    NECorner->x = chunk->x;
                    NECorner->y = chunk->y;
                } else {
                    //SE
                    SECorner->x = chunk->x;
                    SECorner->y = chunk->y;
                }
            } else {
                if (chunk->y > center->y) {
                    //NW
                    NWCorner->x = chunk->x;
                    NWCorner->y = chunk->y;
                } else {
                    //SW
                    SWCorner->x = chunk->x;
                    SWCorner->y = chunk->y;
                }
            }
        }
    } else {
        NEChild->transform();
        NWChild->transform();
        SEChild->transform();
        SWChild->transform();
    }
}


#include <stdio.h>
#include "MergeTable.h"
#include "QuadTree.h"

void QuadTree::mergeCorners(MergeTable* m) {
    //QuadTree* neighbour

    
    QuadTree * NNeigh = getNeighbour(Dir_N);
    if ((NNeigh!=NULL)&&(NNeigh->depth == depth)) {
        m->merge(&NCorner,&(NNeigh->SCorner));
        m->merge(&NECorner,&(NNeigh->SECorner));
        m->merge(&NWCorner,&(NNeigh->SWCorner));
    }
    
    QuadTree * SNeigh = getNeighbour(Dir_S);
    if ((SNeigh!=NULL)&&(SNeigh->depth == depth)) {
        m->merge(&SCorner,&(SNeigh->SCorner));
        m->merge(&SECorner,&(SNeigh->SECorner));
        m->merge(&SWCorner,&(SNeigh->SWCorner));
    }
    
    QuadTree * ENeigh = getNeighbour(Dir_E);
    if ((ENeigh!=NULL)&&(ENeigh->depth == depth)) {
        m->merge(&ECorner,&(ENeigh->WCorner));
        m->merge(&NECorner,&(ENeigh->NWCorner));
        m->merge(&SECorner,&(ENeigh->SWCorner));
    }
    
    QuadTree * WNeigh = getNeighbour(Dir_W);
    if ((WNeigh!=NULL)&&(WNeigh->depth == depth)) {
        m->merge(&WCorner,&(WNeigh->ECorner));
        m->merge(&NWCorner,&(WNeigh->NECorner));
        m->merge(&SWCorner,&(WNeigh->SECorner));
    }
    
    

    if (isLeaf()) {

    } else {
        m->merge(&NECorner, &(NEChild->NECorner));
        m->merge(&NWCorner, &(NWChild->NWCorner));
        m->merge(&SECorner, &(SEChild->SECorner));
        m->merge(&SWCorner, &(SWChild->SWCorner));

        m->merge(&ECorner, &(NEChild->SECorner));
        m->merge(&ECorner, &(NEChild->SECorner));
        m->merge(&WCorner, &(NWChild->SWCorner));
        m->merge(&WCorner, &(NWChild->SWCorner));
        m->merge(&NCorner, &(NEChild->NWCorner));
        m->merge(&NCorner, &(NWChild->NECorner));
        m->merge(&SCorner, &(SEChild->SWCorner));
        m->merge(&SCorner, &(SWChild->SECorner));



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

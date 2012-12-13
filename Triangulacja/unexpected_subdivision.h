/* 
 * File:   unexpected_subdivision.h
 * Author: marcin
 *
 * Created on December 4, 2012, 4:10 AM
 */

#ifndef UNEXPECTED_SUBDIVISION_H
#define	UNEXPECTED_SUBDIVISION_H

#include "General_exception.h"

/**
 * Wyjątek rzucany, gdy nastąpi próba nieporządanego podziału kwadratu.
 */
class Unexpected_subdivision : public General_exception {
    public:
    Unexpected_subdivision() : General_exception(){
    }

    Unexpected_subdivision(std::string cause) : General_exception(cause){
        
    }
};

#endif	/* UNEXPECTED_SUBDIVISION_H */


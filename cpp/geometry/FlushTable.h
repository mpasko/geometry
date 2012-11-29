/* 
 * File:   FlushTable.h
 * Author: marcin
 *
 * Created on November 29, 2012, 1:27 PM
 */

#ifndef FLUSHTABLE_H
#define	FLUSHTABLE_H

template<typename T>
class FlushTable{
    T** flushtable;
    int flushindex;
    int size;
public:
    FlushTable(int sz);
    
    void operator+=(T* obj);
    
    virtual ~FlushTable();
};

#endif	/* FLUSHTABLE_H */


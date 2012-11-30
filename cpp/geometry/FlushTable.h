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

#include <iostream>
#include <exception>

template<typename T>
FlushTable<T>::FlushTable(int sz):flushindex(0),size(sz){
        flushtable = new T*[sz];
}

template<typename T>
void FlushTable<T>::operator+=(T* obj){
        flushtable[flushindex++] = obj;
        if(flushindex>=size){
            std::cout << "Error! FlushTable overflow!\n";
            throw size;
        }
}

template<typename T>
FlushTable<T>::~FlushTable(){
    for(int i = 0; i<flushindex; ++i){
        try{
            delete flushtable[i];
        }catch(std::exception e){
            std::cout << "Error! FlushTable elements should not be released manually!\n";
        }
    }
    delete flushtable;
}

#endif	/* FLUSHTABLE_H */


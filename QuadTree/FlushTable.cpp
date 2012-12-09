/* 
 * File:   FlushTable.cpp
 * Author: marcin
 * 
 * Created on November 29, 2012, 1:27 PM
 */

#include "FlushTable.h"

#include <iostream>
#include <exception>

template<class T>
FlushTable<T>::FlushTable(int sz):flushindex(0),size(sz){
        flushtable = new T*[sz];
}

template<class T>
void FlushTable<T>::operator+=(T* obj){
        flushtable[flushindex++] = obj;
        if(flushindex>=size){
            std::cout << "Error! FlushTable overflow!\n";
            throw size;
        }
}

template<class T>
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

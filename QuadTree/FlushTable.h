/* 
 * File:   FlushTable.h
 * Author: marcin
 *
 * Created on November 29, 2012, 1:27 PM
 */

#ifndef FLUSHTABLE_H
#define	FLUSHTABLE_H

/** \brief Szablon klasy ułatwiający panowanie nad wyciekami pamieci. Zawiera tablicę wskaźników na obszary pamieci do późniejszego zwolnienia. */
template<class T>
class FlushTable{
    T** flushtable;
    int flushindex;
    int size;
public:
    FlushTable(int sz);
    
    /** \brief Dodaje wskaźnik na pilnowany obiekt do tablicy
    * @param wskaźnik na obiekt do zwolnienia
    */
    void operator+=(T* obj);
    
    virtual ~FlushTable();
};

#endif	/* FLUSHTABLE_H */


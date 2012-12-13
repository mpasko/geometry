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
    /** Tablica wskaźników do pamięci*/
    T** flushtable;
    /** Index wskazujący na wolne miejsce w tablicy. */
    int flushindex;
    /** Rozmiar tablicy*/
    int size;
public:
    /**
     * @param sz rozmiar talbicy flushtable
     */
    FlushTable(int sz);
    
    /** \brief Dodaje wskaźnik na pilnowany obiekt do tablicy
    * @param obj wskaźnik na obiekt do zwolnienia
    */
    void operator+=(T* obj);
    
    virtual ~FlushTable();
};

#endif	/* FLUSHTABLE_H */


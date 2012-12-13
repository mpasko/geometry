/*
 * \brief metody do zapisywania stanu symulacji
 */

#ifndef VISUALIZATION_H
#define	VISUALIZATION_H

#define PASKO

#include "Point.h"
#include <iostream>
#include <fstream>

#define red "ff0000"
#define green "00ff00"
#define blue "0000ff"
#define black "000000"

/** \brief Formatuje pojedynczy punkt w celu wizualizacji
* @param out strumień wyjściowy
* @param x1 odcięta
* @param y1 rzędna
* @param color kolor 
*/
void drawpoint(std::ostream& out, const float x1, const float y1, const char*color);

/** \brief Formatuje odcinek złożony z dwóch punktów w celu wizualizacji
* @param out strumień wyjściowy
* @param x1 odcięta pierwszego punktu
* @param y1 rzędna pierwszego punktu 
* @param x2 odcięta drugiego punktu
* @param y2 rzędna drugiego punktu
* @param color kolor 
*/
void drawline(std::ostream& out, const float x1, const float y1, const float x2, const float y2, const char*color);

/** \brief Formatuje pojedynczy punkt w celu wizualizacji
* @param out strumień wyjściowy
* @param p1 punkt
* @param color kolor 
*/
void drawline(std::ostream& out, const Point*p1, const char*color);

/** \brief Formatuje odcinek złożony z dwóch punktów w celu wizualizacji
* @param out strumień wyjściowy
* @param p1 pierwszy punkt
* @param p2 drugi punkt
* @param color kolor 
*/
void drawline(std::ostream& out, const Point*p1, const Point*p2, const char*color);

/** \brief Separuje kroki algorytmu, czyści obszar graficzny wizualizatora
* @param out strumień wyjściowy
*/
void step(std::ostream& out);

#endif	/* VISUALIZATION_H */


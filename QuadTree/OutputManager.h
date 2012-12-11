#ifndef OUTPUTMANAGER_H
#define	OUTPUTMANAGER_H

#include "QuadTree.h"

#include <list>
#include <ostream>
#include <fstream>

/** \brief Klasa do zapisywania bierzącego stanu symulacji do pliu */
class OutputManager {
public:
    OutputManager(Polygon* polygon,  QuadTree* quadtree, std::ofstream* out_stream);
    OutputManager(std::list<Point*>* points_set,  QuadTree* quadtree, std::ofstream* out_stream);

    /**
     * Zapisuje obecny stan symulacji do pliku, czyli strukturę QuadTree oraz położenie
     * zbioru triangulowanych punktów lub triangulownego wielokąta.
     */
    void print_simulation_step();
private:
    /**
     * Informuje co wypisać do pliku, jeżeli pole jest rowne <i>true</i>
     * triangulacja odbywa się dla zbioru punktów, w przeciwnym przypadku dla
     * wielokąta i oprocz punktw zapisane są rownież krawędzie
     */
    bool draws_points_set;

    /**
     * Strumień wyjściowy
     */
    std::ofstream* output_stream;
    QuadTree* quad_tree;
    Polygon* polygon;
    std::list<Point*>* points_set;
};

#endif	/* OUTPUTMANAGER_H */


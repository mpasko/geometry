#ifndef OUTPUTMANAGER_H
#define	OUTPUTMANAGER_H

#include "QuadTree.h"

#include <list>
#include <ostream>
#include <fstream>

/**
 * Klasa do zapisywania bierzącego stanu symulacji do pliku.
 * Klasa zapisuje dane eksperymentu w fomacie, który umożliwia  późniejsze
 * wyświetlenie zapisanego stanu w wizualizatorze.*/
class OutputManager {
public:
    /**
     * Konstruktor output managera nad zbiorem punktów.
     * @param polygon wielokąt dla którego jest generowana siatka
     * @param quadtree drzewo quadtree użyte do generacji siatki
     * @param out_stream strumień wyjściowy, do zapisywania przebiegu symulacji
     */
    OutputManager(Polygon*& polygon, QuadTree*& quadtree, std::ofstream*& out_stream);
    /**
     * Konstruktor output managera nad zbiorem punktów.
     * @param points_set zbiór punktów dla którego jest generowana siatka
     * @param quadtree drzewo quadtree użyte do generacji siatki
     * @param out_stream strumień wyjściowy, do zapisywania przebiegu symulacji
     */
    OutputManager(std::list<Point*>*& points_set, QuadTree*& quadtree, std::ofstream*& out_stream);

    /** Zapisanie obecnego stanu symulacji do pliku. Dane są zapisane jako nowy krok symulacji.
     * Zapisana zostaje struktura QuadTree oraz położenie zbioru triangulowanych
     * punktów lub wielokąta, zależnie od tego co zostało podane na wejściu
     * algorytmu. Jeżeli wskaźnik do któregoś z powyższych elementów jest
     * równy NULL, element nie jest wypisany, jeżeli wskaźnik na strumień wyjściowy
     * jest równy NULL funkcja natychmiast wraca.
     */
    void print_simulation_step();
    
    /**
     * Zapisuje zbiór punktów(lub wielokąt) do pliku. Dane są zapisane jako nowy krok symulacji.
     * Jeżeli wskaźnik na strumień wyjściowy jest równy NULL funkcja natychmiast wraca.
     */
    void print_points_set();
private:
    /**
     * Informuje co wypisać do pliku. Jeżeli pole jest rowne <i>true</i>
     * output manager przyjmuje, że triangulacja odbywa się dla zbioru punktów,
     * w przeciwnym przypadku zakłada, że jako wejście podano wielokąt
     */
    bool draws_points_set;

    /**
     * Strumień wyjściowy
     */
    std::ofstream* output_stream;

    /**
     * Quadtree, używane do generacji siatki
     */
    QuadTree* quad_tree;

    /**
     * Wskaźnik na wielokąt dla którego generowana jest siatka.
     * Jeżeli siatka jest generowana dla zbioru punktów zamiast wielokąta
     * pole jest równe NULL.
     */
    Polygon* polygon;

    /**
     * Wskaźnik na listę punktów dla których generowana jest siatka.
     * Jeżeli siatka jest generowana dla wielokąta zamiast zbioru punktów
     * pole jest równe NULL.
     */
    std::list<Point*>* points_set;
};

#endif	/* OUTPUTMANAGER_H */


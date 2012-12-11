/* 
 * File:   QuadTree.h
 * Author: marcin
 *
 * Created on December 2, 2012, 8:17 PM
 */

#ifndef QUADTREE_H
#define	QUADTREE_H

#include <iostream>
#include <list>
#include "Point.h"
#include "FlushTable.h"
#include "Polygon.h"
#include "MergeTable.h"
#include "OutputManager.h"

using namespace std;

/** 8 glownych kierunkow swiata*/
enum Direction {
    Dir_N, Dir_NE, Dir_E, Dir_SE, Dir_S, Dir_SW, Dir_W, Dir_NW
};

/** Podzbior typu Direction - kierunki ukosne */
enum DiagonalDir {
    Diag_NE, Diag_NW, Diag_SE, Diag_SW
};

/** Podzbior typu */
enum PerpendicularDir {
    Per_N, Per_E, Per_S, Per_W
};

/** \brief Klasa reprezentująca QuadTree, zawiera w sobie metody do przekształcania jego struktury.*/
class QuadTree {
    FlushTable<Point> * flush;
    class OutputManager* output_manager;

    Point * NECorner;
    Point * NWCorner;
    Point * SECorner;
    Point * SWCorner;

    QuadTree* getNeighbour(Direction direction, Direction source_dir, QuadTree* source);
    QuadTree* slideDown(Direction direction, QuadTree* source);

    /**
     * Sprawdzenie czy węzeł jest zrównoważony
     * @return <i>true</i> jeżeli sąsiedzi spełniają warunki równowagi dla węzła,
     * <i>false</i> w przeciwnym przypadku.
     */
    bool is_unbalanced();

    /**
     * Rekursywne równoważenie dzieci węzła, aż dojdzie do liści.
     * @return <i>true</i> jeżeli choć jeden węzeł w poddrzewie węzła został
     * podzielony, <i>false</i> w przeciwnym przypadku.
     */
    bool balance_children();

    /**
     * Rekursywnie równoważy węzeł tak długo, aż węzeł oraz całe jego poddrzewo
     * spełnia warunki równowagi
     * @return <i>true</i> jeżeli węzeł lub choć jeden węzeł w poddrzewie został
     * podzielony, <i>false</i> w przeciwnym przypadku.
     */
    bool balance();

    /**
     * Zwraca wskaźnik do dziecka poddrzewa w którym znaleźć się punkt. <br>
     * <b>UWAGA : </b> jeżeli punkt leży poza kwadratem wynik działania funkcji
     * jest nieokreślony.
     * @param p sprawdzany punkt
     * @return dziecko do którego powinien należeć punkt
     */
    QuadTree* match(Point* p);

    /**
     * Pobiera dziecko zależnie od wskazanego regionu
     * @param region ćwiartka węzła
     * @return wskaźnik na dziecko znajdujące się we wskazanej ćwiartce
     */
    QuadTree* getChildByRegion(DiagonalDir region);

    /**
     * Pobiera dziecko znajdujące się przy wskazanej ścianie węzła wg podanej
     * współrzędnych
     * @param side przy której ścianie należy szukać dziecka
     * @param value wartość jednej ze współrzędnych, która musi zawierać się w
     * dziecku, w przypadku szukania dziecka przy ścianie pionowej kwadratu
     * jest to współrzędna y-kowa, w przypadku sszuaknia przy ścianie poziomej
     * jest to współrzędna x-owa.
     * @return szukane dziecko lub <i>NULL</i> jeżeli węzeł jest liściem.
     */
    QuadTree* getChildContainingCoord(PerpendicularDir side, double value);

    void split_to_maximize_distance(double accepted_distance);
    void split_until_size(double target_size);

    /**Tworzy rozszerzonego sąsiada w jednym z sąsiadów węzła*/
    void create_extended_neighbour(Direction direction);

    /**
     * Rekursywnie dzieli pionowy lub poziomego węzeł do ustalone głębokości. Przy każdym
     * z podziałów na danej głębokości dzielone jest jedno i tylko jedno dziecko.
     * @param side pionowy lub poziomy kierunek w którym mają następować koejne podziały
     * @param target_depth głębokość do której ma następować podział
     * @param side_middle współrzędna x-owa w przypadku podziałów w kierunku ściany
     * poziomej lub y-kowa w przypadku podziałów w kierunku ściany pioowej, koeljny
     * kwadrat wybierany do do kolejnego podziiału musi znajodwać się możliwie
     * najbliżej ściany wskazywanej przez <b>side</b> i zawierać podaną wspórzędną
     */
    void subdivideOrthogonal(PerpendicularDir side, int target_depth, double side_middle);

    /**
     * Rekursywnie dzieli węzeł na powęzły, aż do określonej głębokości. Przy każdym
     * z podziałów na danej głębokości dzielone jest jedno i tylko jedno dziecko
     * @param region skośny kierunek określający w jakim kierunku od najmniejszego podzału
     * powinien znajdwać się węzeł, który wywołał na obecnymw ęźle podział
     * @param węzeł, który wywołał na obecnymw węźle podział, wraz z parametrem
     * <b>region</b> pozwala wybrać dziecko, do następnego rekursywnego podziału
     * @param target_depth głębokość na jaką ma nastąpić podział
     */
    void subdivideDiagonal(DiagonalDir region, QuadTree* source, int target_depth);

    Point* getCrossing(Point*a, Point* b);
public:
    /** Zbiór wszsytkich punktów zawartych w obszarze QuadTree dla których
     jest przeprowadzana triangulacja*/
    std::list<Point*> points;

    /** Dziecko w północno-wschodnim rogu*/
    class QuadTree* NEChild;
    /** Dziecko w północno-zachodnim rogu*/
    class QuadTree* NWChild;
    /** Dziecko w południowo-wschodnim rogu*/
    class QuadTree* SEChild;
    /** Dziecko w południowo-zachodnim rogu*/
    class QuadTree* SWChild;

    Point * ECorner;
    Point * WCorner;
    Point * SCorner;
    Point * NCorner;

    class QuadTree* parent;

    /**w ktorej czesci rodzica znajduje sie dany node.*/
    DiagonalDir parent_region;
    Point* center;
    double width;
    double half;
    Point* chunk;

    int depth;

    QuadTree(double cx, double cy, double w, QuadTree* parent);

    /**
     * Sprawdzenie czy węzeł jest liściem QuadTree
     * @return <i>true</i> jeżeli węzeł jest liściem, <i>false</i> w przeciwnym 
     * przypadku
     */
    bool isLeaf() const;


    /**
     * Tworzy początkowy podział drzewa QuadTree poprzez dodawanie do niego
     * kolejnych punktów i odpowiedni podział siatki, tak by nie zanjdowały się
     * w jedynm kwadracie dwa punkty.
     * @param points_set punkty, które mają zostać dodane do siatki
     */
    void init_mesh(const list<Point*>* points_set);

    /**
     * Dzieli siatkę w taki spoób, żeby nigdy dwa różne punkty nie leżały od
     * siebie bliżej niż <i>2 * sqrt(2) * a</i>, gdzie <i>a</i> to dlugosc boku
     * kwadratu w ktorym znajduje sie punkt
     */
    void split_too_close_boxes();

    void subdivide();

    /**
     * Dzieli siatkę w taki sposób, że każdy z węzłów zawierający punkt oraz
     * każdy z rodziców tego dziecka, aż do korzenia otoczony jest ośmioma
     * rozszerzonymi sąsiadami tej samej wielkości.
     */
    void surround_with_neighbours_ascending();

    /**
     * Otacza węzeł ośmioma sąsiadami tej samej wielkości, poprzez podział
     * węzłów sąsiadujących (o ile nie są już wystarczająco podzielone)
     * z węzłem na którym została wywołana metoda.
     */
    void create_extended_neighbours();

    /**
     * Dzieli drzewo w taki sposób, żeby zrównoważyć wszystkie jego węzły.
     * Metoda wywoływana jest od korzenia i rekursywnie zagłębia się w kolejne
     * dzieci, jeżeli w czasie przechodzenia drzewa nastąpiło podzielenie
     * korzenia, metoda wywoła się ponownie po przejściu całego drzewa, do
     * momentu, gdy nic nie ulegnie zmianie.
     */
    void balance_tree();

    void putNextPoint(Point * p);

    friend ostream & operator<<(ostream& out, const QuadTree& tree);

    QuadTree* getNeighbour(Direction direction);

    Point* getNECorner() const;
    Point* getSECorner() const;
    Point* getNWCorner() const;
    Point* getSWCorner() const;

    Point* getSteiner();

    void transform();
    void mergeCorners(MergeTable* m);

    virtual ~QuadTree();

    /** Ustawia zarządcę zapisywania przebiegu symulacji, w obecnej wersji
     * programu zarządca nie jest używany w wywołaniach metod QuadTree
     * @param output_manager zarządca wypisywania symulacji
     */
    void set_output_manager(OutputManager*& output_manager);
};


#endif	/* QUADTREE_H */


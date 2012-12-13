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
#include "EmptyNodeException.h"

using namespace std;

/** 8 glownych kierunkow swiata*/
enum Direction {
    Dir_N, Dir_NE, Dir_E, Dir_SE, Dir_S, Dir_SW, Dir_W, Dir_NW
};

/** Podzbior typu Direction - kierunki ukosne */
enum DiagonalDir {
    Diag_NE, Diag_NW, Diag_SE, Diag_SW
};

/** Podzbior typu Direction - kierunki prostopadłe */
enum PerpendicularDir {
    Per_N, Per_E, Per_S, Per_W
};

/** \brief Klasa reprezentująca węzeł QuadTree, zawiera w sobie metody do przekształcania jego struktury.*/
class QuadTree {
    FlushTable<Point> * flush;
    class OutputManager* output_manager;

    /** Wierzchołek północno-wschodni */
    Point * NECorner;
    /** Wierzchołek północno-zachodni */
    Point * NWCorner;
    /** Wierzchołek południowo-wschodni */
    Point * SECorner;
    /** Wierzchołek południowo-zachodnia */
    Point * SWCorner;

    /** Służy do rekurencyjnego wywołania getNeighbour.
    * @param direction aktualny kierunek (może ulegac zmianie w kolejnych wywołaniach)
    * @param source_dir początkowy kierunek
    * @param source wskaźnik na QuadTree z którego zaczęliśmy poszukiwania
    */
    QuadTree* getNeighbour(Direction direction, Direction source_dir, QuadTree* source);
    QuadTree* slideDown(Direction direction, QuadTree* source);

    /**
     * Sprawdzenie czy węzeł jest zrównoważony.
     * @return <i>true</i> jeżeli sąsiedzi spełniają warunki równowagi dla węzła,
     * <i>false</i> w przeciwnym przypadku.
     */
    bool is_unbalanced();

    /**
     * Wywołuje balance() na wszystkich dzieciach węzła
     * @return <i>true</i> jeżeli choć jeden węzeł w poddrzewie węzła został
     * podzielony, <i>false</i> w przeciwnym przypadku.
     */
    bool balance_children();

    /**
     * Rekursywnie, zstępująco równoważy poddrzewo węzła.
     * @return <i>true</i> jeżeli węzeł lub choć jeden węzeł w poddrzewie został
     * podzielony, <i>false</i> w przeciwnym przypadku.
     */
    bool balance();

    /**
     * Zwraca wskaźnik do dziecko poddrzewa w którym powinien znaleźć się punkt. <br>
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

    /**
     * @callgraph
     * Rekurencyjnie dzieli węzeł z punktem tak długo, aż jego szerokość będzie mniejsza
     * od zadanej wartości. Funkcja sprawdza głównie, czy podział jest dozwolony,
     * właściwe dzielenie kwadratu następuje poprzez wenętrzne wywołanie funkcji
     * split_until_size(double).
     * @param accepted_distance - maksymalna szerokość jaką powinien posiadać ostateczny kwadrat
     * @throws EmptyNodeException - jeżeli kwadrat nie zawiera punktu
     */
    void split_to_maximize_distance(double accepted_distance) throw(EmptyNodeException);

    /**
     * @callergraph
     * Rekurencyjnie dzieli węzeł tak długo, aż jego szerokość będzie mniejsza
     * od zadanej wartości. Dzielony node <b>musi</b> zawierać punkt,
     * ponieważ do kolenjych podziałów wybierane jest zawsze dziecko węzła z punktem.
     * Funkcja nie sprawdza czy węzeł na którym jest wywołana jest pusty, zatem
     * przed wywołaniem funkcji należy zapenić, że węzał zawiera punkt.
     * @param target_size maksymalna szerokość ostatecznego kwadratu, otrzymanego
     * na slkutek podziału
     */
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

    /** Zwraca punkt przecięcia zadanej krawędzi z elementem siatki QuadTree 
    * @param a początek krawędzi
    * @param b koniec krawędzi
    */
    Point* getCrossing(Point*a, Point* b);
public:
    /** Zbiór wszsytkich punktów zawartych w obszarze QuadTree dla których
     jest przeprowadzana triangulacja*/
    std::list<Point*> points;

    /** Wskaźnik na dziecko w północno-wschodnim rogu*/
    class QuadTree* NEChild;
    /** Wskaźnik na dziecko w północno-zachodnim rogu*/
    class QuadTree* NWChild;
    /** Wskaźnik na dziecko w południowo-wschodnim rogu*/
    class QuadTree* SEChild;
    /** Wskaźnik na dziecko w południowo-zachodnim rogu*/
    class QuadTree* SWChild;

    /** Wskaźnik na środek wschodniej krawędzi */
    Point * ECorner;
    /** Wskaźnik na środek zachodniej krawędzi */
    Point * WCorner;
    /** Wskaźnik na środek południowej krawędzi */
    Point * SCorner;
    /** Wskaźnik na środek północnej krawędzi */
    Point * NCorner;

    /** Wskaźnik na rodzica węzła lub NULL, jeżeli węzeł jest korzeniem.*/
    class QuadTree* parent;

    /**informacja w ktorej ćwiartce rodzica znajduje sie dany node.*/
    DiagonalDir parent_region;
    
    /** Współrzędne środka */
    Point* center;
    
    /** Szerokość */
    double width;
    /** Połowa szerokosci */
    double half;
    /** Punkt zawarty wewnątrz liscia */
    Point* chunk;

    /** Głębokość zagłebienia w strukturze QuadTree */
    int depth;

    QuadTree(double cx, double cy, double w, QuadTree* parent);

    /**
     * Sprawdzenie czy węzeł jest liściem QuadTree
     * @return <i>true</i> jeżeli węzeł jest liściem, <i>false</i> w przeciwnym 
     * przypadku
     */
    bool isLeaf() const;


    /**
     * Tworzy początkowy podział drzewa QuadTree oraz inicjalizuje jego listę punktami
     * nad którymi tworzona będzie siatka. Podział następuje poprzez dodawanie do drzewa
     * kolejnych punktów z listy i odpowiedni podział siatki, tak by żadne dwa punkty
     * nie zanjdowały się one w tym samym kwadracie.
     * @param points_set punkty, które mają zostać dodane do siatki
     */
    void init_mesh(const list<Point*>* points_set);

    /**
     * Dzieli siatkę w taki spoób, żeby nigdy dwa różne punkty nie leżały od
     * siebie bliżej niż <i>2 * sqrt(2) * a</i>, gdzie <i>a</i> to dlugosc boku
     * kwadratu w ktorym znajduje sie punkt
     */
    void split_too_close_boxes();

    /** Dokonuje podpodziału na mniejsze kwadraty*/
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

    /** Wkłada kolejny punkt do struktury dokonując podpodziałów w miarę potrzeby 
    * @param p Wkładany punkt
    */
    void putNextPoint(Point * p);

    friend ostream & operator<<(ostream& out, const QuadTree& tree);

    /** Zwraca sąsiada węzła QuadTree
    * @param direction kierunek poszukiwań
    */
    QuadTree* getNeighbour(Direction direction);

    /** Pobranie północno-wschodniego wierzchołka*/
    Point* getNECorner() const;
    /** Pobranie południowo-wschodniego wierzchołka*/
    Point* getSECorner() const;
    /** Pobranie północno zachodniego wierzchołka*/
    Point* getNWCorner() const;
    /** Pobranie południowo wschodniego wierzchołka*/
    Point* getSWCorner() const;

    /** Zwraca współrzędne punktu Steinera */
    Point* getSteiner();

    /** Dokonuje transformację siatki */
    void transform();
    /** Dokonuje scalania wierzchołków 
    * @param m obiekt klasy MergeTable indeksujący wierzchołki do scalania
    */
    void mergeCorners(MergeTable* m);

    virtual ~QuadTree();

    /** Ustawia zarządcę zapisywania przebiegu symulacji, w obecnej wersji
     * programu zarządca nie jest używany w wywołaniach metod QuadTree
     * @param output_manager zarządca wypisywania symulacji
     */
    void set_output_manager(OutputManager*& output_manager);
};


#endif	/* QUADTREE_H */


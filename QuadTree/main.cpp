/* 
 * File:   main.cpp
 * Author: marcin
 *
 * Created on November 29, 2012, 1:18 PM
 */

#include <cstdlib>
#include "Point.h"
#include <exception>
#include <iostream>
#include <ostream>
#include "Polygon.h"
#include <fstream>
#include <limits>
#include <string.h>
#include "trimmer.h"
#include "QuadTree.h"
#include "Visualization.h"
#include "triangulation.h"
#include "General_exception.h"
#include "OutputManager.h"
#include "Bad_Conversion.h"
#include "random_generation.h"
#include <sstream>

using namespace std;

/*Zalozenie: os y biegnie do gory*/

Polygon* load_polygon_data(char* filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "input stream is not opened." << endl;
        exit(EXIT_FAILURE);
    }

    string s;
    getline(file, s);
    s = trim(s);
    int size = atof(s.c_str());

    Polygon * p = new Polygon(size);
    for (int i = 0; i < size; ++i) {
        float x, y;
        string sx, sy, empty;
        getline(file, sx, ',');
        sx = trim(sx);
        x = atof(sx.c_str());
        getline(file, sy, ',');
        sx = trim(sy);
        y = atof(sy.c_str());
        getline(file, empty, ',');
        getline(file, empty, ',');
        getline(file, empty, '\n');

        Point * current = new Point(x, y);
        *p += current;
    }
    file.close();
    return p;
}

list<Point*>* load_points_data(char* filename) {
    list<Point*>* points = new list<Point*>();
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "input stream is not opened." << endl;
        exit(EXIT_FAILURE);
    }

    string s;
    getline(file, s);
    s = trim(s);
    int size = atof(s.c_str());

    for (int i = 0; i < size; ++i) {
        float x, y;
        string sx, sy, empty;
        getline(file, sx, ',');
        sx = trim(sx);
        x = atof(sx.c_str());
        getline(file, sy, ',');
        sx = trim(sy);
        y = atof(sy.c_str());
        getline(file, empty, ',');
        getline(file, empty, ',');
        getline(file, empty, '\n');
        points->push_back(new Point(x, y));
    }
    file.close();
    return points;
}

QuadTree* create_initial_box(const list<Point*>* points_list) {
    double max_x = std::numeric_limits<double>::min();
    double max_y = std::numeric_limits<double>::min();
    double min_x = std::numeric_limits<double>::max();
    double min_y = std::numeric_limits<double>::max();
    double x, y;
    for (list<Point*>::const_iterator it = points_list->begin(); it != points_list->end(); ++it) {
        x = (*it)->x;
        y = (*it)->y;
        if (x > max_x) {
            max_x = x;
        }
        if (y > max_y) {
            max_y = y;
        }
        if (x < min_x) {
            min_x = x;
        }
        if (y < min_y) {
            min_y = y;
        }
    }
    double ylength = max_y - min_y;
    double xlength = max_x - min_x;
    double side;
    if (xlength > ylength) {
        side = 2 * xlength;
    } else {
        side = 2 * ylength;
    }
    return new QuadTree(max_x - xlength / 2, max_y - ylength / 2, side, NULL);
}

inline double string_to_double(string const& s) {
    istringstream i(s);
    double x;
    if (!(i >> x)) {
        throw Bad_Conversion("string_to_double(\"" + s + "\")");
    }
    return x;
}

inline int string_to_int(string const& s) {
    istringstream i(s);
    int x;
    if (!(i >> x)) {
        throw Bad_Conversion("string_to_double(\"" + s + "\"");
    }
    return x;
}

void error_imput_handler() {
    cout << "incorrect parameters use 'help' to get more details" << endl;
    exit(EXIT_FAILURE);
}

void help() {
    cout << "input:" << endl;
    cout << "polygon in_file_path [out_file_path]" << endl;
    cout << "points in_file_path [out_file_path]" << endl;
    cout << "random side_length second_side_length points_number [out_file_path]" << endl;
    cout << "random radius points_number [out_file_path]" << endl;
    cout << endl << "If no output file is specified then simulation is saved in " <<
            "\"sim_out.txt\" file. You can use this file later putting it as " <<
            "the visualizator input." << endl;
}

int main(int argc, char** argv) {

    try {
        OutputManager* output_manager;
        ofstream* out_stream;
        Polygon* p;
        QuadTree* qt;
        list<Point*>* points_list;

        if (argc >= 1 && strcmp(strlwr(argv[1]), "help") == 0) {
            help();
            return EXIT_SUCCESS;
        }

        if (strcmp(strlwr(argv[1]), "random") == 0) {
            if (strcmp(strlwr(argv[2]), "rectangle") == 0) {
                if (argc < 5) {
                    error_imput_handler();
                }
                double xrange = string_to_double(argv[3]);
                double yrange = string_to_double(argv[4]);
                int points_number = string_to_double(argv[5]);
                points_list = new list<Point*>();
                *points_list = generate_points_inside_rectangle(xrange, yrange, points_number);
                if (argc >= 6) {
                    out_stream = new ofstream(argv[6]);
                } else {
                    out_stream = new ofstream("sim_out.txt");
                }
            } else {
                if (strcmp(strlwr(argv[2]), "circle") == 0) {
                    if (argc < 4) {
                        error_imput_handler();
                    }
                    double r = string_to_double(argv[3]);
                    double points_number = string_to_int(argv[4]);
                    points_list = new list<Point*>();
                    *points_list = generate_points_inside_circle(r, points_number);
                    if (argc >= 5) {
                        out_stream = new ofstream(argv[5]);
                    } else {
                        out_stream = new ofstream("sim_out.txt");
                    }
                } else {
                    error_imput_handler();
                }
            }        
            qt = create_initial_box(points_list);
            output_manager = new OutputManager(points_list, qt, out_stream);
        } else {
            if (argc < 3) {
                error_imput_handler();
            }
            char* filen;
            filen = argv[2];
            points_list = load_points_data(filen);
            qt = create_initial_box(points_list);
            qt->set_output_manager(output_manager);

            if (strcmp(strlwr(argv[1]), "polygon") == 0) {
                p = new Polygon(points_list);
                if (argc >= 3) {
                    out_stream = new ofstream(argv[3]);
                } else {
                    out_stream = new ofstream("sim_out.txt");
                }
                output_manager = new OutputManager(p, qt, out_stream);
            } else {
                if (strcmp(strlwr(argv[1]), "points") == 0) {
                    if (argc >= 3) {
                        out_stream = new ofstream(argv[3]);
                    } else {
                        out_stream = new ofstream("sim_out.txt");
                    }
                    output_manager = new OutputManager(points_list, qt, out_stream);
                } else {
                    error_imput_handler();
                }
            }
        }

        for (list<Point*>::iterator it = points_list->begin(); it != points_list->end(); ++it) {
            cout << (*it)->x << " " << (*it)->y << endl;
        }

        ofstream& output_stream = *out_stream;

//        output_manager->print_simulation_step();

        /*stworz poczatkowa siatke poprzez dokladanie do niej kolejnych punktow
         (dzielac przy tym odpowiednio quadtree tak by dwa punkty nie lezaly
         w jednym kwadracie*/
        qt->init_mesh(points_list);
        output_manager->print_simulation_step();

        qt->split_too_close_boxes();
        /*Wypisz siatke po podzieleniu kwadratow z punktami zbyt blisko siebie*/
        output_manager->print_simulation_step();

        qt->surround_with_neighbours_ascending();
        /*Wypisz siatke po otoczaniu kwadratow z punktami i och rodzicow
         * sasaidami o tej samej wiwlkosci*/
        output_manager->print_simulation_step();

        qt->balance_tree();
        /*Wypisz siatke po zrownowazeniu drzewa*/
        output_manager->print_simulation_step();

        int size = points_list->size();
        MergeTable merge(size * size * 100);
        qt->mergeCorners(&merge);
        qt->transform();
        /*Wypisz siatke po naciagnieciu wierzcholkow QuadTree*/
        output_manager->print_simulation_step();

        /*Wypisz triangulacje z siatka quad tree oznaczona osobnym kolorem*/
        output_manager->print_simulation_step();
        triangulate(output_stream, qt);

        /*Wypisz ostateczny wynik triangulacji*/
        output_manager->print_simulation_step();
        triangulate(output_stream, qt, red);

        //step(out_stream);
        //        out_stream << *qt;
        //        out_stream << *p;


    } catch (General_exception e) {
        cout << e.what() << endl;
    }
    return 0;
}


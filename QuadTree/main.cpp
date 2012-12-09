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
#include "trimmer.h"
#include "QuadTree.h"
#include "Visualization.h"
#include "triangulation.h"
#include "General_exception.h"

using namespace std;

/*Zalozenie: os y biegnie do gory*/

Polygon* load_data(int size, char* filename) {
	Polygon * p = new Polygon(size);
	ifstream file(filename);
    if (!file.is_open()) {
		cout << "input stream is not opened." << endl;
		exit(EXIT_FAILURE);
	}
	Point * prev = NULL;
	Point * first = NULL;
	FlushTable<Point> flush(size + 1);
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
		if (prev != NULL) {
		} else {
			first = current;
		}
		prev = current;
	}
	file.close();
	return p;
}

QuadTree* create_initial_box(Polygon* polygon) {
	double max_x = std::numeric_limits<double>::min();
	double max_y = std::numeric_limits<double>::min();
	double min_x = std::numeric_limits<double>::max();
	double min_y = std::numeric_limits<double>::max();
	double x, y;
	for (int j = 0; j < polygon->length(); ++j) {
		x = (*polygon)[j]->x;
		y = (*polygon)[j]->y;
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

QuadTree* init_mesh(ostream&out_stream, Polygon* p) {
	QuadTree* qt = create_initial_box(p);

	for (int j = 0; j < p->length(); ++j) {
		qt->points.push_back((*p)[j]);
	}

	for (list<Point*>::iterator it = qt->points.begin(); it != qt->points.end(); ++it) {
		qt->putNextPoint(*it);
	}

	return qt;
}

/*
 * 
 */
int main(int argc, char** argv) {

    try {
        int size;
        char* filen;
        if (argc >= 3) {
            size = atoi(argv[1]);
            filen = argv[2];
        } else {
            size = 23;
            filen = (char*) "input.in";
        }
		ofstream out_stream("sim_out.txt");

        Polygon* p = load_data(size, filen);
        for (int i = 0; i < p->length(); ++i) {
            cout << (*p)[i]->x << " " << (*p)[i]->y << endl;
        }
        out_stream << *p;
        MergeTable merge(size * size * 100);
        QuadTree* qt = init_mesh(out_stream, p);

        //  step(out_stream);
        out_stream << *qt;
        out_stream << *p;

        qt->split_too_close_boxes();

        // step(out_stream);
        qt->preproccess();
        qt->balance_tree();
        qt->mergeCorners(&merge);
        qt->transform();

        triangulate(out_stream, p, qt);

        //step(out_stream);
        out_stream << *qt;
        out_stream << *p;

    } catch (General_exception e) {
        cout << e.what() << endl;
    }
	return 0;
}


#ifndef GFIGURE_H
#define	GFIGURE_H

#include "Display_properties.h"

using namespace std;

class GFigure {
public:
    int id;
    string symbol;
    Display_properties disp_properties;
    bool hide;

    GFigure();
    GFigure(string symbol, Display_properties disp_properties);

    virtual string to_sim_format() = 0;

};

#endif	/* GFIGURE_H */


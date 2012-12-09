#ifndef DISPLAY_PROPERTIES_H
#define	DISPLAY_PROPERTIES_H

#include <string>

using namespace std;

class Display_properties {
public:
    string color;
    int thickness;
    string style;

    Display_properties();

    Display_properties(string color, int tightness, string style);

    string to_sim_format();

    void set_properties(string color, int thickness, string style);

};

#endif	/* DISPLAY_PROPERTIES_H */



#include "Display_properties.h"
#include <stdio.h>

Display_properties::Display_properties() {
}

Display_properties::Display_properties(string color, int tightness, string style) {
        this->color = color;
        this->thickness = tightness;
        this->style = style;
    }

string Display_properties::to_sim_format() {
        char bufffer[10];
        sprintf(bufffer, "%d", thickness);
        return color + "&" + style + "&" + string(bufffer);
    }

void Display_properties::set_properties(string color, int thickness, string style){
        this->color = color;
        this->thickness = thickness;
        this->style = style;
    }


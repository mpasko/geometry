#include "GFigure.h"

GFigure::GFigure(){
}

GFigure::GFigure(string symbol, Display_properties disp_properties) : hide(false) {
    this->symbol = symbol;
    this->disp_properties = disp_properties;
}


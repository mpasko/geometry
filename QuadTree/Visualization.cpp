#include "Visualization.h"

#ifdef PASKO

//FIXME co to jest? :) -> tego tu byc nie powinno...
//tylko powinno byc tutaj: :)
static int seq = 0;

void drawpoint(std::ostream& out, const float x1, const float y1, const char*color){
    out << x1 <<", "<< -y1 <<", "<< color << ", " << "" << ", " << seq << std::endl;
    ++seq;
}

void drawline(std::ostream& out, const float x1, const float y1, const float x2, float y2, const char*color){
    out << x1 <<", "<< -y1 <<", "<< color << ", " << ""   << ", " << seq << std::endl;
    out << x2 <<", "<< -y2 <<", "<< color << ", " << "" << ", " << seq << std::endl;
    ++seq;
}

void step(std::ostream& out){
    out << "step" << std::endl;
}

#else

void drawline(std::ostream& out, const float x1, const float y1, const float x2, float y2, const char*color){
    
}

void drawpoint(std::ostream& out, const float x1, const float y1, const char*color){
    
}

#endif

void drawline(std::ostream& out, const Point*p1, const char*color){
    drawpoint(out,p1->x,p1->y,color);
}

void drawline(std::ostream& out, const Point*p1, const Point*p2, const char*color){
    drawline(out,p1->x,p1->y,p2->x,p2->y,color);
}

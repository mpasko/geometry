#include "General_exception.h"

/** \brief Wyjąek rzucany, gdy węzeł QuadTree wbrew oczekiwaniom nie zawiera punktu.*/
class EmptyNodeException : public General_exception {
public:
    EmptyNodeException() : General_exception(){
    }

    EmptyNodeException(std::string cause) : General_exception(cause){
    }
private:

};

#ifndef UNEXPECTED_ENUM_VALUE_EXCEPTION_H
#define	UNEXPECTED_ENUM_VALUE_EXCEPTION_H

#include "General_exception.h"

/**
 * \brief Wyjątek rzucany, gdy w insrukcji switch wybrany zostanie inny enum niż te z przewidywnej puli
 */
class Unexpected_enum_value_exception : public General_exception {
public:
    Unexpected_enum_value_exception() : General_exception(){
    }

    Unexpected_enum_value_exception(std::string cause) : General_exception(cause){
    }
private:

};

#endif	/* UNEXPECTED_ENUM_VALUE_EXCEPTION_H */


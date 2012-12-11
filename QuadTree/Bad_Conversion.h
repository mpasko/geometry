/* 
 * File:   Bad_Conversion.h
 * Author: Admin
 *
 * Created on 11 grudzie� 2012, 07:56
 */

#ifndef BAD_CONVERSION_H
#define	BAD_CONVERSION_H

#include "General_exception.h"

/** \brief Wyjątek rzucany przy niepoprawnej konwersji stringa na wartość określonego typu. */
class Bad_Conversion : public General_exception {
public:

    Bad_Conversion() : General_exception() {
    };

    Bad_Conversion(std::string cause) : General_exception(cause) {
    };
};


#endif	/* BAD_CONVERSION_H */

